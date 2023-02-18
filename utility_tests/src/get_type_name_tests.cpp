#include <CppUnitTest.h>

#include <dak/utility/type_info.h>
#include <dak/utility/tests/helpers.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace dak::utility::tests
{		
   TEST_CLASS(get_type_name_tests)
	{
	public:
		TEST_METHOD(get_type_name_test)
		{
         Assert::AreEqual<text_t>(L"bool",     get_type_name<bool>());
         Assert::AreEqual<text_t>(L"char",     get_type_name<char>());
         Assert::AreEqual<text_t>(L"wchar_t",  get_type_name<wchar_t>());
         Assert::AreEqual<text_t>(L"int8_t",   get_type_name<int8_t>());
         Assert::AreEqual<text_t>(L"int16_t",  get_type_name<int16_t>());
         Assert::AreEqual<text_t>(L"int32_t",  get_type_name<int32_t>());
         Assert::AreEqual<text_t>(L"int64_t",  get_type_name<int64_t>());
         Assert::AreEqual<text_t>(L"uint8_t",  get_type_name<uint8_t>());
         Assert::AreEqual<text_t>(L"uint16_t", get_type_name<uint16_t>());
         Assert::AreEqual<text_t>(L"uint32_t", get_type_name<uint32_t>());
         Assert::AreEqual<text_t>(L"uint64_t", get_type_name<uint64_t>());
         Assert::AreEqual<text_t>(L"float",    get_type_name<float>());
         Assert::AreEqual<text_t>(L"double",   get_type_name<double>());
      }
   };
}
