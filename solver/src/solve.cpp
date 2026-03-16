#include "dak/solver/problem.h"
#include "dak/solver/solution.h"
#include "dak/solver/solve.h"
#include "dak/utility/progress.h"
#include "dak/utility/multi_thread_progress.h"
#include "dak/utility/threaded_worker.h"


namespace dak::solver
{
   using multi_thread_progress_t = dak::utility::multi_thread_progress_t;
   using per_thread_progress_t = dak::utility::per_thread_progress_t;
   using problem_threaded_worker_t = dak::utility::threaded_worker_t<sub_problem_t::ptr_t, all_solutions_t>;


   ////////////////////////////////////////////////////////////////////////////
   //
   // Keeper of all solutions.

   // Normalize and add a solution if it is not already known.
   static void add_solution(all_solutions_t& all_solutions, const solution_t::ptr_t& a_solution, size_t count = 1)
   {
      for (auto& [existing_solution, count] : all_solutions) {
         if ((*existing_solution <=> *a_solution) == std::strong_ordering::equal) {
            count += 1;
            return;
         }
      }
      all_solutions[a_solution] += 1;
   }

   // Add many solutions, we assume they have been already normalized.
   static void add_solutions(all_solutions_t& all_solutions, all_solutions_t& other_solutions)
   {
      for (auto& [solution, count] : other_solutions)
         add_solution(all_solutions, solution, count);
   }


   ////////////////////////////////////////////////////////////////////////////
   //
   // Solve the placement of all given tiles.

   struct solve_context_t
   {
      solve_context_t(
         problem_threaded_worker_t& a_threaded_worker,
         const problem_t::ptr_t& a_problem,
         multi_thread_progress_t& a_progress,
         size_t a_depth)
         : threaded_worker(a_threaded_worker)
         , problem(a_problem)
         , progress(a_progress)
         , recursion_depth(a_depth)
      {
      }

      solve_context_t(const solve_context_t& a_ctx)
         : threaded_worker(a_ctx.threaded_worker)
         , problem(a_ctx.problem)
         , progress(a_ctx.progress)
         , recursion_depth(a_ctx.recursion_depth)
      {
         // Note: do *not* copy solutions!
      }

      problem_threaded_worker_t& threaded_worker;
      const problem_t::ptr_t&    problem;
      per_thread_progress_t      progress;
      size_t                     recursion_depth;
      all_solutions_t            solutions;
   };

   static void solve_partial(
      const sub_problem_t::ptr_t& a_sub_problem,
      const solution_t::ptr_t& partial_solution,
      solve_context_t& a_ctx);

   static void solve_recursion(
      const sub_problem_t::ptr_t& a_sub_problem,
      const solution_t::ptr_t& a_partial_solution,
      const solution_part_t::ptr_t& a_part,
      solve_context_t& a_ctx)
   {
      solution_t::ptr_t new_partial = a_partial_solution->clone();
      new_partial->add_part(a_part);

      if (a_ctx.problem->has_more_sub_problems(a_sub_problem))
      {
         solve_partial(a_sub_problem, new_partial, a_ctx);
      }
      else if (a_ctx.problem->is_solution_valid(new_partial))
      {
         new_partial->normalize();
         add_solution(a_ctx.solutions, new_partial);
      }
   }

   static void solve_sub_problem_with_tile(
      const sub_problem_t::ptr_t& a_sub_problem,
      const solution_t::ptr_t& partial_solution,
      solve_context_t& a_ctx)
   {
      a_ctx.progress.progress(1);

      const auto potential_parts = a_ctx.problem->get_sub_problem_potential_parts(a_sub_problem, partial_solution);
      for (const auto& part : potential_parts)
      {
         if (partial_solution->is_compatible(part))
         {
            solve_recursion(a_sub_problem, partial_solution, part, a_ctx);
         }
      }
   }


   static void solve_partial(
      const sub_problem_t::ptr_t& a_sub_problem,
      const solution_t::ptr_t& partial_solution,
      solve_context_t& a_ctx)
   {
      std::vector<std::future<all_solutions_t>> solutions_futures;

      const auto sub_sub_problems = a_ctx.problem->create_sub_problems(a_sub_problem, partial_solution);
      for (const sub_problem_t::ptr_t& sub_sub_problem : sub_sub_problems)
      {
         //#ifndef _DEBUG
         //// Avoid queuing sub-sub-problem that are too simple or if there are already enough
         //// parallel tasks, to avoid overflowing the work queue.
         //if (partial_solution->is_almost_done(a_ctx.problem))
         //{
         //   // Note: a_progress is passed by value so that a new one will be created for the sub-thread.
         //   auto new_future = a_ctx.threaded_worker.add_work(sub_sub_problem, a_ctx.recursion_depth, [&a_ctx, partial_solution](sub_problem_t::ptr_t a_sub_sub_problem, size_t a_depth) -> all_solutions_t
         //   {
         //      solve_context_t ctx(a_ctx);
         //      try
         //      {
         //         ctx.recursion_depth = a_depth;
         //         solve_sub_problem_with_tile(a_sub_sub_problem, partial_solution, ctx);
         //      }
         //      catch (...)
         //      {
         //         ctx.threaded_worker.stop();
         //      }
         //      return ctx.solutions;
         //   });
         //   solutions_futures.emplace_back(std::move(new_future));
         //}
         //else
         //#endif
         {
            solve_sub_problem_with_tile(sub_sub_problem, partial_solution, a_ctx);
         }
      }

      for (auto& new_future : solutions_futures)
      {
         auto partial_solutions = a_ctx.threaded_worker.wait_for(new_future, a_ctx.recursion_depth);
         add_solutions(a_ctx.solutions, partial_solutions);
      }
   }

   all_solutions_t solve(const problem_t::ptr_t& a_problem, const solution_t::ptr_t& an_empty_solution, progress_t& a_progress)
   {
      all_solutions_t all_solutions;

      // Protect the normal non-thread-safe progress against multi-threading.
      multi_thread_progress_t mt_progress(a_progress);

      problem_threaded_worker_t threaded_worker(3, 1);

      // The first tile can be chosen arbitrarily and placed.
      // This will force the orientation of the solution, so
      // we won't have to compare with rotations or translations.

      std::vector<std::future<all_solutions_t>> solutions_futures;

      for (const auto& sub_problem : a_problem->create_initial_sub_problems())
      {
         auto new_future = threaded_worker.add_work(sub_problem, 0, [&threaded_worker , &a_problem, &an_empty_solution, &mt_progress](sub_problem_t::ptr_t sub_problem, size_t a_depth) -> all_solutions_t
         {
            solve_context_t ctx(threaded_worker, a_problem, mt_progress, a_depth);
            try
            {
               solve_sub_problem_with_tile(sub_problem, an_empty_solution, ctx);
            }
            catch (...)
            {
               ctx.threaded_worker.stop();
            }
            return ctx.solutions;
         });
         solutions_futures.emplace_back(std::move(new_future));
      }

      for (auto& new_future : solutions_futures)
      {
         auto partial_solutions = threaded_worker.wait_for(new_future, 0);
         add_solutions(all_solutions, partial_solutions);
      }

      return all_solutions;
   }

}
