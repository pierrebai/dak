#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <compare>
#include <memory>

namespace dak::solver
{
   struct problem_t;

   ////////////////////////////////////////////////////////////////////////////
   //
   // Part of a solution, we build a solution by solving and adding parts.

   struct solution_part_t
   {
      using ptr_t = std::shared_ptr<solution_part_t>;

      solution_part_t() = default;
      virtual ~solution_part_t() = default;

      // Compare solution parts.
      auto operator<=>(const solution_part_t&) const = default;
   };

   ////////////////////////////////////////////////////////////////////////////
   //
   // Solution to a problem.

   struct solution_t
   {
      using ptr_t = std::shared_ptr<solution_t>;

      // Create a new solution.
      solution_t() = default;
      virtual ~solution_t() = default;

      // Make a copy of this solution.
      virtual ptr_t clone() const = 0;

      // Add a part of the solution to this solution.
      virtual void add_part(const solution_part_t::ptr_t& a_part) = 0;

      // Normalize the solution so that any other identical solutions will
      // have the same set of positions and orientation.
      virtual void normalize() = 0;

      // Verify if the solution part is compatible with the solution so far.
      virtual bool is_compatible(const solution_part_t::ptr_t& a_part) const = 0;

      // Check if the solution has no invalid holes or borders.
      // (Hole with more than 3 sides or having more than two of the same color.)
      virtual bool is_valid() const = 0;

      // Nearing completion, stop spawning threads.
      virtual bool is_almost_done(const std::shared_ptr<problem_t>& a_problem) const = 0;

      // Compare solutions.
      virtual std::strong_ordering operator<=>(const solution_t& another_solution) const = 0;
   };
}
