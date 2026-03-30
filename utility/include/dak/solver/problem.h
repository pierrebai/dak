#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <dak/solver/solution.h>

#include <vector>


namespace dak::solver
{
   ////////////////////////////////////////////////////////////////////////////
   //
   // Problem, provides sub-problems to the solver.

   struct problem_t
   {
      using ptr_t = std::shared_ptr<problem_t>;
      virtual ~problem_t() = default;
   };

   ////////////////////////////////////////////////////////////////////////////
   //
   // Example problem, declares what is expected by the solver.

   struct example_problem_t : problem_t
   {
      // Sub problem
      struct sub_problem_t
      {
         sub_problem_t() = default;
         ~sub_problem_t() = default;
      };
      
      // Create a problem.
      example_problem_t() = default;
      ~example_problem_t() = default;

      // Verify if the problem is valid.
      bool is_valid() const;

      // Solver interaction.

      // Create the initial list of sub-problems to solve.
      std::vector<sub_problem_t> create_initial_sub_problems() const;

      // Create sub-problems from a given sub-problem that was solved.
      std::vector<sub_problem_t> create_sub_problems(
         const sub_problem_t& a_current_sub_problem,
         const example_solution_t& a_partial_solution) const;

      // Verify if there are more sub-problems to be created from the given sub-problem.
      bool has_more_sub_problems(const sub_problem_t& a_current_sub_problem) const;

      // Retrieve all potential solution parts that could solve the problem at given sub-problem and partial solution.
      std::vector<example_solution_t::part_t> get_sub_problem_potential_parts(
         const sub_problem_t& a_current_sub_problem,
         const example_solution_t& a_partial_solution) const;

      // Verify if the solution satisfies the initial problem.
      bool is_solution_valid(const example_solution_t& a_solution) const;
   };

}

