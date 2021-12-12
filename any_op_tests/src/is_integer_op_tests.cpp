#include <CppUnitTest.h>

#include <dak/any_op/all.h>
#include <dak/any_op/tests/helpers.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace dak::any_op;

namespace dak::any_op::tests
{		
   TEST_CLASS(is_integer_op_tests)
	{
	public:
		TEST_METHOD(is_integer_test)
		{
         register_ops();

         Assert::IsFalse(is_integer<bool>());
         Assert::IsFalse(is_integer<char>());
         Assert::IsFalse(is_integer<wchar_t>());
         Assert::IsTrue(is_integer<int8_t>());
         Assert::IsTrue(is_integer<int16_t>());
         Assert::IsTrue(is_integer<int32_t>());
         Assert::IsTrue(is_integer<int64_t>());
         Assert::IsFalse(is_integer<uint8_t>());
         Assert::IsFalse(is_integer<uint16_t>());
         Assert::IsFalse(is_integer<uint32_t>());
         Assert::IsFalse(is_integer<uint64_t>());
         Assert::IsFalse(is_integer<float>());
         Assert::IsFalse(is_integer<double>());
      }
   };
}
