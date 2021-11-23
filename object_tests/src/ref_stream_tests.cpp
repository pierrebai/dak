#include "CppUnitTest.h"

#include "dak/object/ref_stream.h"
#include "dak/object/similar.h"
#include "dak/object/timeline.h"
#include "dak/object/tests/helpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace dak::object::tests
{		
   TEST_CLASS(stream_tests)
   {
   public:

      TEST_METHOD(ostream_name)
      {
         wstringstream ss;
         ss << voc::rock;
         Assert::AreEqual(text_t(L"/\"rock\""), ss.str());
      }

      TEST_METHOD(ostream_empty_dict)
      {
         wstringstream ss;
         dict_t d1;
         ss << d1;
         Assert::AreEqual(text_t(L"{\n}"), ss.str());
      }

      TEST_METHOD(ostream_one_item_dict)
      {
         wstringstream ss;
         dict_t d2;
         d2[voc::rock] = 3;
         ss << d2;
         Assert::AreEqual(text_t(L"{\n/\"rock\": i 3,\n}"), ss.str());
      }

      TEST_METHOD(ostream_one_empty_array)
      {
         wstringstream ss;
         array_t a1;
         ss << a1;
         Assert::AreEqual(text_t(L"[\n]"), ss.str());
      }

      TEST_METHOD(ostream_three_items_array)
      {
         wstringstream ss;
         array_t a2;
         a2.grow() = 3;
         a2.grow() = 5;
         a2.grow() = 7;
         ss << a2;
         Assert::AreEqual(text_t(L"[\ni 3,\ni 5,\ni 7,\n]"), ss.str());
      }

      TEST_METHOD(ostream_complex_dict)
      {
         wstringstream ss;
         auto o1 = object_t::make();
         {
            timeline_t undo_redo;
            transaction_t tr1;

            auto& mo1 = o1->modify(tr1);

            auto o2 = object_t::make();
            mo1[voc::child] = o2;

            auto& mo2 = o2->modify(tr1);
            array_t& a3 = mo2[voc::after];

            a3[0] = true;
            a3[1] = o1;

            tr1.commit(undo_redo);
         }
         ref_ostream_t(ss) << o1;
         Assert::AreEqual(text_t(
            L"ref 1 {\n"
            L"/\"child\": r ref 2 {\n"
            L"/\"after\": a [\n"
            L"b 1,\n"
            L"r ref -1,\n"
            L"],\n"
            L"},\n"
            L"}"),
            ss.str());
      }

      TEST_METHOD(istream_name)
      {
         wstringstream ss;

         name_t expected(text_t(L"expected"));
         ss << expected;

         name_t received;
         ss >> received;
         Assert::AreEqual(expected, received);
      }

      TEST_METHOD(istream_empty_dict)
      {
         wstringstream ss;

         dict_t expected;
         ss << expected;

         dict_t received;
         ss >> received;
         Assert::AreEqual(expected, received);
      }

      TEST_METHOD(istream_one_item_dict)
      {
         wstringstream ss;

         dict_t expected;
         expected[text_t(L"rock")] = 3;
         ss << expected;

         dict_t received;
         ss >> received;
         Assert::AreEqual(expected, received);
      }

      TEST_METHOD(istream_empty_array)
      {
         wstringstream ss;

         array_t expected;
         ss << expected;

         array_t received;
         ss >> received;
         Assert::AreEqual(expected, received);
      }

      TEST_METHOD(istream_three_items_array)
      {
         wstringstream ss;

         array_t expected;
         expected.grow() = 3;
         expected.grow() = 5;
         expected.grow() = 7;
         ss << expected;

         array_t received;
         ss >> received;
         Assert::AreEqual(expected, received);
      }

      TEST_METHOD(istream_complex_dict)
      {
         const text_t child(L"child");
         const text_t after(L"after");

         wstringstream ss;
         auto expected = object_t::make();
         {
            timeline_t undo_redo;
            transaction_t tr1;

            auto& mo1 = expected->modify(tr1);

            auto o2 = object_t::make();
            mo1[child] = o2;

            auto& mo2 = o2->modify(tr1);
            array_t& a3 = mo2[after];

            a3[0] = true;
            a3[1] = expected;

            tr1.commit(undo_redo);
         }
         ref_ostream_t(ss) << expected;

         ref_t<object_t> received;
         ref_istream_t(ss) >> received;

         Assert::IsTrue(received.is_valid());
         Assert::IsTrue(are_similar(valid_ref_t<object_t>(received), expected));
      }
   };
}
