#include "CppUnitTest.h"

#include "dak/object/object.h"
#include "dak/object/timeline.h"
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

         timeline_t undo_redo;

         {
            transaction_t t1;

            fill_object(*ro1->modify(t1));

            t1.commit(undo_redo);
         }

         verify_object(ro1);

         {
            transaction_t t1;

            object_t& o1 = *ro1->modify(t1);

            o1[rock] = 7;

            t1.commit(undo_redo);
         }

         undo_redo.undo();

         {
            transaction_t t1;

            fill_object(*ro1->modify(t1));

            t1.commit(undo_redo);
         }

         undo_redo.undo();

         for (int i = 0; i < 3; ++i)
         {
            undo_redo.undo();

            Assert::AreEqual<index_t>(0, ro1->size());

            undo_redo.redo();

            verify_object(ro1);
         }

         undo_redo.undo();

         Assert::AreEqual<index_t>(0, ro1->size());

         undo_redo.undo();

         Assert::AreEqual<index_t>(0, ro1->size());

         undo_redo.undo();

         Assert::AreEqual<index_t>(0, ro1->size());

         undo_redo.redo();

         verify_object(ro1);

         undo_redo.redo();

         verify_object(ro1);

         undo_redo.redo();

         verify_object(ro1);
      }

      TEST_METHOD(transaction_cancel)
      {
         auto ro1 = object_t::make();

         timeline_t undo_redo;

         {
            transaction_t t1;

            fill_object(*ro1->modify(t1));

            t1.cancel();
         }

         Assert::AreEqual<index_t>(0, ro1->size());
      }

      TEST_METHOD(sub_transaction)
      {
         auto ro1 = object_t::make();

         timeline_t undo_redo;

         {
            transaction_t tr;

            {
               object_t& o1 = *ro1->modify(tr);
               o1[rock] = 5;
            }

            tr.commit(undo_redo);
         }

         Assert::AreEqual<int32_t>(5, (*ro1)[rock]);

         {
            transaction_t tr;

            {
               object_t& o1 = *ro1->modify(tr);
               o1[rock] = 7;
            }

            {
               transaction_t sub_tr;

               object_t& o1 = *ro1->modify(sub_tr);
               o1[rock] = 17;

               sub_tr.cancel();
            }

            Assert::AreEqual<int32_t>(7, (*ro1)[rock]);

            {
               transaction_t sub_tr;

               object_t& o1 = *ro1->modify(sub_tr);
               o1[rock] = 17;

               sub_tr.sub_commit(tr);
            }

            Assert::AreEqual<int32_t>(17, (*ro1)[rock]);

            tr.commit(undo_redo);
         }

         Assert::AreEqual<int32_t>(17, (*ro1)[rock]);
      }

   private:
      void fill_object(object_t& o1)
      {
         o1[rock] = 3;
         o1[pebble] = 4;
         o1[sand] = 5.0;
         o1[hello] = L"6";
         o1[world] = voc::rock;
      }

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
