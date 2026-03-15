#include "dak/solver/solve.h"
#include "dak/utility/progress.h"

#include <algorithm>

#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace dak::solver;
using namespace dak::utility;

namespace dak::solver::tests
{
   struct test_sub_problem_t : sub_problem_t
   {
      int value_to_solve;
      std::vector<int> other_values;
   };

   struct test_solution_part_t : solution_part_t
   {
      int value;
   };

   struct test_solution_t : solution_t
   {
      std::vector<int> values;

      ptr_t clone() const override
      {
         return std::make_shared<test_solution_t>(*this);
      }

      void add_part(const solution_part_t::ptr_t& a_part) override
      {
         auto part = std::dynamic_pointer_cast<test_solution_part_t>(a_part);
         if (!part)
            return;
         values.push_back(part->value);
      }

      void normalize()
      {
         std::sort(values.begin(), values.end());
      }

      bool is_compatible(const solution_part_t::ptr_t& a_part) const
      {
         auto part = std::dynamic_pointer_cast<test_solution_part_t>(a_part);
         if (!part)
            return {};

         return (values.size() % 2) == (part->value % 2);
      }

      bool is_valid() const
      {
         return values.size() == 5;
      }

      bool is_almost_done() const
      {
         return values.size() >= 4;
      }

      std::strong_ordering operator<=>(const solution_t& another_solution) const
      {
         auto other = dynamic_cast<const test_solution_t*>(&another_solution);
         if (!other)
            return std::strong_ordering::less;

         return values <=> other->values;
      }

   };

   struct test_problem_t : public problem_t
   {
      test_problem_t() = default;

      std::vector<sub_problem_t::ptr_t> create_initial_sub_problems() const override
      {
         test_sub_problem_t sub;
         sub.value_to_solve = 0;
         sub.other_values = { 1, 2, 3, 4 };
         return std::vector<sub_problem_t::ptr_t>({ std::make_shared<test_sub_problem_t>(sub) });
      }

      std::vector<sub_problem_t::ptr_t> create_sub_problems(
         const sub_problem_t::ptr_t& a_current_sub_problem,
         const solution_t::ptr_t& a_partial_solution) const override
      {
         auto current = std::dynamic_pointer_cast<test_sub_problem_t>(a_current_sub_problem);
         if (!current)
            return {};

         std::vector<sub_problem_t::ptr_t> sub_problems;
         std::vector<int> other_values = current->other_values;
         for (size_t i = 0; i < other_values.size(); ++i) {
            test_sub_problem_t sub;
            sub.value_to_solve = other_values[0];
            sub.other_values = { other_values.begin() + 1, other_values.end() };
            sub_problems.emplace_back(std::make_shared<test_sub_problem_t>(sub));
            std::rotate(other_values.begin(), other_values.begin() + 1, other_values.end());
         }
         return sub_problems;
      }

      bool has_more_sub_problems(const sub_problem_t::ptr_t& a_current_sub_problem) const override
      {
         auto current = std::dynamic_pointer_cast<test_sub_problem_t>(a_current_sub_problem);
         if (!current)
            return false;

         return current->other_values.size() > 0;
      }

      std::vector<solution_part_t::ptr_t> get_sub_problem_potential_parts(
         const sub_problem_t::ptr_t& a_current_sub_problem,
         const solution_t::ptr_t& a_partial_solution) const override
      {
         auto current = std::dynamic_pointer_cast<test_sub_problem_t>(a_current_sub_problem);
         if (!current)
            return {};

         std::vector<solution_part_t::ptr_t> parts;
         test_solution_part_t part;
         part.value = current->value_to_solve;
         parts.emplace_back(std::make_shared<test_solution_part_t>(part));
         return parts;
      }

      // Verify if the solution satisfies the initial problem.
      bool is_solution_valid(const solution_t::ptr_t& a_solution) const
      {
         auto test_solution = std::dynamic_pointer_cast<test_solution_t>(a_solution);
         if (!test_solution)
            return false;

         return test_solution->values.size() == 5;
      }

   };

	TEST_CLASS(solve_tests)
	{
	public:
		
		TEST_METHOD(solve_test_problem)
		{
         auto problem = std::make_shared<test_problem_t>();
         auto starting_solution = std::make_shared<test_solution_t>();

         struct dummy_progress_t : progress_t
         {
            void update_progress(size_t a_total_count_so_far) override {}
         };
         dummy_progress_t progress;
         auto solutions = solve(problem, starting_solution, progress);

         Assert::AreEqual<size_t>(3, solutions.size());
		}
   };
}
