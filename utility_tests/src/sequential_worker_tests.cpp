#include <dak/utility/sequential_worker.h>

#include <CppUnitTest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace dak::utility::tests
{
	TEST_CLASS(sequential_worker_tests)
	{
	public:
		
      TEST_METHOD(test_sequential_work)
      {
         sequential_worker_t<size_t, size_t> worker;

         std::vector<std::future<size_t>> future_results;

         for (size_t i = 0; i < 10; ++i)
            future_results.emplace_back(worker.add_work(i, [](size_t a_value)
            {
               return a_value + 7;
            }));

         size_t total = 0;
         for (auto& future_val : future_results)
            total += worker.wait_for(future_val);

         const size_t expected_total = 7 * future_results.size()
                                     + (future_results.size() * (future_results.size() - 1)) / 2;
         Assert::AreEqual<size_t>(expected_total, total);
		}
	};
}
