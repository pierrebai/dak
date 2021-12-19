#include <CppUnitTest.h>

#include <dak/object/value.h>
#include <dak/object/object.h>
#include <dak/object/voc.h>
#include <dak/object/tests/helpers.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace dak::any_op;

namespace dak::object::tests
{	
   TEST_CLASS(value_function_tests)
	{
	public:
      value_function_tests()
      {
         any_op::register_ops();
         register_object_ops();
      }

      TEST_METHOD(value_call_no_arg_no_return)
      {
         auto o = object_t::make();

         int call_count = 0;
         o[voc::rock] = std::function<void()>([&call_count]() { call_count += 1; });
         o[voc::rock]();
         o[voc::rock]();

         Assert::AreEqual<int>(2, call_count);
      }


      TEST_METHOD(value_call_two_args)
      {
         auto o = object_t::make();

         o[voc::rock] = std::function<int(int, int)>([](int a, int b) { return a+b; });
         int result = o[voc::rock].call<int>(1, 2);
         Assert::AreEqual<int>(3, result);
         Assert::AreEqual<int>(7, o[voc::rock].call<int>(10, -3));
      }
   };
}
