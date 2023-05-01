#include <CppUnitTest.h>

#include <dak/object_io/ref_istream_op.h>
#include <dak/object_io/ref_ostream_op.h>
#include <dak/object/similar.h>
#include <dak/object/timeline.h>

#include <dak/object_io/tests/helpers.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace dak::object::tests
{		
   TEST_CLASS(ref_ostream_tests)
   {
   public:
      ref_ostream_tests()
      {
         any_op::register_ops();
         object::register_object_ops();
         ref_istream_op_t::register_ops();
         ref_ostream_op_t::register_ops();
      }

      TEST_METHOD(ostream_invalid)
      {
         wstringstream ss;
         struct unknown_t {} unknown;

         ss << unknown;
         Assert::AreEqual(text_t(L"@ 1 void "), ss.str());

         Assert::IsFalse(ss.fail());
      }

      TEST_METHOD(ostream_invalid_and_abort)
      {
         wstringstream ss;
         struct unknown_t {} unknown;

         ref_ostream_t rostr(ss);
         rostr.set_abort_on_unknown(true);

         rostr << unknown;
         Assert::AreEqual(text_t(L"@ 1 "), ss.str());

         Assert::IsTrue(ss.fail());
      }

      TEST_METHOD(ostream_name)
      {
         wstringstream ss;
         ss << voc::rock;
         Assert::AreEqual(text_t(L"@ 1 dak::object::name_t / 1 : \"\" / \"rock\""), ss.str());
      }

      TEST_METHOD(ostream_empty_dict)
      {
         wstringstream ss;
         dict_t d1;
         ss << d1;
         Assert::AreEqual(text_t(L"@ 1 dak::object::dict_t {\n}"), ss.str());
      }

      TEST_METHOD(ostream_one_item_dict)
      {
         wstringstream ss;
         dict_t d2;
         d2[voc::rock] = 3;
         ss << d2;
         Assert::AreEqual(text_t(
            L"@ 1 dak::object::dict_t {\n"
            L"  @ 2 dak::object::name_t / 1 : \"\" / \"rock\": @ 3 dak::object::value_t @ 4 int32_t 3,"
            L"\n"
            L"}"), ss.str());
      }

      TEST_METHOD(ostream_one_empty_array)
      {
         wstringstream ss;
         array_t a1;
         ss << a1;
         Assert::AreEqual(text_t(L"@ 1 dak::object::array_t [\n]"), ss.str());
      }

      TEST_METHOD(ostream_three_items_array)
      {
         wstringstream ss;
         array_t a2;
         a2.grow() = 3;
         a2.grow() = 5;
         a2.grow() = 7;
         ss << a2;
         Assert::AreEqual(text_t(
            L"@ 1 dak::object::array_t [\n"
            L"  @ 2 dak::object::value_t @ 3 int32_t 3,\n"
            L"  @ -2 @ -3 5,\n"
            L"  @ -2 @ -3 7,\n"
            L"]"), ss.str());
      }

      TEST_METHOD(ostream_complex_dict)
      {
         wstringstream ss;
         auto o1 = object_t::make();
         {
            timeline_t undo_redo;
            transaction_t tr1;

            auto& mo1 = *o1->modify(tr1);

            auto o2 = object_t::make();
            mo1[voc::child] = o2;

            auto& mo2 = *o2->modify(tr1);
            array_t& a3 = mo2[voc::after];

            a3[0] = true;
            a3[1] = o1;

            tr1.commit_into(undo_redo);
         }
         ref_ostream_t(ss) << o1;
         Assert::AreEqual(text_t(
            L"@ 1 dak::object::edit_ref_t<object_t> 1 {\n"
            L"  @ 2 dak::object::name_t / 1 : \"\" / \"child\": @ 3 dak::object::value_t @ 4 dak::object::ref_t<object_t> 2 {\n"
            L"    @ -2 / 2 : \"\" / \"after\": @ -3 @ 5 dak::object::array_t [\n"
            L"      @ -3 @ 6 bool 1,\n"
            L"      @ -3 @ -4 -1,\n"
            L"    ],\n"
            L"  },\n"
            L"}"),
            ss.str());
      }

      TEST_METHOD(ostream_name_metadata)
      {
         timeline_t undo_redo;

         auto ns = namespace_t::make();
         name_t rock_with_metadata = name_t(ns, voc::rock);
         {
            transaction_t tr;

            rock_with_metadata.add_metadata(voc::always, tr);

            tr.commit_into(undo_redo);
         }

         wstringstream ss;
         auto o1 = object_t::make();
         {
            transaction_t tr1;

            auto& mo1 = *o1->modify(tr1);

            auto o2 = object_t::make();
            mo1[voc::child] = o2;

            auto& mo2 = *o2->modify(tr1);
            array_t& a3 = mo2[rock_with_metadata];

            a3[0] = true;
            a3[1] = weak_ref_t<object_t>(o1);

            tr1.commit_into(undo_redo);
         }

         ref_ostream_t(ss) << o1;

         Assert::AreEqual(text_t(
            L"@ 1 dak::object::edit_ref_t<object_t> 1 {\n"
            L"  @ 2 dak::object::name_t / 1 : \"\" / \"child\": @ 3 dak::object::value_t @ 4 dak::object::ref_t<object_t> 2 {\n"
            L"    @ -2 / 2 : \"\" / \"rock\" {\n"
            L"      @ -2 / 3 : \"\" / \"always\",\n"
            L"    }: @ -3 @ 5 dak::object::array_t [\n"
            L"      @ -3 @ 6 bool 1,\n"
            L"      @ -3 @ 7 dak::object::weak_ref_t<object_t> -1,\n"
            L"    ],\n"
            L"  },\n"
            L"}"),
            ss.str());
      }
   };
}
