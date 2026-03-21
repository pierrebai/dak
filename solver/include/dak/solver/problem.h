#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <dak/solver/solution.h>

#include <memory>
#include <vector>


namespace dak::solver
{
   struct solution_t;

   ////////////////////////////////////////////////////////////////////////////
   //
   // Sub problem

   struct sub_problem_t
   {
      using ptr_t = std::shared_ptr<sub_problem_t>;

      sub_problem_t() = default;
      virtual ~sub_problem_t() = default;
   };

   ////////////////////////////////////////////////////////////////////////////
   //
   // Problem, provide sub-problems to the solver.

   struct problem_t
   {
      using ptr_t = std::shared_ptr<problem_t>;
      
      // Create a problem.
      problem_t() = default;
      virtual ~problem_t() = default;

      // Verify if the problem is valid.
      virtual bool is_valid() const = 0;

      // Solver interaction.

      // Create the initial list of sub-problems to solve.
      virtual std::vector<sub_problem_t::ptr_t> create_initial_sub_problems() const = 0;

      // Create sub-problems from a given sub-problem that was solved.
      virtual std::vector<sub_problem_t::ptr_t> create_sub_problems(
         const sub_problem_t::ptr_t& a_current_sub_problem,
         const solution_t::ptr_t& a_partial_solution) const = 0;

      // Verify if there are more sub-problems to be created from the given sub-problem.
      virtual bool has_more_sub_problems(const sub_problem_t::ptr_t& a_current_sub_problem) const = 0;

      // Retrieve all potential solution parts that could solve the problem at given sub-problem and partial solution.
      virtual std::vector<solver::solution_part_t::ptr_t> get_sub_problem_potential_parts(
         const sub_problem_t::ptr_t& a_current_sub_problem,
         const solution_t::ptr_t& a_partial_solution) const = 0;

      // Verify if the solution satisfies the initial problem.
      virtual bool is_solution_valid(const solution_t::ptr_t& a_solution) const = 0;
   };

}

