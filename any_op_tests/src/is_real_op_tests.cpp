#include <CppUnitTest.h>

#include <dak/any_op/all.h>
#include <dak/any_op/tests/helpers.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace dak::any_op;

namespace dak::any_op::tests
{		
   TEST_CLASS(is_real_op_tests)
	{
	public:
		TEST_METHOD(is_real_test)
		{
         register_ops();

         Assert::IsFalse(is_real<bool>());
         Assert::IsFalse(is_real<char>());
         Assert::IsFalse(is_real<wchar_t>());
         Assert::IsFalse(is_real<int8_t>());
         Assert::IsFalse(is_real<int16_t>());
         Assert::IsFalse(is_real<int32_t>());
         Assert::IsFalse(is_real<int64_t>());
         Assert::IsFalse(is_real<uint8_t>());
         Assert::IsFalse(is_real<uint16_t>());
         Assert::IsFalse(is_real<uint32_t>());
         Assert::IsFalse(is_real<uint64_t>());
         Assert::IsTrue(is_real<float>());
         Assert::IsTrue(is_real<double>());
      }
   };
}
