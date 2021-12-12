#include <CppUnitTest.h>

#include <dak/any_op/all.h>
#include <dak/any_op/tests/helpers.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace dak::any_op;

namespace dak::any_op::tests
{		
   TEST_CLASS(get_type_info_op_tests)
	{
	public:
		TEST_METHOD(get_type_info_test)
		{
         register_ops();

         Assert::IsTrue(typeid(bool) ==     get_type_info(L"bool"));
         Assert::IsTrue(typeid(char) ==     get_type_info(L"char"));
         Assert::IsTrue(typeid(wchar_t) ==  get_type_info(L"wchar_t"));
         Assert::IsTrue(typeid(int8_t) ==   get_type_info(L"int8_t"));
         Assert::IsTrue(typeid(int16_t) ==  get_type_info(L"int16_t"));
         Assert::IsTrue(typeid(int32_t) ==  get_type_info(L"int32_t"));
         Assert::IsTrue(typeid(int64_t) ==  get_type_info(L"int64_t"));
         Assert::IsTrue(typeid(uint8_t) ==  get_type_info(L"uint8_t"));
         Assert::IsTrue(typeid(uint16_t) == get_type_info(L"uint16_t"));
         Assert::IsTrue(typeid(uint32_t) == get_type_info(L"uint32_t"));
         Assert::IsTrue(typeid(uint64_t) == get_type_info(L"uint64_t"));
         Assert::IsTrue(typeid(float) ==    get_type_info(L"float"));
         Assert::IsTrue(typeid(double) ==   get_type_info(L"double"));
      }
   };
}
