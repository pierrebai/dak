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
   TEST_CLASS(ref_istream_tests)
   {
   public:
      ref_istream_tests()
      {
         any_op::register_ops();
         object::register_object_ops();
         ref_istream_op_t::register_ops();
         ref_ostream_op_t::register_ops();
      }

      TEST_METHOD(istream_invalid)
      {
         struct unknown_t {} unknown;

         wstringstream ss;
         transaction_t tr;

         ss << unknown;

         unknown_t received;
         ref_istream_t(ss, voc::get_namespace(), tr) >> received;

         Assert::IsFalse(ss.fail());
      }

      TEST_METHOD(istream_invalid_and_abort)
      {
         struct unknown_t {} unknown;

         wstringstream ss;
         transaction_t tr;

         ss << unknown;

         unknown_t received;
         ref_istream_t ristr(ss, voc::get_namespace(), tr);
         ristr.set_abort_on_unknown(true);
         ristr >> received;

         Assert::IsTrue(ss.fail());
      }

      TEST_METHOD(istream_name)
      {
         wstringstream ss;
         transaction_t tr;

         name_t expected(voc::hexagon);
         ss << expected;

         name_t received;
         ref_istream_t(ss, voc::get_namespace(), tr) >> received;
         Assert::AreEqual(expected, received);
      }

      TEST_METHOD(istream_empty_dict)
      {
         wstringstream ss;
         transaction_t tr;

         dict_t expected;
         ss << expected;

         dict_t received;
         ref_istream_t istr(ss, { voc::get_namespace() }, tr);
         istr >> received;
         Assert::AreEqual(expected, received);

         istr.clear();
      }

      TEST_METHOD(istream_one_item_dict)
      {
         wstringstream ss;
         transaction_t tr;

         dict_t expected;
         expected[voc::rock] = 3;
         ss << expected;

         dict_t received;
         ref_istream_t(ss, voc::get_namespace(), tr) >> received;
         Assert::AreEqual(expected, received);
      }

      TEST_METHOD(istream_empty_array)
      {
         wstringstream ss;
         transaction_t tr;

         array_t expected;
         ss << expected;

         array_t received;
         ref_istream_t(ss, voc::get_namespace(), tr) >> received;
         Assert::AreEqual(expected, received);
      }

      TEST_METHOD(istream_multi_items_array)
      {
         wstringstream ss;
         transaction_t tr;

         array_t expected;
         expected.grow() = 3;
         expected.grow() = voc::above;
         expected.grow() = 5;
         expected.grow() = voc::above;
         expected.grow() = voc::below;
         ss << expected;

         array_t received;
         ref_istream_t(ss, voc::get_namespace(), tr) >> received;
         Assert::AreEqual(expected, received);
      }

      TEST_METHOD(istream_complex_dict)
      {
         timeline_t undo_redo;

         wstringstream ss;
         auto expected = object_t::make();
         {
            transaction_t tr1;

            auto& mo1 = *expected->modify(tr1);

            auto o2 = object_t::make();
            mo1[voc::child] = o2;

            auto& mo2 = *o2->modify(tr1);
            array_t& a3 = mo2[voc::after];

            a3[0] = true;
            a3[1] = weak_ref_t<object_t>(expected);

            dict_t& d32 = a3[2];
            d32[voc::date] = 55;

            tr1.commit_into(undo_redo);
         }
         ref_ostream_t(ss) << expected;

         ref_t<object_t> received;
         {
            transaction_t tr;
            ref_istream_t(ss, voc::get_namespace(), tr) >> received;
            tr.commit_into(undo_redo);
         }

         Assert::IsTrue(received.is_valid());
         Assert::IsTrue(are_similar(valid_ref_t<object_t>(received), expected));

         ss.clear();
         ref_ostream_t rostr(ss);

         const int64_t reserved_id = rostr.get_object_id(expected);
         Assert::AreNotEqual<int64_t>(0, reserved_id);
         Assert::AreEqual<int64_t>(-reserved_id, rostr.get_object_id(expected));

         rostr.clear();
         Assert::AreEqual<int64_t>(reserved_id, rostr.get_object_id(expected));
      }

      TEST_METHOD(istream_parsing_create_names_and_namespaces)
      {
         std::wistringstream ss(
            L"@ 1 dak::object::ref_t<object_t> 1 {\n"
            L"  @ 2 dak::object::name_t / 1 : \"\" / \"child\": @ 3 dak::object::value_t @ -1 2 {\n"
            L"    @ -2 / 2 : \"custom\" / \"after\": @ -3 @ 4 dak::object::array_t [\n"
            L"      @ -3 @ 5 bool 1,\n"
            L"      @ -3 @ 6 dak::object::weak_ref_t<object_t> -1,\n"
            L"    ],\n"
            L"  },\n"
            L"}");
         transaction_t tr;

         ref_t<object_t> received;
         auto target_ns = namespace_t::make();
         ref_istream_t(ss, target_ns, tr) >> received;

         Assert::IsFalse(ss.fail());
         Assert::IsTrue(received.is_valid());

         Assert::IsTrue(target_ns->get_namespace(L"").is_null());
         Assert::IsTrue(target_ns->get_namespace(L"custom").is_valid());

         name_t child = target_ns->get_name(L"child");
         name_t custom_after = valid_ref_t(target_ns->get_namespace(L"custom"))->get_name(L"after");

         Assert::IsTrue(child.is_valid());
         Assert::IsTrue(custom_after.is_valid());

         valid_ref_t valid_rec(received);

         Assert::AreEqual<index_t>(1, valid_rec->size());
         Assert::AreEqual(typeid(ref_t<object_t>), valid_rec[child].get_type_info());

         valid_ref_t<object_t> child_obj = valid_rec[child];

         Assert::AreEqual<index_t>(1, child_obj->size());
         Assert::AreEqual(typeid(array_t), child_obj[custom_after].get_type_info());

         const array_t arr = child_obj[custom_after];

         Assert::AreEqual<index_t>(2, arr.size());

         Assert::AreEqual(typeid(bool), arr[0].get_type_info());
         Assert::IsTrue(arr[0].as_boolean());

         Assert::AreEqual(typeid(weak_ref_t<object_t>), arr[1].get_type_info());
         Assert::IsTrue(arr[1].as_weak_ref() == received);
      }

      TEST_METHOD(istream_parsing_metadata)
      {
         std::wistringstream ss(
            L"@ 1 dak::object::edit_ref_t<object_t> 1 {\n"
            L"  @ 2 dak::object::name_t / 1 : \"\" / \"child\": @ 3 dak::object::value_t @ 4 dak::object::ref_t<object_t> 2 {\n"
            L"    @ -2 / 2 : \"\" / \"rock\" {\n"
            L"      @ -2 / 3 : \"\" / \"always\",\n"
            L"    }: @ -3 @ 5 dak::object::array_t [\n"
            L"      @ -3 @ 6 bool 1,\n"
            L"      @ -3 @ 7 dak::object::weak_ref_t<object_t> -1,\n"
            L"    ],\n"
            L"  },\n"
            L"}");
         transaction_t tr;
         auto target_ns = namespace_t::make();

         ref_t<object_t> received;
         ref_istream_t(ss, target_ns, tr) >> received;

         Assert::IsFalse(ss.fail());
         Assert::IsTrue(received.is_valid());

         name_t child = target_ns->get_name(L"child");
         name_t rock = target_ns->get_name(L"rock");
         name_t always = target_ns->get_name(L"always");

         valid_ref_t valid_rec(received);

         Assert::AreEqual<index_t>(1, valid_rec->size());
         Assert::AreEqual(typeid(ref_t<object_t>), valid_rec[child].get_type_info());

         valid_ref_t<object_t> child_obj = valid_rec[child];

         Assert::AreEqual<index_t>(1, child_obj->size());
         Assert::AreEqual(typeid(array_t), child_obj[rock].get_type_info());

         Assert::IsTrue(rock.has_metadata(always));

         const array_t arr = child_obj[rock];

         Assert::AreEqual<index_t>(2, arr.size());

         Assert::AreEqual(typeid(bool), arr[0].get_type_info());
         Assert::IsTrue(arr[0].as_boolean());

         Assert::AreEqual(typeid(weak_ref_t<object_t>), arr[1].get_type_info());
         Assert::IsTrue(arr[1].as_weak_ref() == received);
      }

      //////////////////////////////////////////////////////////////////////////
      //
      // Parsing error tests. These are fragile since they may fail for reasons
      // other than the intended one!

      TEST_METHOD(istream_parsing_missing_array_comma)
      {
         std::wistringstream ss(
            L"@ 1 dak::object::ref_t<object_t> 1 {\n"
            L"  @ 2 dak::object::name_t / 1 : \"\" / \"child\": @ 3 dak::object::value_t @ -1 2 {\n"
            L"    @ -2 / 2 : \"custom\" / \"after\": @ -3 @ 4 dak::object::array_t [\n"
            L"      @ -3 @ 5 bool 1\n" // here
            L"      @ -3 @ 6 dak::object::weak_ref_t<object_t> -1,\n"
            L"    ],\n"
            L"  },\n"
            L"}");
         transaction_t tr;

         ref_t<object_t> received;
         ref_istream_t(ss, voc::get_namespace(), tr) >> received;

         Assert::IsTrue(ss.fail());
      }

      TEST_METHOD(istream_parsing_missing_opening_accolade)
      {
         std::wistringstream ss(
            L"@ 1 dak::object::ref_t<object_t> 1 {\n"
            L"  @ 2 dak::object::name_t / 1 : \"\" / \"child\": @ 3 dak::object::value_t @ -1 2\n" //here
            L"    @ -2 / 2 : \"custom\" / \"after\": @ -3 @ 4 dak::object::array_t [\n"
            L"      @ -3 @ 5 bool 1,\n"
            L"      @ -3 @ 6 dak::object::weak_ref_t<object_t> -1,\n"
            L"    ],\n"
            L"  },\n"
            L"}");
         transaction_t tr;

         ref_t<object_t> received;
         ref_istream_t(ss, voc::get_namespace(), tr) >> received;

         Assert::IsTrue(ss.fail());
      }

      TEST_METHOD(istream_parsing_missing_closing_accolade)
      {
         std::wistringstream ss(
            L"@ 1 dak::object::ref_t<object_t> 1 {\n"
            L"  @ 2 dak::object::name_t / 1 : \"\" / \"child\": @ 3 dak::object::value_t @ -1 2 {\n"
            L"    @ -2 / 2 : \"custom\" / \"after\": @ -3 @ 4 dak::object::array_t [\n"
            L"      @ -3 @ 5 bool 1,\n"
            L"      @ -3 @ 6 dak::object::weak_ref_t<object_t> -1,\n"
            L"    ],\n"
            L"  ,\n" // here
            L"}");
         transaction_t tr;

         ref_t<object_t> received;
         ref_istream_t(ss, voc::get_namespace(), tr) >> received;

         Assert::IsTrue(ss.fail());
      }

      TEST_METHOD(istream_parsing_missing_column)
      {
         std::wistringstream ss(
            L"@ 1 dak::object::ref_t<object_t> 1 {\n"
            L"  @ 2 dak::object::name_t / 1  \"\" / \"child\": @ 3 dak::object::value_t @ -1 2 {\n" //here
            L"    @ -2 / 2 : \"custom\" / \"after\": @ -3 @ 4 dak::object::array_t [\n"
            L"      @ -3 @ 5 bool 1,\n"
            L"      @ -3 @ 6 dak::object::weak_ref_t<object_t> -1,\n"
            L"    ],\n"
            L"  },\n"
            L"}");
         transaction_t tr;

         ref_t<object_t> received;
         ref_istream_t(ss, voc::get_namespace(), tr) >> received;

         Assert::IsTrue(ss.fail());
      }

      TEST_METHOD(istream_parsing_missing_opening_bracket)
      {
         std::wistringstream ss(
            L"@ 1 dak::object::ref_t<object_t> 1 {\n"
            L"  @ 2 dak::object::name_t / 1 : \"\" / \"child\": @ 3 dak::object::value_t @ -1 2 {\n"
            L"    @ -2 / 2 : \"custom\" / \"after\": @ -3 @ 4 dak::object::array_t \n" //here
            L"      @ -3 @ 5 bool 1,\n"
            L"      @ -3 @ 6 dak::object::weak_ref_t<object_t> -1,\n"
            L"    ],\n"
            L"  },\n"
            L"}");
         transaction_t tr;

         ref_t<object_t> received;
         ref_istream_t(ss, voc::get_namespace(), tr) >> received;

         Assert::IsTrue(ss.fail());
      }

      TEST_METHOD(istream_parsing_missing_closing_bracket)
      {
         std::wistringstream ss(
            L"@ 1 dak::object::ref_t<object_t> 1 {\n"
            L"  @ 2 dak::object::name_t / 1 : \"\" / \"child\": @ 3 dak::object::value_t @ -1 2 {\n"
            L"    @ -2 / 2 : \"custom\" / \"after\": @ -3 @ 4 dak::object::array_t [\n"
            L"      @ -3 @ 5 bool 1,\n"
            L"      @ -3 @ 6 dak::object::weak_ref_t<object_t> -1,\n"
            L"    ,\n" //here
            L"  },\n"
            L"}");
         transaction_t tr;

         ref_t<object_t> received;
         ref_istream_t(ss, voc::get_namespace(), tr) >> received;

         Assert::IsTrue(ss.fail());
      }


      TEST_METHOD(istream_parsing_missing_object_comma)
      {
         std::wistringstream ss(
            L"@ 1 dak::object::ref_t<object_t> 1 {\n"
            L"  @ 2 dak::object::name_t / 1 : \"\" / \"child\": @ 3 dak::object::value_t @ -1 2 {\n"
            L"    @ -2 / 2 : \"custom\" / \"after\": @ -3 @ 4 dak::object::array_t [\n"
            L"      @ -3 @ 5 bool 1,\n"
            L"      @ -3 @ 6 dak::object::weak_ref_t<object_t> -1,\n"
            L"    ],\n"
            L"  }\n" //here
            L"}");
         transaction_t tr;

         ref_t<object_t> received;
         ref_istream_t(ss, voc::get_namespace(), tr) >> received;

         Assert::IsTrue(ss.fail());
      }

      TEST_METHOD(istream_parsing_missing_name_first_slash)
      {
         std::wistringstream ss(
            L"@ 1 dak::object::ref_t<object_t> 1 {\n"
            L"  @ 2 dak::object::name_t 1 : \"\" / \"child\": @ 3 dak::object::value_t @ -1 2 {\n" //here
            L"    @ -2 / 2 : \"custom\" / \"after\": @ -3 @ 4 dak::object::array_t [\n"
            L"      @ -3 @ 5 bool 1,\n"
            L"      @ -3 @ 6 dak::object::weak_ref_t<object_t> -1,\n"
            L"    ],\n"
            L"  },\n"
            L"}");
         transaction_t tr;

         ref_t<object_t> received;
         ref_istream_t(ss, voc::get_namespace(), tr) >> received;

         Assert::IsTrue(ss.fail());
      }

      TEST_METHOD(istream_parsing_missing_name_second_slash)
      {
         std::wistringstream ss(
            L"@ 1 dak::object::ref_t<object_t> 1 {\n"
            L"  @ 2 dak::object::name_t / 1 : \"\"  \"child\": @ 3 dak::object::value_t @ -1 2 {\n" //here
            L"    @ -2 / 2 : \"custom\" / \"after\": @ -3 @ 4 dak::object::array_t [\n"
            L"      @ -3 @ 5 bool 1,\n"
            L"      @ -3 @ 6 dak::object::weak_ref_t<object_t> -1,\n"
            L"    ],\n"
            L"  },\n"
            L"}");
         transaction_t tr;

         ref_t<object_t> received;
         ref_istream_t(ss, voc::get_namespace(), tr) >> received;

         Assert::IsTrue(ss.fail());
      }

      TEST_METHOD(istream_parsing_bad_name_id)
      {
         std::wistringstream ss(
            L"@ 1 dak::object::ref_t<object_t> 1 {\n"
            L"  @ 2 dak::object::name_t / -1 : \"\" / \"child\": @ 3 dak::object::value_t @ -1 2 {\n" // here
            L"    @ -2 / 2 : \"custom\" / \"after\": @ -3 @ 4 dak::object::array_t [\n"
            L"      @ -3 @ 5 bool 1,\n"
            L"      @ -3 @ 6 dak::object::weak_ref_t<object_t> -1,\n"
            L"    ],\n"
            L"  },\n"
            L"}");
         transaction_t tr;

         ref_istream_t ristr(ss, voc::get_namespace(), tr);
         ristr.set_abort_on_unknown(true);

         ref_t<object_t> received;
         ristr >> received;

         Assert::IsTrue(ss.fail());
      }

      TEST_METHOD(istream_parsing_bad_type_id)
      {
         std::wistringstream ss(
            L"@ 1 dak::object::ref_t<object_t> 1 {\n"
            L"  @ -2 dak::object::name_t / 1 : \"\" / \"child\": @ 3 dak::object::value_t @ -1 2 {\n" //here
            L"    @ -2 / 2 : \"custom\" / \"after\": @ -3 @ 4 dak::object::array_t [\n"
            L"      @ -3 @ 5 bool 1,\n"
            L"      @ -3 @ 6 dak::object::weak_ref_t<object_t> -1,\n"
            L"    ],\n"
            L"  },\n"
            L"}");
         transaction_t tr;

         ref_istream_t ristr(ss, voc::get_namespace(), tr);
         ristr.set_abort_on_unknown(true);

         ref_t<object_t> received;
         ristr >> received;

         Assert::IsTrue(ss.fail());
      }

      TEST_METHOD(istream_parsing_bad_ref_id)
      {
         std::wistringstream ss(
            L"@ 1 dak::object::ref_t<object_t> -3 {\n" // here
            L"  @ 2 dak::object::name_t / 1 : \"\" / \"child\": @ 3 dak::object::value_t @ -1 2 {\n"
            L"    @ -2 / 2 : \"custom\" / \"after\": @ -3 @ 4 dak::object::array_t [\n"
            L"      @ -3 @ 5 bool 1,\n"
            L"      @ -3 @ 6 dak::object::weak_ref_t<object_t> -1,\n"
            L"    ],\n"
            L"  },\n"
            L"}");
         transaction_t tr;

         ref_istream_t ristr(ss, voc::get_namespace(), tr);
         ristr.set_abort_on_unknown(true);

         ref_t<object_t> received;
         ristr >> received;

         Assert::IsTrue(ss.fail());
      }

      TEST_METHOD(istream_parsing_missing_metadat_comma)
      {
         std::wistringstream ss(
            L"@ 1 dak::object::edit_ref_t<object_t> 1 {\n"
            L"  @ 2 dak::object::name_t / 1 : \"\" / \"child\": @ 3 dak::object::value_t @ 4 dak::object::ref_t<object_t> 2 {\n"
            L"    @ -2 / 2 : \"\" / \"rock\" {\n"
            L"      @ -2 / 3 : \"\" / \"always\"\n" //here
            L"    }: @ -3 @ 5 dak::object::array_t [\n"
            L"      @ -3 @ 6 bool 1,\n"
            L"      @ -3 @ 7 dak::object::weak_ref_t<object_t> -1,\n"
            L"    ],\n"
            L"  },\n"
            L"}");
         transaction_t tr;
         auto target_ns = namespace_t::make();

         ref_t<object_t> received;
         ref_istream_t(ss, target_ns, tr) >> received;

         Assert::IsTrue(ss.fail());
      }

      TEST_METHOD(istream_parsing_missing_metadat_closing_brace)
      {
         std::wistringstream ss(
            L"@ 1 dak::object::edit_ref_t<object_t> 1 {\n"
            L"  @ 2 dak::object::name_t / 1 : \"\" / \"child\": @ 3 dak::object::value_t @ 4 dak::object::ref_t<object_t> 2 {\n"
            L"    @ -2 / 2 : \"\" / \"rock\" {\n"
            L"      @ -2 / 3 : \"\" / \"always\",\n"
            L"    : @ -3 @ 5 dak::object::array_t [\n" // here
            L"      @ -3 @ 6 bool 1,\n"
            L"      @ -3 @ 7 dak::object::weak_ref_t<object_t> -1,\n"
            L"    ],\n"
            L"  },\n"
            L"}");
         transaction_t tr;
         auto target_ns = namespace_t::make();

         ref_t<object_t> received;
         ref_istream_t(ss, target_ns, tr) >> received;

         Assert::IsTrue(ss.fail());
      }
   };
}
