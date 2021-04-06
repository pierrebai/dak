#include "CppUnitTest.h"

#include "dak/object/stream.h"
#include "dak/object/tests/helpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace dak::object::tests
{		
   TEST_CLASS(stream_tests)
   {
      public:

      TEST_METHOD(stream_base)
      {
         wstringstream ss;

         ss.clear();
         ss.str(L"");
         ss << namer_t(voc::get_root()) << voc::rock;
         Assert::AreEqual(text_t(L"rock"), ss.str());

         ss.clear();
         ss.str(L"");
         dict_t d1;
         ss << namer_t(voc::get_root()) << d1;
         Assert::AreEqual(text_t(L"{ }"), ss.str());

         ss.clear();
         ss.str(L"");
         dict_t d2;
         d2[voc::rock] = 3;
         ss << namer_t(voc::get_root()) << d2;
         Assert::AreEqual(text_t(L"{ rock : 3 , }"), ss.str());

         ss.clear();
         ss.str(L"");
         array_t a1;
         ss << namer_t(voc::get_root()) << a1;
         Assert::AreEqual(text_t(L"[ ]"), ss.str());

         ss.clear();
         ss.str(L"");
         array_t a2;
         a2.grow() = 3;
         a2.grow() = 5;
         a2.grow() = 7;
         ss << namer_t(voc::get_root()) << a2;
         Assert::AreEqual(text_t(L"[ 3 , 5 , 7 , ]"), ss.str());

      }
   };
}
