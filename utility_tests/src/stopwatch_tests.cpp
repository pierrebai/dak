#include <dak/utility/stopwatch.h>

#include <CppUnitTest.h>

#include <thread>
#include <chrono>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std::chrono_literals;

namespace dak::utility::tests
{
	TEST_CLASS(stopwatch_tests)
	{
	public:
		
		TEST_METHOD(test_stopwatch)
		{
         stopwatch_t stopwatch;

         std::this_thread::sleep_for(1ms);

         Assert::AreNotEqual(0., stopwatch.elapsed());

         const double t1 = stopwatch.elapsed();
         std::this_thread::sleep_for(1ms);
         const double t2 = stopwatch.elapsed();

         Assert::AreNotEqual(t1, t2);

         stopwatch.stop();

		}

      TEST_METHOD(test_stopwatch_time_buffer)
      {
         double time = 0;
         stopwatch_t stopwatch(time);

         std::this_thread::sleep_for(1ms);

         stopwatch.elapsed();
         Assert::AreNotEqual(0., time);

         stopwatch.elapsed();
         const double t1 = time;
         std::this_thread::sleep_for(1ms);
         stopwatch.elapsed();
         const double t2 = time;

         Assert::AreNotEqual(t1, t2);

         // Stop updates the time buffer a last time and after stop,
         // the time buffer is no longer updated by the stopwatch.
         stopwatch.stop();

         stopwatch.elapsed();
         const double t3 = time;
         std::this_thread::sleep_for(1ms);
         stopwatch.elapsed();
         const double t4 = time;

         Assert::AreEqual(t3, t4);

      }

      TEST_METHOD(test_stopwatch_formatted_buffer)
      {
         std::string narrow_time;
         std::wstring wide_time;
         stopwatch_t stopwatch(nullptr, &narrow_time, &wide_time);

         std::this_thread::sleep_for(1ms);

         stopwatch.elapsed();
         Assert::AreNotEqual<std::string>("", narrow_time);
         Assert::AreNotEqual<std::wstring>(L"", wide_time);

         stopwatch.elapsed();
         std::string nt1 = narrow_time;
         std::wstring wt1 = wide_time;
         std::this_thread::sleep_for(3ms);
         stopwatch.elapsed();
         std::string nt2 = narrow_time;
         std::wstring wt2 = wide_time;

         Assert::AreNotEqual(nt1, nt2);
         Assert::AreNotEqual(wt1, wt2);

         // Stop updates the time buffer a last time and after stop,
         // the time buffer is no longer updated by the stopwatch.
         stopwatch.stop();

         stopwatch.elapsed();
         std::string nt3 = narrow_time;
         std::wstring wt3 = wide_time;
         std::this_thread::sleep_for(3ms);
         stopwatch.elapsed();
         std::string nt4 = narrow_time;
         std::wstring wt4 = wide_time;

         Assert::AreEqual(nt3, nt4);
         Assert::AreEqual(wt3, wt4);
      }

      TEST_METHOD(test_stopwatch_long_time_buffer)
      {
         double time = 0;
         stopwatch_t stopwatch(time);

         stopwatch.set_elapsed(300.5);
         Assert::AreEqual(300.5, time);

         stopwatch.set_elapsed(30000.5);
         Assert::AreEqual(30000.5, time);
      }

      TEST_METHOD(test_stopwatch_long_time_formatted_buffer)
      {
         std::string narrow_time;
         std::wstring wide_time;
         stopwatch_t stopwatch(nullptr, &narrow_time, &wide_time);

         stopwatch.set_elapsed(300.5);
         Assert::AreEqual<std::string>("5m 0s 500ms", narrow_time);
         Assert::AreEqual<std::wstring>(L"5m 0s 500ms", wide_time);

         stopwatch.set_elapsed(7265.5);
         Assert::AreEqual<std::string>("2h 1m 5s 500ms", narrow_time);
         Assert::AreEqual<std::wstring>(L"2h 1m 5s 500ms", wide_time);

      }
   };
}
