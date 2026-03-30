#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include "dak/solver/solve.h"
#include "dak/utility/progress.h"
#include "dak/utility/multi_thread_progress.h"
#include "dak/utility/threaded_worker.h"

#include <set>

namespace dak::utility
{
   struct progress_t;
}

namespace dak::solver
{
   using progress_t = dak::utility::progress_t;

   template <class PROBLEM_T, class SOLUTION_T>
   struct solver_t
   {
      using SUB_PROBLEM_T   = typename PROBLEM_T::sub_problem_t;
      using SOLUTION_PART_T = typename SOLUTION_T::part_t;

      ////////////////////////////////////////////////////////////////////////////
      //
      // Container of solutions.

      using all_solutions_t = std::set<SOLUTION_T>;

      ////////////////////////////////////////////////////////////////////////////
      //
      // Solve the problem.

      static all_solutions_t solve(const PROBLEM_T& a_problem, const SOLUTION_T& an_empty_solution, progress_t& a_progress)
      {
         all_solutions_t all_solutions;

         // Protect the normal non-thread-safe progress against multi-threading.
         multi_thread_progress_t mt_progress(a_progress);

         problem_threaded_worker_t threaded_worker(5, 1);

         std::vector<std::future<all_solutions_t>> solutions_futures;

         for (const auto& sub_problem : a_problem.create_initial_sub_problems())
         {
            auto new_future = threaded_worker.add_work(sub_problem, 0, [&threaded_worker , &a_problem, &an_empty_solution, &mt_progress](SUB_PROBLEM_T sub_problem, size_t a_depth) -> all_solutions_t
            {
               solve_context_t ctx(threaded_worker, a_problem, mt_progress, a_depth);
               try
               {
                  if (ctx.progress.is_progress_stopped()) {
                     ctx.threaded_worker.stop(true);
                  }
                  else {
                     solve_sub_problem_with_tile(sub_problem, an_empty_solution, ctx);
                  }
               }
               catch (...)
               {
                  ctx.threaded_worker.stop(true);
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

   private:
      using multi_thread_progress_t = dak::utility::multi_thread_progress_t;
      using per_thread_progress_t = dak::utility::per_thread_progress_t;
      using problem_threaded_worker_t = dak::utility::threaded_worker_t<SUB_PROBLEM_T, all_solutions_t>;

      ////////////////////////////////////////////////////////////////////////////
      //
      // Solve the placement of all given tiles.

      struct solve_context_t
      {
         solve_context_t(
            problem_threaded_worker_t& a_threaded_worker,
            const PROBLEM_T& a_problem,
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
         const PROBLEM_T&           problem;
         per_thread_progress_t      progress;
         size_t                     recursion_depth;
         all_solutions_t            solutions;
      };

      ////////////////////////////////////////////////////////////////////////////
      //
      // Keeper of all solutions.

      // Add a solution, we assume it has been already normalized.
      static void add_solution(all_solutions_t& all_solutions, const SOLUTION_T& a_solution)
      {
         auto it = all_solutions.find(a_solution);
         if (it != all_solutions.end()) {
            const_cast<SOLUTION_T&>(*it).add_similar_solution(a_solution);
         }
         else {
            all_solutions.insert(a_solution);
         }
      }

      // Add many solutions, we assume they have been already normalized.
      static void add_solutions(all_solutions_t& all_solutions, all_solutions_t& other_solutions)
      {
         for (auto& solution : other_solutions)
            add_solution(all_solutions, solution);
      }


      static void solve_recursion(
         const SUB_PROBLEM_T& a_sub_problem,
         const SOLUTION_T& a_partial_solution,
         const SOLUTION_PART_T& a_part,
         solve_context_t& a_ctx)
      {
         SOLUTION_T new_partial = a_partial_solution;
         new_partial.add_part(a_part);

         if (a_ctx.problem.has_more_sub_problems(a_sub_problem))
         {
            solve_partial(a_sub_problem, new_partial, a_ctx);
         }
         else if (a_ctx.problem.is_solution_valid(new_partial))
         {
            new_partial.normalize();
            add_solution(a_ctx.solutions, new_partial);
         }
      }

      static void solve_sub_problem_with_tile(
         const SUB_PROBLEM_T& a_sub_problem,
         const SOLUTION_T& partial_solution,
         solve_context_t& a_ctx)
      {
         a_ctx.progress.progress(1);

         const auto potential_parts = a_ctx.problem.get_sub_problem_potential_parts(a_sub_problem, partial_solution);
         for (const auto& part : potential_parts)
         {
            if (partial_solution.is_compatible(part))
            {
               solve_recursion(a_sub_problem, partial_solution, part, a_ctx);
            }
         }
      }


      static void solve_partial(
         const SUB_PROBLEM_T& a_sub_problem,
         const SOLUTION_T& partial_solution,
         solve_context_t& a_ctx)
      {
         std::vector<std::future<all_solutions_t>> solutions_futures;

         const auto sub_sub_problems = a_ctx.problem.create_sub_problems(a_sub_problem, partial_solution);
         for (const SUB_PROBLEM_T& sub_sub_problem : sub_sub_problems)
         {
            #ifndef TANTRIX_DO_NOT_MULTI_THREAD
            // Avoid queuing sub-sub-problem that are too simple or if there are already enough
            // parallel tasks, to avoid overflowing the work queue.
            if (!partial_solution.is_almost_done(a_ctx.problem))
            {
            // Note: a_progress is passed by value so that a new one will be created for the sub-thread.
            auto new_future = a_ctx.threaded_worker.add_work(sub_sub_problem, a_ctx.recursion_depth, [&a_ctx, partial_solution](SUB_PROBLEM_T a_sub_sub_problem, size_t a_depth) -> all_solutions_t
            {
               solve_context_t ctx(a_ctx);
               try
               {
                  ctx.recursion_depth = a_depth;
                  if (ctx.progress.is_progress_stopped()) {
                     ctx.threaded_worker.stop(true);
                  }
                  else {
                     solve_sub_problem_with_tile(a_sub_sub_problem, partial_solution, ctx);
                  }
               }
               catch (...)
               {
                  ctx.threaded_worker.stop(true);
               }
               return ctx.solutions;
            });
            solutions_futures.emplace_back(std::move(new_future));
            }
            else
            #endif
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

   };
}
