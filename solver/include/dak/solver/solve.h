#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <dak/solver/problem.h>
#include <dak/solver/solution.h>

#include <map>

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
   // Solve the problem.

   using all_solutions_t = std::map<solution_t::ptr_t, size_t>;

   all_solutions_t solve(
      const problem_t::ptr_t& a_problem,
      const solution_t::ptr_t& an_empty_solution,
      progress_t& a_progress);
}
