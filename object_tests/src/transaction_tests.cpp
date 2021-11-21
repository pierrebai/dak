#include "CppUnitTest.h"

#include "dak/object/object.h"
#include "dak/object/transaction.h"
#include "dak/object/voc.h"
#include "dak/object/tests/helpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace dak::object::tests
{		
   using namespace voc;

   TEST_CLASS(transaction_tests)
   {
   public:

      TEST_METHOD(transaction_base)
      {
         auto ro1 = object_t::make();

         commited_transactions_t undo_redo;

         {
            transaction_t t1;

            auto& o1 = ro1->modify(t1);

            o1[rock] = 3;
            o1[pebble] = 4;
            o1[sand] = 5.0;
            o1[hello] = L"6";
            o1[world] = voc::rock;

            t1.commit(undo_redo);
         }

         verify_object(ro1);

         for (int i = 0; i < 3; ++i)
         {
            undo_redo.undo();

            Assert::AreEqual<index_t>(0, ro1->size());

            undo_redo.redo();

            verify_object(ro1);
         }
      }

   private:
      void verify_object(const valid_ref_t<object_t>& object)
      {
         Assert::AreEqual<int32_t>(3, object[rock]);
         Assert::AreEqual<int64_t>(4, object[pebble]);
         Assert::AreEqual<double>(5.0, object[sand]);
         Assert::AreEqual<text_t>(L"6", object[hello]);
         Assert::AreEqual<name_t>(rock, object[world]);
      }
   };
}
