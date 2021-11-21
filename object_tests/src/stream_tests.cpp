#include "CppUnitTest.h"

#include "dak/object/ref_stream.h"
#include "dak/object/timeline.h"
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
         ss << voc::rock;
         Assert::AreEqual(text_t(L"rock"), ss.str());

         ss.clear();
         ss.str(L"");
         dict_t d1;
         ss << d1;
         Assert::AreEqual(text_t(L"{\n}"), ss.str());

         ss.clear();
         ss.str(L"");
         dict_t d2;
         d2[voc::rock] = 3;
         ss << d2;
         Assert::AreEqual(text_t(L"{\nrock : 3 ,\n}"), ss.str());

         ss.clear();
         ss.str(L"");
         array_t a1;
         ss << a1;
         Assert::AreEqual(text_t(L"[\n]"), ss.str());

         ss.clear();
         ss.str(L"");
         array_t a2;
         a2.grow() = 3;
         a2.grow() = 5;
         a2.grow() = 7;
         ss << a2;
         Assert::AreEqual(text_t(L"[\n3 ,\n5 ,\n7 ,\n]"), ss.str());

         ss.clear();
         ss.str(L"");
         auto o1 = object_t::make();
         auto o2 = object_t::make();
         {
            timeline_t undo_redo;
            transaction_t tr1;

            auto& mo1 = o1->modify(tr1);
            mo1[voc::child] = o2;

            auto& mo2 = o2->modify(tr1);
            array_t& a3 = mo2[voc::after];

            a3[0] = true;
            a3[1] = o1;

            tr1.commit(undo_redo);
         }
         ref_stream_t(ss) << o1;
         Assert::AreEqual(text_t(L"ref 1 {\nchild : ref 2 {\nafter : [\n1 ,\nref -1 ,\n] ,\n} ,\n}"), ss.str());
      }
   };
}
