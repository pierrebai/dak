#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <compare>
#include <memory>

namespace dak::solver
{
   ////////////////////////////////////////////////////////////////////////////
   //
   // Solution to a problem.

   struct solution_t
   {
      using ptr_t = std::shared_ptr<solution_t>;
      virtual ~solution_t() = default;
   };

   ////////////////////////////////////////////////////////////////////////////
   //
   // Example solution to a problem.

   struct example_problem_t;

   struct example_solution_t : solution_t
   {
      // Part of a solution, we build a solution by solving and adding parts.

      struct part_t
      {
         part_t() = default;
         ~part_t() = default;

         // Compare solution parts.
         auto operator<=>(const part_t&) const = default;
      };

      // Create a new solution.
      example_solution_t() = default;
      ~example_solution_t() = default;

      // Add a part of the solution to this solution.
      void add_part(const part_t& a_part);

      // Normalize the solution so that any other identical solutions will
      // have the same set of positions and orientation.
      void normalize();

      // Verify if the solution part is compatible with the solution so far.
      bool is_compatible(const part_t& a_part) const;

      // Check if the solution has no invalid holes or borders.
      // (Hole with more than 3 sides or having more than two of the same color.)
      bool is_valid() const;

      // Nearing completion, stop spawning threads.
      bool is_almost_done(const example_problem_t& a_problem) const;

      // Compare solutions.
      std::strong_ordering operator<=>(const example_solution_t& another_solution) const;

      // Add a similar solution to this solution.
      void add_similar_solution(const solution_t& another_solution);
   };
}
