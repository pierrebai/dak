#include <CppUnitTest.h>

#include <dak/any_op/all.h>
#include <dak/any_op/tests/helpers.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace dak::any_op;

namespace dak::any_op::tests
{		
   TEST_CLASS(convert_op_tests)
	{
	public:
      TEST_METHOD(convert_test)
      {
         register_ops();

         Assert::AreEqual<int32_t>(1,  convert<int32_t, bool>(true));
         Assert::AreEqual<int32_t>(97, convert<int32_t, char>('a'));
         Assert::AreEqual<int32_t>(98, convert<int32_t, wchar_t>(L'b'));
         Assert::AreEqual<int32_t>(2,  convert<int32_t, int8_t>(2));
         Assert::AreEqual<int32_t>(3,  convert<int32_t, int16_t>(3));
         Assert::AreEqual<int32_t>(4,  convert<int32_t, int32_t>(4));
         Assert::AreEqual<int32_t>(5,  convert<int32_t, int64_t>(5));
         Assert::AreEqual<int32_t>(6,  convert<int32_t, uint8_t>(6));
         Assert::AreEqual<int32_t>(7,  convert<int32_t, uint16_t>(7));
         Assert::AreEqual<int32_t>(8,  convert<int32_t, uint32_t>(8));
         Assert::AreEqual<int32_t>(9,  convert<int32_t, uint64_t>(9));
         Assert::AreEqual<int32_t>(10, convert<int32_t, float>(10.f));
         Assert::AreEqual<int32_t>(11, convert<int32_t, double>(11.));

         Assert::AreEqual<int64_t>(1,  convert<int64_t, bool>(true));
         Assert::AreEqual<int64_t>(65, convert<int64_t, char>('A'));
         Assert::AreEqual<int64_t>(66, convert<int64_t, wchar_t>(L'B'));
         Assert::AreEqual<int64_t>(2,  convert<int64_t, int8_t>(2));
         Assert::AreEqual<int64_t>(3,  convert<int64_t, int16_t>(3));
         Assert::AreEqual<int64_t>(4,  convert<int64_t, int32_t>(4));
         Assert::AreEqual<int64_t>(5,  convert<int64_t, int64_t>(5));
         Assert::AreEqual<int64_t>(6,  convert<int64_t, uint8_t>(6));
         Assert::AreEqual<int64_t>(7,  convert<int64_t, uint16_t>(7));
         Assert::AreEqual<int64_t>(8,  convert<int64_t, uint32_t>(8));
         Assert::AreEqual<int64_t>(9,  convert<int64_t, uint64_t>(9));
         Assert::AreEqual<int64_t>(10, convert<int64_t, float>(10.f));
         Assert::AreEqual<int64_t>(11, convert<int64_t, double>(11.));

         Assert::AreEqual<double>(1.,  convert<double, bool>(true));
         Assert::AreEqual<double>(65., convert<double, char>('A'));
         Assert::AreEqual<double>(66., convert<double, wchar_t>(L'B'));
         Assert::AreEqual<double>(2.,  convert<double, int8_t>(2));
         Assert::AreEqual<double>(3.,  convert<double, int16_t>(3));
         Assert::AreEqual<double>(4.,  convert<double, int32_t>(4));
         Assert::AreEqual<double>(5.,  convert<double, int64_t>(5));
         Assert::AreEqual<double>(6.,  convert<double, uint8_t>(6));
         Assert::AreEqual<double>(7.,  convert<double, uint16_t>(7));
         Assert::AreEqual<double>(8.,  convert<double, uint32_t>(8));
         Assert::AreEqual<double>(9.,  convert<double, uint64_t>(9));
         Assert::AreEqual<double>(10., convert<double, float>(10.f));
         Assert::AreEqual<double>(11., convert<double, double>(11.));

         Assert::AreEqual<bool>(true, convert<bool, bool>(true));
         Assert::AreEqual<bool>(true, convert<bool, char>('A'));
         Assert::AreEqual<bool>(true, convert<bool, wchar_t>(L'B'));
         Assert::AreEqual<bool>(true, convert<bool, int8_t>(2));
         Assert::AreEqual<bool>(true, convert<bool, int16_t>(3));
         Assert::AreEqual<bool>(true, convert<bool, int32_t>(4));
         Assert::AreEqual<bool>(true, convert<bool, int64_t>(5));
         Assert::AreEqual<bool>(true, convert<bool, uint8_t>(6));
         Assert::AreEqual<bool>(true, convert<bool, uint16_t>(7));
         Assert::AreEqual<bool>(true, convert<bool, uint32_t>(8));
         Assert::AreEqual<bool>(true, convert<bool, uint64_t>(9));
         Assert::AreEqual<bool>(true, convert<bool, float>(10.f));
         Assert::AreEqual<bool>(true, convert<bool, double>(11.));
         Assert::AreEqual<bool>(true, convert<bool, text_t>(L"hello"));

         Assert::AreEqual<bool>(false, convert<bool, bool>(false));
         Assert::AreEqual<bool>(false, convert<bool, char>('\0'));
         Assert::AreEqual<bool>(false, convert<bool, wchar_t>(L'\0'));
         Assert::AreEqual<bool>(false, convert<bool, int8_t>(0));
         Assert::AreEqual<bool>(false, convert<bool, int16_t>(0));
         Assert::AreEqual<bool>(false, convert<bool, int32_t>(0));
         Assert::AreEqual<bool>(false, convert<bool, int64_t>(0));
         Assert::AreEqual<bool>(false, convert<bool, uint8_t>(0));
         Assert::AreEqual<bool>(false, convert<bool, uint16_t>(0));
         Assert::AreEqual<bool>(false, convert<bool, uint32_t>(0));
         Assert::AreEqual<bool>(false, convert<bool, uint64_t>(0));
         Assert::AreEqual<bool>(false, convert<bool, float>(0.f));
         Assert::AreEqual<bool>(false, convert<bool, double>(0.));
         Assert::AreEqual<bool>(false, convert<bool, text_t>(text_t()));
         Assert::AreEqual<bool>(false, convert<bool, str_ptr_t>(nullptr));
         Assert::AreEqual<bool>(false, convert<bool, str_ptr_t>(L""));

         //Assert::AreEqual<array_t>(convert<array_t, dict_t>());
      }
   };
}
