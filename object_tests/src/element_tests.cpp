#include "CppUnitTest.h"

#include "dak/object/element.h"
#include "dak/object/object.h"
#include "dak/object/voc.h"
#include "dak/object/tests/helpers.h"

#include "dak/any_op/compare_op.h"
#include "dak/any_op/size_op.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace dak::any_op;

namespace dak::object::tests
{	
   namespace
   {
      struct data_t
      {
         int i = 4;
         float f = 33.0f;

         auto operator<=>(const data_t&) const = default;
      };

      void register_data_ops()
      {
         compare_op_t::make<>::op<comparison_t, data_t, data_t>([](const data_t& arg_a, const data_t& arg_b) -> comparison_t
            {
               if (arg_a.i < arg_b)
                  return comparison_t::less;
               if (arg_a > arg_b)
                  return comparison_t::more;
               return comparison_t::equal;
            });

         size_op_t::make<>::op<uint64_t, data_t>([](const data_t& arg_a) -> uint64_t { return 77u; });

      }
   }


   TEST_CLASS(element_tests)
	{
	public:
      element_tests()
      {
         register_data_ops();
      }

		TEST_METHOD(element_base)
		{

         element_t e;

         Assert::AreEqual(e, element_t());
         Assert::AreEqual(e, element_t::empty);
         Assert::AreNotEqual(e, element_t(1));

         Assert::IsTrue( e == element_t());
         Assert::IsTrue(e == element_t::empty);
         Assert::IsFalse(e != element_t());

         Assert::IsFalse(e == element_t(1));
         Assert::IsFalse(element_t::empty == element_t(1));
         Assert::IsTrue(e != element_t(1));
      }

      TEST_METHOD(element_constructors)
      {
         valid_ref_t<object_t> o = object_t::make();
         data_t y;

         element_t e_u;
         element_t e_t1(text_t(L"text"));
         element_t e_t2(L"strptr");
         element_t e_c1('c');
         element_t e_c2(L'w');
         element_t e_b(true);
         element_t e_i2((int16_t)2);
         element_t e_i1((int32_t)1);
         element_t e_i3((int64_t)3);
         element_t e_u1((uint16_t)4u);
         element_t e_u2((uint32_t)5u);
         element_t e_u3((uint64_t)6u);
         element_t e_r1(7.0f);
         element_t e_r2(8.0);
         element_t e_a((array_t()));
         element_t e_d((dict_t()));
         element_t e_n(voc::rock);
         element_t e_o(o);
         element_t e_y(y);

         Assert::AreEqual(datatype_t::unknown, e_u.type());
         Assert::AreEqual(datatype_t::text, e_t1.type());
         Assert::AreEqual(datatype_t::text, e_t2.type());
         Assert::AreEqual(datatype_t::integer, e_c1.type());
         Assert::AreEqual(datatype_t::integer, e_c2.type());
         Assert::AreEqual(datatype_t::boolean, e_b.type());
         Assert::AreEqual(datatype_t::integer, e_i2.type());
         Assert::AreEqual(datatype_t::integer, e_i1.type());
         Assert::AreEqual(datatype_t::integer, e_i3.type());
         Assert::AreEqual(datatype_t::integer, e_u1.type());
         Assert::AreEqual(datatype_t::integer, e_u2.type());
         Assert::AreEqual(datatype_t::integer, e_u3.type());
         Assert::AreEqual(datatype_t::real, e_r1.type());
         Assert::AreEqual(datatype_t::real, e_r2.type());
         Assert::AreEqual(datatype_t::array, e_a.type());
         Assert::AreEqual(datatype_t::dict, e_d.type());
         Assert::AreEqual(datatype_t::name, e_n.type());
         Assert::AreEqual(datatype_t::ref, e_o.type());
         Assert::AreEqual(datatype_t::data, e_y.type());
      }

      TEST_METHOD(element_assignments)
      {
         auto o = object_t::make();
         data_t y;

         element_t e_u;
         element_t e_t1;
         element_t e_t2;
         element_t e_c1;
         element_t e_c2;
         element_t e_b;
         element_t e_i2;
         element_t e_i1;
         element_t e_i3;
         element_t e_u1;
         element_t e_u2;
         element_t e_u3;
         element_t e_r1;
         element_t e_r2;
         element_t e_a;
         element_t e_d;
         element_t e_n;
         element_t e_o;
         element_t e_y;

         e_u  = element_t();
         e_t1 = text_t(L"text");
         e_t2 = L"strptr";
         e_c1 = 'c';
         e_c2 = L'w';
         e_b  = true;
         e_i2 = (int16_t)2;
         e_i1 = (int32_t)1;
         e_i3 = (int64_t)3;
         e_u1 = (uint16_t)4u;
         e_u2 = (uint32_t)5u;
         e_u3 = (uint64_t)6u;
         e_r1 = 7.0f;
         e_r2 = 8.0;
         e_a  = array_t();
         e_d  = dict_t();
         e_n  = voc::rock;
         e_o  = o;
         e_y = y;

         Assert::AreEqual(datatype_t::unknown, e_u.type());
         Assert::AreEqual(datatype_t::text, e_t1.type());
         Assert::AreEqual(datatype_t::text, e_t2.type());
         Assert::AreEqual(datatype_t::integer, e_c1.type());
         Assert::AreEqual(datatype_t::integer, e_c2.type());
         Assert::AreEqual(datatype_t::boolean, e_b.type());
         Assert::AreEqual(datatype_t::integer, e_i2.type());
         Assert::AreEqual(datatype_t::integer, e_i1.type());
         Assert::AreEqual(datatype_t::integer, e_i3.type());
         Assert::AreEqual(datatype_t::integer, e_u1.type());
         Assert::AreEqual(datatype_t::integer, e_u2.type());
         Assert::AreEqual(datatype_t::integer, e_u3.type());
         Assert::AreEqual(datatype_t::real, e_r1.type());
         Assert::AreEqual(datatype_t::real, e_r2.type());
         Assert::AreEqual(datatype_t::array, e_a.type());
         Assert::AreEqual(datatype_t::dict, e_d.type());
         Assert::AreEqual(datatype_t::name, e_n.type());
         Assert::AreEqual(datatype_t::ref, e_o.type());
         Assert::AreEqual(datatype_t::data, e_y.type());
      }

      TEST_METHOD(element_text_assignments)
      {
         element_t e1;

         e1 = L"hello";
         Assert::AreEqual<text_t>(text_t(L"hello"), e1);

         e1 = (str_ptr_t)nullptr;
         Assert::AreEqual<text_t>(text_t(L""), e1);

         e1 = L"bye";
         Assert::AreEqual<text_t>(text_t(L"bye"), e1);

         e1.reset(datatype_t::text);
         Assert::AreEqual<text_t>(text_t(L""), e1);

         e1 = L"bye";
         Assert::AreEqual<text_t>(text_t(L"bye"), e1);

         e1.verify(datatype_t::text);
         Assert::AreEqual<text_t>(text_t(L"bye"), e1);
      }

      TEST_METHOD(element_conversion)
      {
         auto o = object_t::make();
         data_t y;

         element_t e_u;
         element_t e_t1(text_t(L"text"));
         element_t e_t2(L"strptr");
         element_t e_c1('c');
         element_t e_c2(L'w');
         element_t e_b(true);
         element_t e_i2((int16_t)2);
         element_t e_i1((int32_t)1);
         element_t e_i3((int64_t)3);
         element_t e_u1((uint16_t)4u);
         element_t e_u2((uint32_t)5u);
         element_t e_u3((uint64_t)6u);
         element_t e_r1(7.0f);
         element_t e_r2(8.0);
         element_t e_a((array_t()));
         element_t e_d((dict_t()));
         element_t e_n(voc::rock);
         element_t e_o(o);
         element_t e_y(y);

         Assert::AreEqual<int32_t>(0, e_u);
         Assert::AreEqual<text_t>(text_t(L"text"), e_t1);
         Assert::AreEqual<text_t>(L"strptr", e_t2);
         Assert::AreEqual<char>('c', e_c1);
         Assert::AreEqual<wchar_t>(L'w', e_c2);
         Assert::AreEqual<bool>(true, e_b);
         Assert::AreEqual<int16_t>((int16_t)2, e_i2);
         Assert::AreEqual<int32_t>((int32_t)1, e_i1);
         Assert::AreEqual<int64_t>((int64_t)3, e_i3);
         Assert::AreEqual<uint16_t>((uint16_t)4u, e_u1);
         Assert::AreEqual<uint32_t>((uint32_t)5u, e_u2);
         Assert::AreEqual<uint64_t>((uint64_t)6u, e_u3);
         Assert::AreEqual<float>(7.0f, e_r1);
         Assert::AreEqual<double>(8.0, e_r2);
         Assert::AreEqual<array_t>((array_t()), e_a);
         Assert::AreEqual<dict_t>((dict_t()), e_d);
         Assert::AreEqual<name_t>(voc::rock, e_n);
         Assert::AreEqual<valid_ref_t<object_t>>(o, e_o);
         Assert::AreEqual<any_t>(any_t(y), e_y);
      }

      TEST_METHOD(element_const_conversion)
      {
         auto o = object_t::make();
         data_t y;

         const element_t e_u;
         const element_t e_t1(text_t(L"text"));
         const element_t e_t2(L"strptr");
         const element_t e_c1('c');
         const element_t e_c2(L'w');
         const element_t e_b(true);
         const element_t e_i2((int16_t)2);
         const element_t e_i1((int32_t)1);
         const element_t e_i3((int64_t)3);
         const element_t e_u1((uint16_t)4u);
         const element_t e_u2((uint32_t)5u);
         const element_t e_u3((uint64_t)6u);
         const element_t e_r1(7.0f);
         const element_t e_r2(8.0);
         const element_t e_a((array_t()));
         const element_t e_d((dict_t()));
         const element_t e_n(voc::rock);
         const element_t e_o(o);
         const element_t e_y(y);

         Assert::AreEqual<int32_t>(0, e_u);
         Assert::AreEqual<text_t>(text_t(L"text"), e_t1);
         Assert::AreEqual<text_t>(L"strptr", e_t2);
         Assert::AreEqual<char>('c', e_c1);
         Assert::AreEqual<wchar_t>(L'w', e_c2);
         Assert::AreEqual<bool>(true, e_b);
         Assert::AreEqual<int16_t>((int16_t)2, e_i2);
         Assert::AreEqual<int32_t>((int32_t)1, e_i1);
         Assert::AreEqual<int64_t>((int64_t)3, e_i3);
         Assert::AreEqual<uint16_t>((uint16_t)4u, e_u1);
         Assert::AreEqual<uint32_t>((uint32_t)5u, e_u2);
         Assert::AreEqual<uint64_t>((uint64_t)6u, e_u3);
         Assert::AreEqual<float>(7.0f, e_r1);
         Assert::AreEqual<double>(8.0, e_r2);
         Assert::AreEqual<array_t>((array_t()), e_a);
         Assert::AreEqual<dict_t>((dict_t()), e_d);
         Assert::AreEqual<name_t>(voc::rock, e_n);
         Assert::AreEqual<valid_ref_t<object_t>>(o, e_o);
         Assert::AreEqual<any_t>(any_t(y), e_y);
      }

      TEST_METHOD(element_unknown_assignments)
      {
         auto o = object_t::make();
         data_t y;

         element_t e_u;
         element_t e_t1(text_t(L"text"));
         element_t e_t2(L"strptr");
         element_t e_c1('c');
         element_t e_c2(L'w');
         element_t e_b(true);
         element_t e_i2((int16_t)2);
         element_t e_i1((int32_t)1);
         element_t e_i3((int64_t)3);
         element_t e_u1((uint16_t)4u);
         element_t e_u2((uint32_t)5u);
         element_t e_u3((uint64_t)6u);
         element_t e_r1(7.0f);
         element_t e_r2(8.0);
         element_t e_a((array_t()));
         element_t e_d((dict_t()));
         element_t e_n(voc::rock);
         element_t e_o(o);
         element_t e_y(y);

         // Assigning an empty element_t of type unknown
         // should set the type to unknown and reset the value.
         e_u = element_t();
         e_t1 = element_t();
         e_t2 = element_t();
         e_c1 = element_t();
         e_c2 = element_t();
         e_b = element_t();
         e_i2 = element_t();
         e_i1 = element_t();
         e_i3 = element_t();
         e_u1 = element_t();
         e_u2 = element_t();
         e_u3 = element_t();
         e_r1 = element_t();
         e_r2 = element_t();
         e_a = element_t();
         e_d = element_t();
         e_n = element_t();
         e_o = element_t();
         e_y = element_t();

         Assert::AreEqual(datatype_t::unknown, e_u.type());
         Assert::AreEqual(datatype_t::unknown, e_t1.type());
         Assert::AreEqual(datatype_t::unknown, e_t2.type());
         Assert::AreEqual(datatype_t::unknown, e_c1.type());
         Assert::AreEqual(datatype_t::unknown, e_c2.type());
         Assert::AreEqual(datatype_t::unknown, e_b.type());
         Assert::AreEqual(datatype_t::unknown, e_i2.type());
         Assert::AreEqual(datatype_t::unknown, e_i1.type());
         Assert::AreEqual(datatype_t::unknown, e_i3.type());
         Assert::AreEqual(datatype_t::unknown, e_u1.type());
         Assert::AreEqual(datatype_t::unknown, e_u2.type());
         Assert::AreEqual(datatype_t::unknown, e_u3.type());
         Assert::AreEqual(datatype_t::unknown, e_r1.type());
         Assert::AreEqual(datatype_t::unknown, e_r2.type());
         Assert::AreEqual(datatype_t::unknown, e_a.type());
         Assert::AreEqual(datatype_t::unknown, e_d.type());
         Assert::AreEqual(datatype_t::unknown, e_n.type());
         Assert::AreEqual(datatype_t::unknown, e_o.type());
         Assert::AreEqual(datatype_t::unknown, e_y.type());

         Assert::AreEqual<int32_t>(0, e_u);
         Assert::AreEqual<text_t>(text_t(L""), e_t1);
         Assert::AreEqual<text_t>(L"", e_t2);
         Assert::AreEqual<char>('\0', e_c1);
         Assert::AreEqual<wchar_t>(L'\0', e_c2);
         Assert::AreEqual<bool>(false, e_b);
         Assert::AreEqual<int16_t>((int16_t)0, e_i2);
         Assert::AreEqual<int32_t>((int32_t)0, e_i1);
         Assert::AreEqual<int64_t>((int64_t)0, e_i3);
         Assert::AreEqual<uint16_t>((uint16_t)0u, e_u1);
         Assert::AreEqual<uint32_t>((uint32_t)0u, e_u2);
         Assert::AreEqual<uint64_t>((uint64_t)0u, e_u3);
         Assert::AreEqual<float>(0.0f, e_r1);
         Assert::AreEqual<double>(0.0, e_r2);
         Assert::AreEqual<array_t>((array_t()), e_a);
         Assert::AreEqual<dict_t>((dict_t()), e_d);
         Assert::AreNotEqual<name_t>(voc::rock, e_n);
         Assert::AreNotEqual<valid_ref_t<object_t>>(o, e_o);
         Assert::AreNotEqual<any_t>(y, e_y);
      }

      TEST_METHOD(element_size)
      {
         auto o = object_t::make();
         data_t y;

         dict_t d;
         d[voc::rock] = 33;
         d[voc::pebble] = 4;
         d[voc::sand] = 5;

         array_t a;
         a.grow() = 55;
         a.grow() = 66;
         a.grow() = 77;

         const element_t e_u;
         const element_t e_t1(text_t(L"text"));
         const element_t e_t2(L"strptr");
         const element_t e_c1('c');
         const element_t e_c2(L'w');
         const element_t e_b(true);
         const element_t e_i2((int16_t)2);
         const element_t e_i1((int32_t)1);
         const element_t e_i3((int64_t)3);
         const element_t e_u1((uint16_t)4u);
         const element_t e_u2((uint32_t)5u);
         const element_t e_u3((uint64_t)6u);
         const element_t e_r1(7.0f);
         const element_t e_r2(8.0);
         const element_t e_a(a);
         const element_t e_d(d);
         const element_t e_n(voc::rock);
         const element_t e_o(o);
         const element_t e_y(y);

         Assert::AreEqual<index_t>(0, e_u.size());
         Assert::AreEqual<index_t>(4, e_t1.size());
         Assert::AreEqual<index_t>(6, e_t2.size());
         Assert::AreEqual<index_t>(0, e_c1.size());
         Assert::AreEqual<index_t>(0, e_c2.size());
         Assert::AreEqual<index_t>(0, e_b.size());
         Assert::AreEqual<index_t>(0, e_i2.size());
         Assert::AreEqual<index_t>(0, e_i1.size());
         Assert::AreEqual<index_t>(0, e_i3.size());
         Assert::AreEqual<index_t>(0, e_u1.size());
         Assert::AreEqual<index_t>(0, e_u2.size());
         Assert::AreEqual<index_t>(0, e_u3.size());
         Assert::AreEqual<index_t>(0, e_r1.size());
         Assert::AreEqual<index_t>(0, e_r2.size());
         Assert::AreEqual<index_t>(3, e_a.size());
         Assert::AreEqual<index_t>(3, e_d.size());
         Assert::AreEqual<index_t>(0, e_n.size());
         Assert::AreEqual<index_t>(0, e_o.size());
         Assert::AreEqual<index_t>(77, e_y.size());
      }

      TEST_METHOD(element_compatible)
      {
         auto o = object_t::make();
         data_t y;

         dict_t d;
         d[voc::rock] = 33;
         d[voc::pebble] = 4;
         d[voc::sand] = 5;

         array_t a;
         a.grow() = 55;
         a.grow() = 66;
         a.grow() = 77;

         const element_t e_u;
         const element_t e_t1(text_t(L"text"));
         const element_t e_t2(L"strptr");
         const element_t e_c1('c');
         const element_t e_c2(L'w');
         const element_t e_b(true);
         const element_t e_i2((int16_t)2);
         const element_t e_i1((int32_t)1);
         const element_t e_i3((int64_t)3);
         const element_t e_u1((uint16_t)4u);
         const element_t e_u2((uint32_t)5u);
         const element_t e_u3((uint64_t)6u);
         const element_t e_r1(7.0f);
         const element_t e_r2(8.0);
         const element_t e_a(a);
         const element_t e_d(d);
         const element_t e_n(voc::rock);
         const element_t e_o(o);
         const element_t e_y(y);

         Assert::IsTrue(e_u.compatible(datatype_t::unknown));
         Assert::IsTrue(e_t1.compatible(datatype_t::text));
         Assert::IsTrue(e_t2.compatible(datatype_t::text));
         Assert::IsTrue(e_c1.compatible(datatype_t::integer));
         Assert::IsTrue(e_c2.compatible(datatype_t::integer));
         Assert::IsTrue(e_b.compatible(datatype_t::boolean));
         Assert::IsTrue(e_i2.compatible(datatype_t::integer));
         Assert::IsTrue(e_i1.compatible(datatype_t::integer));
         Assert::IsTrue(e_i3.compatible(datatype_t::integer));
         Assert::IsTrue(e_u1.compatible(datatype_t::integer));
         Assert::IsTrue(e_u2.compatible(datatype_t::integer));
         Assert::IsTrue(e_u3.compatible(datatype_t::integer));
         Assert::IsTrue(e_r1.compatible(datatype_t::real));
         Assert::IsTrue(e_r2.compatible(datatype_t::real));
         Assert::IsTrue(e_a.compatible(datatype_t::array));
         Assert::IsTrue(e_d.compatible(datatype_t::dict));
         Assert::IsTrue(e_n.compatible(datatype_t::name));
         Assert::IsTrue(e_o.compatible(datatype_t::ref));
         Assert::IsTrue(e_y.compatible(datatype_t::data));

         Assert::IsTrue(e_b.compatible(datatype_t::integer));
         Assert::IsTrue(e_i2.compatible(datatype_t::boolean));
         Assert::IsTrue(e_i1.compatible(datatype_t::boolean));
         Assert::IsTrue(e_i3.compatible(datatype_t::boolean));
         Assert::IsTrue(e_u1.compatible(datatype_t::boolean));
         Assert::IsTrue(e_u2.compatible(datatype_t::boolean));
         Assert::IsTrue(e_u3.compatible(datatype_t::boolean));

         Assert::IsFalse(e_u.compatible(datatype_t::text));
         Assert::IsFalse(e_t1.compatible(datatype_t::integer));
         Assert::IsFalse(e_t2.compatible(datatype_t::integer));
         Assert::IsFalse(e_c1.compatible(datatype_t::real));
         Assert::IsFalse(e_c2.compatible(datatype_t::unknown));
         Assert::IsFalse(e_b.compatible(datatype_t::real));
         Assert::IsFalse(e_i2.compatible(datatype_t::text));
         Assert::IsFalse(e_i1.compatible(datatype_t::array));
         Assert::IsFalse(e_i3.compatible(datatype_t::dict));
         Assert::IsFalse(e_u1.compatible(datatype_t::name));
         Assert::IsFalse(e_u2.compatible(datatype_t::ref));
         Assert::IsFalse(e_u3.compatible(datatype_t::real));
         Assert::IsFalse(e_r1.compatible(datatype_t::integer));
         Assert::IsFalse(e_r2.compatible(datatype_t::name));
         Assert::IsFalse(e_a.compatible(datatype_t::dict));
         Assert::IsFalse(e_d.compatible(datatype_t::array));
         Assert::IsFalse(e_n.compatible(datatype_t::integer));
         Assert::IsFalse(e_o.compatible(datatype_t::integer));
         Assert::IsFalse(e_y.compatible(datatype_t::integer));
      }

      TEST_METHOD(element_reset)
      {
         auto o = object_t::make();
         data_t y;

         dict_t d;
         d[voc::rock] = 33;
         d[voc::pebble] = 4;
         d[voc::sand] = 5;

         array_t a;
         a.grow() = 55;
         a.grow() = 66;
         a.grow() = 77;

         element_t e_u;
         element_t e_t1(text_t(L"text"));
         element_t e_t2(L"strptr");
         element_t e_c1('c');
         element_t e_c2(L'w');
         element_t e_b(true);
         element_t e_i2((int16_t)2);
         element_t e_i1((int32_t)1);
         element_t e_i3((int64_t)3);
         element_t e_u1((uint16_t)4u);
         element_t e_u2((uint32_t)5u);
         element_t e_u3((uint64_t)6u);
         element_t e_r1(7.0f);
         element_t e_r2(8.0);
         element_t e_a(a);
         element_t e_d(d);
         element_t e_n(voc::rock);
         element_t e_o(o);
         element_t e_y(y);

         e_u.reset();
         e_t1.reset();
         e_t2.reset();
         e_c1.reset();
         e_c2.reset();
         e_b.reset();
         e_i2.reset();
         e_i1.reset();
         e_i3.reset();
         e_u1.reset();
         e_u2.reset();
         e_u3.reset();
         e_r1.reset();
         e_r2.reset();
         e_a.reset();
         e_d.reset();
         e_n.reset();
         e_o.reset();
         e_y.reset();

         Assert::AreEqual(datatype_t::unknown, e_u.type());
         Assert::AreEqual(datatype_t::unknown, e_t1.type());
         Assert::AreEqual(datatype_t::unknown, e_t2.type());
         Assert::AreEqual(datatype_t::unknown, e_c1.type());
         Assert::AreEqual(datatype_t::unknown, e_c2.type());
         Assert::AreEqual(datatype_t::unknown, e_b.type());
         Assert::AreEqual(datatype_t::unknown, e_i2.type());
         Assert::AreEqual(datatype_t::unknown, e_i1.type());
         Assert::AreEqual(datatype_t::unknown, e_i3.type());
         Assert::AreEqual(datatype_t::unknown, e_u1.type());
         Assert::AreEqual(datatype_t::unknown, e_u2.type());
         Assert::AreEqual(datatype_t::unknown, e_u3.type());
         Assert::AreEqual(datatype_t::unknown, e_r1.type());
         Assert::AreEqual(datatype_t::unknown, e_r2.type());
         Assert::AreEqual(datatype_t::unknown, e_a.type());
         Assert::AreEqual(datatype_t::unknown, e_d.type());
         Assert::AreEqual(datatype_t::unknown, e_n.type());
         Assert::AreEqual(datatype_t::unknown, e_o.type());
         Assert::AreEqual(datatype_t::unknown, e_y.type());
      }

      TEST_METHOD(element_ensure)
      {
         element_t e_u;
         element_t e_t1;
         element_t e_t2;
         element_t e_c1;
         element_t e_c2;
         element_t e_b;
         element_t e_i2;
         element_t e_i1;
         element_t e_i3;
         element_t e_u1;
         element_t e_u2;
         element_t e_u3;
         element_t e_r1;
         element_t e_r2;
         element_t e_a;
         element_t e_d;
         element_t e_n;
         element_t e_o;
         element_t e_y;

         e_u.ensure(datatype_t::unknown);
         e_t1.ensure(datatype_t::text);
         e_t2.ensure(datatype_t::text);
         e_c1.ensure(datatype_t::integer);
         e_c2.ensure(datatype_t::integer);
         e_b.ensure(datatype_t::boolean);
         e_i2.ensure(datatype_t::integer);
         e_i1.ensure(datatype_t::integer);
         e_i3.ensure(datatype_t::integer);
         e_u1.ensure(datatype_t::integer);
         e_u2.ensure(datatype_t::integer);
         e_u3.ensure(datatype_t::integer);
         e_r1.ensure(datatype_t::real);
         e_r2.ensure(datatype_t::real);
         e_a.ensure(datatype_t::array);
         e_d.ensure(datatype_t::dict);
         e_n.ensure(datatype_t::name);
         e_o.ensure(datatype_t::ref);
         e_y.ensure(datatype_t::data);

         Assert::AreEqual(datatype_t::unknown, e_u.type());
         Assert::AreEqual(datatype_t::text, e_t1.type());
         Assert::AreEqual(datatype_t::text, e_t2.type());
         Assert::AreEqual(datatype_t::integer, e_c1.type());
         Assert::AreEqual(datatype_t::integer, e_c2.type());
         Assert::AreEqual(datatype_t::boolean, e_b.type());
         Assert::AreEqual(datatype_t::integer, e_i2.type());
         Assert::AreEqual(datatype_t::integer, e_i1.type());
         Assert::AreEqual(datatype_t::integer, e_i3.type());
         Assert::AreEqual(datatype_t::integer, e_u1.type());
         Assert::AreEqual(datatype_t::integer, e_u2.type());
         Assert::AreEqual(datatype_t::integer, e_u3.type());
         Assert::AreEqual(datatype_t::real, e_r1.type());
         Assert::AreEqual(datatype_t::real, e_r2.type());
         Assert::AreEqual(datatype_t::array, e_a.type());
         Assert::AreEqual(datatype_t::dict, e_d.type());
         Assert::AreEqual(datatype_t::name, e_n.type());
         Assert::AreEqual(datatype_t::ref, e_o.type());
         Assert::AreEqual(datatype_t::data, e_y.type());
      }

      TEST_METHOD(element_ensure_preserve_value)
      {
         auto o = object_t::make();
         data_t y;

         dict_t d;
         d[voc::rock] = 33;
         d[voc::pebble] = 4;
         d[voc::sand] = 5;

         array_t a;
         a.grow() = 55;
         a.grow() = 66;
         a.grow() = 77;

         element_t e_u;
         element_t e_t1(text_t(L"text"));
         element_t e_t2(L"strptr");
         element_t e_c1('c');
         element_t e_c2(L'w');
         element_t e_b(true);
         element_t e_i2((int16_t)2);
         element_t e_i1((int32_t)1);
         element_t e_i3((int64_t)3);
         element_t e_u1((uint16_t)4u);
         element_t e_u2((uint32_t)5u);
         element_t e_u3((uint64_t)6u);
         element_t e_r1(7.0f);
         element_t e_r2(8.0);
         element_t e_a(a);
         element_t e_d(d);
         element_t e_n(voc::rock);
         element_t e_o(o);
         element_t e_y(y);

         // Ensuring the same type should not reset the value.
         e_u.ensure(datatype_t::unknown);
         e_t1.ensure(datatype_t::text);
         e_t2.ensure(datatype_t::text);
         e_c1.ensure(datatype_t::integer);
         e_c2.ensure(datatype_t::integer);
         e_b.ensure(datatype_t::boolean);
         e_i2.ensure(datatype_t::integer);
         e_i1.ensure(datatype_t::integer);
         e_i3.ensure(datatype_t::integer);
         e_u1.ensure(datatype_t::integer);
         e_u2.ensure(datatype_t::integer);
         e_u3.ensure(datatype_t::integer);
         e_r1.ensure(datatype_t::real);
         e_r2.ensure(datatype_t::real);
         e_a.ensure(datatype_t::array);
         e_d.ensure(datatype_t::dict);
         e_n.ensure(datatype_t::name);
         e_o.ensure(datatype_t::ref);
         e_y.ensure(datatype_t::data);

         Assert::AreEqual(datatype_t::unknown, e_u.type());
         Assert::AreEqual(datatype_t::text, e_t1.type());
         Assert::AreEqual(datatype_t::text, e_t2.type());
         Assert::AreEqual(datatype_t::integer, e_c1.type());
         Assert::AreEqual(datatype_t::integer, e_c2.type());
         Assert::AreEqual(datatype_t::boolean, e_b.type());
         Assert::AreEqual(datatype_t::integer, e_i2.type());
         Assert::AreEqual(datatype_t::integer, e_i1.type());
         Assert::AreEqual(datatype_t::integer, e_i3.type());
         Assert::AreEqual(datatype_t::integer, e_u1.type());
         Assert::AreEqual(datatype_t::integer, e_u2.type());
         Assert::AreEqual(datatype_t::integer, e_u3.type());
         Assert::AreEqual(datatype_t::real, e_r1.type());
         Assert::AreEqual(datatype_t::real, e_r2.type());
         Assert::AreEqual(datatype_t::array, e_a.type());
         Assert::AreEqual(datatype_t::dict, e_d.type());
         Assert::AreEqual(datatype_t::name, e_n.type());
         Assert::AreEqual(datatype_t::ref, e_o.type());
         Assert::AreEqual(datatype_t::data, e_y.type());

         Assert::AreEqual<int32_t>(0, e_u);
         Assert::AreEqual<text_t>(text_t(L"text"), e_t1);
         Assert::AreEqual<text_t>(L"strptr", e_t2);
         Assert::AreEqual<char>('c', e_c1);
         Assert::AreEqual<wchar_t>(L'w', e_c2);
         Assert::AreEqual<bool>(true, e_b);
         Assert::AreEqual<int16_t>((int16_t)2, e_i2);
         Assert::AreEqual<int32_t>((int32_t)1, e_i1);
         Assert::AreEqual<int64_t>((int64_t)3, e_i3);
         Assert::AreEqual<uint16_t>((uint16_t)4u, e_u1);
         Assert::AreEqual<uint32_t>((uint32_t)5u, e_u2);
         Assert::AreEqual<uint64_t>((uint64_t)6u, e_u3);
         Assert::AreEqual<float>(7.0f, e_r1);
         Assert::AreEqual<double>(8.0, e_r2);
         Assert::AreEqual<array_t>(a, e_a);
         Assert::AreEqual<dict_t>(d, e_d);
         Assert::AreEqual<name_t>(voc::rock, e_n);
         Assert::AreEqual<valid_ref_t<object_t>>(o, e_o);
         Assert::AreEqual<any_t>(y, e_y);

         // Ensuring a similar type should preserve most of the value.
         e_u.ensure(datatype_t::integer);
         e_t1.ensure(datatype_t::boolean);
         e_t2.ensure(datatype_t::boolean);
         e_c1.ensure(datatype_t::real);
         e_c2.ensure(datatype_t::real);
         e_b.ensure(datatype_t::real);
         e_i2.ensure(datatype_t::real);
         e_i1.ensure(datatype_t::real);
         e_i3.ensure(datatype_t::real);
         e_u1.ensure(datatype_t::real);
         e_u2.ensure(datatype_t::boolean);
         e_u3.ensure(datatype_t::boolean);
         e_r1.ensure(datatype_t::integer);
         e_r2.ensure(datatype_t::boolean);
         e_a.ensure(datatype_t::boolean);
         e_d.ensure(datatype_t::boolean);
         e_n.ensure(datatype_t::boolean);
         e_o.ensure(datatype_t::boolean);
         e_y.ensure(datatype_t::boolean);

         Assert::AreEqual<int64_t>(0, e_u);
         Assert::AreEqual<bool>(true, e_t1);
         Assert::AreEqual<bool>(true, e_t2);
         Assert::AreEqual<double>(99., e_c1);
         Assert::AreEqual<double>(119., e_c2);
         Assert::AreEqual<bool>(1., e_b);
         Assert::AreEqual<double>(2., e_i2);
         Assert::AreEqual<double>(1., e_i1);
         Assert::AreEqual<double>(3., e_i3);
         Assert::AreEqual<double>(4., e_u1);
         Assert::AreEqual<bool>(true, e_u2);
         Assert::AreEqual<bool>(true, e_u3);
         Assert::AreEqual<int64_t>(7, e_r1);
         Assert::AreEqual<bool>(true, e_r2);
         Assert::AreEqual<bool>(true, e_a);
         Assert::AreEqual<bool>(true, e_d);
         Assert::AreEqual<bool>(true, e_n);
         Assert::AreEqual<bool>(true, e_o);
         Assert::AreEqual<bool>(true, e_y);
      }

      TEST_METHOD(element_verify)
      {
         auto o = object_t::make();
         data_t y;

         dict_t d;
         d[voc::rock] = 33;
         d[voc::pebble] = 4;
         d[voc::sand] = 5;

         array_t a;
         a.grow() = 55;
         a.grow() = 66;
         a.grow() = 77;

         element_t e_u;
         element_t e_t1(text_t(L"text"));
         element_t e_t2(L"strptr");
         element_t e_c1('c');
         element_t e_c2(L'w');
         element_t e_b(true);
         element_t e_i2((int16_t)2);
         element_t e_i1((int32_t)1);
         element_t e_i3((int64_t)3);
         element_t e_u1((uint16_t)4u);
         element_t e_u2((uint32_t)5u);
         element_t e_u3((uint64_t)6u);
         element_t e_r1(7.0f);
         element_t e_r2(8.0);
         element_t e_a(a);
         element_t e_d(d);
         element_t e_n(voc::rock);
         element_t e_o(o);
         element_t e_y(y);

         // Verifying the same type should not reset the value.
         e_u.verify(datatype_t::unknown);
         e_t1.verify(datatype_t::text);
         e_t2.verify(datatype_t::text);
         e_c1.verify(datatype_t::integer);
         e_c2.verify(datatype_t::integer);
         e_b.verify(datatype_t::boolean);
         e_i2.verify(datatype_t::integer);
         e_i1.verify(datatype_t::integer);
         e_i3.verify(datatype_t::integer);
         e_u1.verify(datatype_t::integer);
         e_u2.verify(datatype_t::integer);
         e_u3.verify(datatype_t::integer);
         e_r1.verify(datatype_t::real);
         e_r2.verify(datatype_t::real);
         e_a.verify(datatype_t::array);
         e_d.verify(datatype_t::dict);
         e_n.verify(datatype_t::name);
         e_o.verify(datatype_t::ref);
         e_y.verify(datatype_t::data);

         Assert::AreEqual(datatype_t::unknown, e_u.type());
         Assert::AreEqual(datatype_t::text, e_t1.type());
         Assert::AreEqual(datatype_t::text, e_t2.type());
         Assert::AreEqual(datatype_t::integer, e_c1.type());
         Assert::AreEqual(datatype_t::integer, e_c2.type());
         Assert::AreEqual(datatype_t::boolean, e_b.type());
         Assert::AreEqual(datatype_t::integer, e_i2.type());
         Assert::AreEqual(datatype_t::integer, e_i1.type());
         Assert::AreEqual(datatype_t::integer, e_i3.type());
         Assert::AreEqual(datatype_t::integer, e_u1.type());
         Assert::AreEqual(datatype_t::integer, e_u2.type());
         Assert::AreEqual(datatype_t::integer, e_u3.type());
         Assert::AreEqual(datatype_t::real, e_r1.type());
         Assert::AreEqual(datatype_t::real, e_r2.type());
         Assert::AreEqual(datatype_t::array, e_a.type());
         Assert::AreEqual(datatype_t::dict, e_d.type());
         Assert::AreEqual(datatype_t::name, e_n.type());
         Assert::AreEqual(datatype_t::ref, e_o.type());
         Assert::AreEqual(datatype_t::data, e_y.type());

         Assert::AreEqual<int32_t>(0, e_u);
         Assert::AreEqual<text_t>(text_t(L"text"), e_t1);
         Assert::AreEqual<text_t>(L"strptr", e_t2);
         Assert::AreEqual<char>('c', e_c1);
         Assert::AreEqual<wchar_t>(L'w', e_c2);
         Assert::AreEqual<bool>(true, e_b);
         Assert::AreEqual<int16_t>((int16_t)2, e_i2);
         Assert::AreEqual<int32_t>((int32_t)1, e_i1);
         Assert::AreEqual<int64_t>((int64_t)3, e_i3);
         Assert::AreEqual<uint16_t>((uint16_t)4u, e_u1);
         Assert::AreEqual<uint32_t>((uint32_t)5u, e_u2);
         Assert::AreEqual<uint64_t>((uint64_t)6u, e_u3);
         Assert::AreEqual<float>(7.0f, e_r1);
         Assert::AreEqual<double>(8.0, e_r2);
         Assert::AreEqual<array_t>(a, e_a);
         Assert::AreEqual<dict_t>(d, e_d);
         Assert::AreEqual<name_t>(voc::rock, e_n);
         Assert::AreEqual<valid_ref_t<object_t>>(o, e_o);
         Assert::AreEqual<any_t>(y, e_y);
      }

      TEST_METHOD(element_int64_operators)
      {
         element_t e;

         Assert::AreEqual<int64_t>(0, e);

         e += 2;
         Assert::AreEqual<int64_t>(2, e);

         e -= 7;
         Assert::AreEqual<int64_t>(-5, e);

         e *= 3;
         Assert::AreEqual<int64_t>(-15, e);

         e /= -5;
         Assert::AreEqual<int64_t>(3, e);

         e &= 1;
         Assert::AreEqual<int64_t>(1, e);

         e |= 10;
         Assert::AreEqual<int64_t>(11, e);

         e ^= 8;
         Assert::AreEqual<int64_t>(3, e);

         e <<= 2;
         Assert::AreEqual<int64_t>(12, e);

         e >>= 1;
         Assert::AreEqual<int64_t>(6, e);

         e += 2.5;
         Assert::AreEqual<double>(8.5, e);

         e -= 0.99;
         Assert::AreEqual<double>(7.51, e);

         e *= 0.5;
         Assert::AreEqual<double>(3.755, e);

         e /= 2.1;
         Assert::AreEqual<double>(3.755 / 2.1, e);

         e = text_t(L"hello");
         Assert::AreEqual<text_t>(L"hello", e);

         e += L", world!";
         Assert::AreEqual<text_t>(L"hello, world!", e);

         e = L"bye";
         Assert::AreEqual<text_t>(L"bye", e);
      }

      TEST_METHOD(element_double_operators)
      {
         element_t e;

         e = 0.0;

         Assert::AreEqual<double>(0, e);

         e += 2;
         Assert::AreEqual<double>(2, e);

         e -= 7;
         Assert::AreEqual<double>(-5, e);

         e *= 3;
         Assert::AreEqual<double>(-15, e);

         e /= -5;
         Assert::AreEqual<double>(3, e);

         e &= 1;
         Assert::AreEqual<double>(1, e);

         e |= 10;
         Assert::AreEqual<double>(11, e);

         e ^= 8;
         Assert::AreEqual<double>(3, e);

         e <<= 2;
         Assert::AreEqual<double>(12, e);

         e >>= 1;
         Assert::AreEqual<double>(6, e);

         e += 2.5;
         Assert::AreEqual<double>(8.5, e);

         e -= 0.99;
         Assert::AreEqual<double>(7.51, e);

         e *= 0.5;
         Assert::AreEqual<double>(3.755, e);

         e /= 2.1;
         Assert::AreEqual<double>(3.755 / 2.1, e);

         e = text_t(L"hello");
         Assert::AreEqual<text_t>(L"hello", e);

         e += L", world!";
         Assert::AreEqual<text_t>(L"hello, world!", e);

         e = L"bye";
         Assert::AreEqual<text_t>(L"bye", e);
      }

      TEST_METHOD(element_bool_operator)
      {
         auto o = object_t::make();
         data_t y;

         element_t e_u;
         element_t e_t1(L"");
         element_t e_t2(text_t(L""));
         element_t e_c1('\0');
         element_t e_c2(L'\0');
         element_t e_b(false);
         element_t e_i2((int16_t)0);
         element_t e_i1((int32_t)0);
         element_t e_i3((int64_t)0);
         element_t e_u1((uint16_t)0);
         element_t e_u2((uint32_t)0);
         element_t e_u3((uint64_t)0);
         element_t e_r1(0.f);
         element_t e_r2(0.);
         element_t e_a(array_t::empty);
         element_t e_d(dict_t::empty);
         element_t e_n((voc::rock));
         element_t e_o(o);
         element_t e_y(y);

         Assert::AreEqual<bool>(false, e_u);
         Assert::AreEqual<bool>(false, e_t1);
         Assert::AreEqual<bool>(false, e_t2);
         Assert::AreEqual<bool>(false, e_c1);
         Assert::AreEqual<bool>(false, e_c2);
         Assert::AreEqual<bool>(false, e_b);
         Assert::AreEqual<bool>(false, e_i2);
         Assert::AreEqual<bool>(false, e_i1);
         Assert::AreEqual<bool>(false, e_i3);
         Assert::AreEqual<bool>(false, e_u1);
         Assert::AreEqual<bool>(false, e_u2);
         Assert::AreEqual<bool>(false, e_u3);
         Assert::AreEqual<bool>(false, e_r1);
         Assert::AreEqual<bool>(false, e_r2);
         Assert::AreEqual<bool>(false, e_a);
         Assert::AreEqual<bool>(false, e_d);
         Assert::AreEqual<bool>(true, e_n);
         Assert::AreEqual<bool>(true, e_o);
         Assert::AreEqual<bool>(true, e_y);

         dict_t d;
         d[voc::rock] = 33;
         d[voc::pebble] = 4;
         d[voc::sand] = 5;

         array_t a;
         a.grow() = 55;
         a.grow() = 66;
         a.grow() = 77;

         e_u = element_t();
         e_t1 = text_t(L"text");
         e_t2 = L"strptr";
         e_c1 = 'c';
         e_c2 = L'w';
         e_b = true;
         e_i2 = (int16_t)2;
         e_i1 = (int32_t)1;
         e_i3 = (int64_t)3;
         e_u1 = (uint16_t)4u;
         e_u2 = (uint32_t)5u;
         e_u3 = (uint64_t)6u;
         e_r1 = 7.0f;
         e_r2 = 8.0;
         e_a = a;
         e_d = d;
         e_n = voc::rock;
         e_o = object_t::make();
         e_y = data_t();

         Assert::AreEqual<bool>(false, e_u);
         Assert::AreEqual<bool>(true, e_t1);
         Assert::AreEqual<bool>(true, e_t2);
         Assert::AreEqual<bool>(true, e_c1);
         Assert::AreEqual<bool>(true, e_c2);
         Assert::AreEqual<bool>(true, e_b);
         Assert::AreEqual<bool>(true, e_i2);
         Assert::AreEqual<bool>(true, e_i1);
         Assert::AreEqual<bool>(true, e_i3);
         Assert::AreEqual<bool>(true, e_u1);
         Assert::AreEqual<bool>(true, e_u2);
         Assert::AreEqual<bool>(true, e_u3);
         Assert::AreEqual<bool>(true, e_r1);
         Assert::AreEqual<bool>(true, e_r2);
         Assert::AreEqual<bool>(true, e_a);
         Assert::AreEqual<bool>(true, e_d);
         Assert::AreEqual<bool>(true, e_n);
         Assert::AreEqual<bool>(true, e_o);
         Assert::AreEqual<bool>(true, e_y);
      }

      TEST_METHOD(element_array)
      {
         array_t a;
         a.grow() = 55;
         a.grow() = 66.;
         a.grow() = 77.f;

         element_t e;

         e.grow() = 11;
         e.grow() = 22;

         e.insert(0) = 33;

         e.erase(1);

         e.append(a);

         Assert::AreEqual<index_t>(5, e.size());
         Assert::AreEqual<int32_t>(33, e[0]);
         Assert::AreEqual<int32_t>(22, e[1]);
         Assert::AreEqual<int32_t>(55, e[2]);
         Assert::AreEqual<double>(66., e[3]);
         Assert::AreEqual<float>(77.f, e[4]);
      }

      TEST_METHOD(element_dict)
      {
         dict_t d;
         d[voc::rock] = 33.;
         d[voc::pebble] = 4;
         d[voc::sand] = 5.f;

         element_t e;

         e[voc::age] = 55.;
         e.append(d);
         e.erase(voc::rock);
         e.erase(voc::pebble);

         Assert::IsFalse(e.contains(voc::pebble));
         Assert::IsTrue(e.contains(voc::sand));
         Assert::IsTrue(e.contains(voc::age));
         Assert::IsFalse(e.contains(voc::rock));

         Assert::AreEqual<index_t>(2, e.size());
         Assert::AreEqual<float>(5.f, e[voc::sand]);
         Assert::AreEqual<double>(55., e[voc::age]);
      }
   };
}
