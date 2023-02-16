#include <dak/utility/text.h>

#include <CppUnitTest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace dak::utility;

namespace dak::utility::tests
{
   TEST_CLASS(utility_text_tests)
   {
   public:

      TEST_METHOD(utility_text_widen_text)
      {
         Assert::AreEqual(std::wstring(L"Hello"), widen_text("Hello"));
         Assert::AreEqual(std::wstring(L"Hello"), widen_text(std::string("Hello")));
      }

      TEST_METHOD(utility_text_narrow_text)
      {
         Assert::AreEqual(std::string("Hello"), narrow_text(L"Hello"));
         Assert::AreEqual(std::string("Hello"), narrow_text(std::wstring(L"Hello")));
      }

      TEST_METHOD(utility_text_localize)
      {
         Assert::AreEqual<std::string>(std::string("Hello"), L::t("Hello"));
         Assert::AreEqual<std::wstring>(std::wstring(L"Hello"), L::t(L"Hello"));
      }
   };
}
