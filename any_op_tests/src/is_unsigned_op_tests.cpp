#include <CppUnitTest.h>

#include <dak/any_op/all.h>
#include <dak/any_op/tests/helpers.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace dak::any_op;

namespace dak::any_op::tests
{		
   TEST_CLASS(is_unsigned_op_tests)
	{
	public:
		TEST_METHOD(is_unsigned_test)
		{
         register_ops();

         Assert::IsFalse(is_unsigned<bool>());
         Assert::IsFalse(is_unsigned<char>());
         Assert::IsFalse(is_unsigned<wchar_t>());
         Assert::IsFalse(is_unsigned<int8_t>());
         Assert::IsFalse(is_unsigned<int16_t>());
         Assert::IsFalse(is_unsigned<int32_t>());
         Assert::IsFalse(is_unsigned<int64_t>());
         Assert::IsTrue(is_unsigned<uint8_t>());
         Assert::IsTrue(is_unsigned<uint16_t>());
         Assert::IsTrue(is_unsigned<uint32_t>());
         Assert::IsTrue(is_unsigned<uint64_t>());
         Assert::IsFalse(is_unsigned<float>());
         Assert::IsFalse(is_unsigned<double>());
      }
   };
}
