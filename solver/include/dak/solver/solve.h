#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <dak/solver/problem.h>
#include <dak/solver/solution.h>

#include <set>

namespace dak::utility
{
   struct progress_t;
}

namespace dak::solver
{
   struct problem_t;
   using progress_t = dak::utility::progress_t;

   ////////////////////////////////////////////////////////////////////////////
   //
   // Container of solutions.

   struct less_solution_ptr_t
   {
      bool operator()(const solution_t::ptr_t& a, const solution_t::ptr_t& b) const
      {
         if (!a)
            return bool(b);
         if (!b)
            return false;
         return (*a <=> *b) == std::strong_ordering::less;
      }
   };

   using all_solutions_t = std::set<solution_t::ptr_t, less_solution_ptr_t>;

   ////////////////////////////////////////////////////////////////////////////
   //
   // Solve the problem.

   all_solutions_t solve(
      const problem_t::ptr_t& a_problem,
      const solution_t::ptr_t& an_empty_solution,
      progress_t& a_progress);
}
