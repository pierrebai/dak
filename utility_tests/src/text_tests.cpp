#include <dak/utility/text.h>

#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace dak::utility;

namespace dak::utility::tests
{
   TEST_CLASS(utility_text_tests)
   {
   public:

      TEST_METHOD(utility_text_convert)
      {
         Assert::AreEqual(std::wstring(L"Hello"), convert("Hello"));
         Assert::AreEqual(std::wstring(L"Hello"), convert(std::string("Hello")));
      }

      TEST_METHOD(utility_text_localize)
      {
         Assert::AreEqual<std::string>(std::string("Hello"), L::t("Hello"));
         Assert::AreEqual<std::wstring>(std::wstring(L"Hello"), L::t(L"Hello"));
      }
   };
}
