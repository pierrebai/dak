#include <CppUnitTest.h>

#include <dak/any_op/all.h>
#include <dak/any_op/tests/helpers.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace dak::any_op;

namespace dak::any_op::tests
{		
   TEST_CLASS(is_compatible_op_tests)
	{
	public:
		TEST_METHOD(is_compatible_test)
		{
         register_ops();

         Assert::IsTrue(is_compatible<int32_t, bool>());
         Assert::IsTrue(is_compatible<int32_t, char>());
         Assert::IsTrue(is_compatible<int32_t, wchar_t>());
         Assert::IsTrue(is_compatible<int32_t, int8_t>());
         Assert::IsTrue(is_compatible<int32_t, int16_t>());
         Assert::IsTrue(is_compatible<int32_t, int32_t>());
         Assert::IsTrue(is_compatible<int32_t, int64_t>());
         Assert::IsTrue(is_compatible<int32_t, uint8_t>());
         Assert::IsTrue(is_compatible<int32_t, uint16_t>());
         Assert::IsTrue(is_compatible<int32_t, uint32_t>());
         Assert::IsTrue(is_compatible<int32_t, uint64_t>());
         Assert::IsTrue(is_compatible<int32_t, float>());
         Assert::IsTrue(is_compatible<int32_t, double>());

         Assert::IsTrue(is_compatible<int64_t, bool>());
         Assert::IsTrue(is_compatible<int64_t, char>());
         Assert::IsTrue(is_compatible<int64_t, wchar_t>());
         Assert::IsTrue(is_compatible<int64_t, int8_t>());
         Assert::IsTrue(is_compatible<int64_t, int16_t>());
         Assert::IsTrue(is_compatible<int64_t, int32_t>());
         Assert::IsTrue(is_compatible<int64_t, int64_t>());
         Assert::IsTrue(is_compatible<int64_t, uint8_t>());
         Assert::IsTrue(is_compatible<int64_t, uint16_t>());
         Assert::IsTrue(is_compatible<int64_t, uint32_t>());
         Assert::IsTrue(is_compatible<int64_t, uint64_t>());
         Assert::IsTrue(is_compatible<int64_t, float>());
         Assert::IsTrue(is_compatible<int64_t, double>());

         Assert::IsTrue(is_compatible<double, bool>());
         Assert::IsTrue(is_compatible<double, char>());
         Assert::IsTrue(is_compatible<double, wchar_t>());
         Assert::IsTrue(is_compatible<double, int8_t>());
         Assert::IsTrue(is_compatible<double, int16_t>());
         Assert::IsTrue(is_compatible<double, int32_t>());
         Assert::IsTrue(is_compatible<double, int64_t>());
         Assert::IsTrue(is_compatible<double, uint8_t>());
         Assert::IsTrue(is_compatible<double, uint16_t>());
         Assert::IsTrue(is_compatible<double, uint32_t>());
         Assert::IsTrue(is_compatible<double, uint64_t>());
         Assert::IsTrue(is_compatible<double, float>());
         Assert::IsTrue(is_compatible<double, double>());

         Assert::IsTrue(is_compatible<bool, bool>());
         Assert::IsTrue(is_compatible<bool, char>());
         Assert::IsTrue(is_compatible<bool, wchar_t>());
         Assert::IsTrue(is_compatible<bool, int8_t>());
         Assert::IsTrue(is_compatible<bool, int16_t>());
         Assert::IsTrue(is_compatible<bool, int32_t>());
         Assert::IsTrue(is_compatible<bool, int64_t>());
         Assert::IsTrue(is_compatible<bool, uint8_t>());
         Assert::IsTrue(is_compatible<bool, uint16_t>());
         Assert::IsTrue(is_compatible<bool, uint32_t>());
         Assert::IsTrue(is_compatible<bool, uint64_t>());
         Assert::IsTrue(is_compatible<bool, float>());
         Assert::IsTrue(is_compatible<bool, double>());
      }
   };
}
