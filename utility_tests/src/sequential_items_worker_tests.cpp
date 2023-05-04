#include <dak/utility/sequential_items_worker.h>

#include <CppUnitTest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace dak::utility::tests
{
   struct adder_t : work_item_t
   {
      size_t value = 0;

      adder_t(size_t a_value) : value(a_value) {}
      void execute() override { value += 7; }
      static auto make(size_t a_value) { return std::make_shared<adder_t>(a_value); }
   };

	TEST_CLASS(sequential_items_worker_tests)
	{
	public:
		
      TEST_METHOD(test_sequential_work)
      {
         using item_ptr_t = sequential_items_worker_t::item_ptr_t;
         sequential_items_worker_t worker;

         std::vector<std::future<item_ptr_t>> future_results;

         for (size_t i = 0; i < 10; ++i)
            future_results.emplace_back(worker.add_work(adder_t::make(i)));

         size_t total = 0;
         for (auto& item : future_results)
            if (auto adder = std::dynamic_pointer_cast<adder_t>(worker.wait_for(item)))
               total += adder->value;

         const size_t expected_total = 7 * future_results.size()
                                     + (future_results.size() * (future_results.size() - 1)) / 2;
         Assert::AreEqual<size_t>(expected_total, total);
		}
	};
}
