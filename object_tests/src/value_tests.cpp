#include "CppUnitTest.h"

#include "dak/object/value.h"
#include "dak/object/object.h"
#include "dak/object/voc.h"
#include "dak/object/tests/helpers.h"

#include <dak/any_op/compare_op.h>
#include <dak/any_op/size_op.h>
#include <dak/any_op/construct_op.h>
#include <dak/any_op/convert_op.h>
#include <dak/any_op/is_compatible_op.h>

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

         std::function<bool()> is_compatible([]() -> bool { return true; });

         size_op_t::make<>::op<uint64_t, data_t>([](const data_t& arg_a) -> uint64_t { return 77u; });
         is_compatible_op_t::make<data_t, data_t>::op<bool>(is_compatible);
         construct_op_t::make<data_t>::op<data_t>((std::function<data_t()>)[]() -> data_t { return data_t(); });
         convert_op_t::make<bool>::op<bool, data_t>([](const data_t& arg_b) -> bool { return true; });
         convert_op_t::make<data_t>::op<data_t, data_t>([](const data_t& arg_b) -> data_t { return arg_b; });
      }
   }


   TEST_CLASS(value_tests)
	{
	public:
      value_tests()
      {
         register_data_ops();
         any_op::register_ops();
         register_object_ops();
      }

		TEST_METHOD(value_base)
		{

         value_t e;

         Assert::AreEqual(e, value_t());
         Assert::AreEqual(e, value_t::empty);
         Assert::AreNotEqual(e, value_t(1));

         Assert::IsTrue( e == value_t());
         Assert::IsTrue(e == value_t::empty);
         Assert::IsFalse(e != value_t());

         Assert::IsFalse(e == value_t(1));
         Assert::IsFalse(value_t::empty == value_t(1));
         Assert::IsTrue(e != value_t(1));

         Assert::IsTrue(value_t(2) > value_t(1));
         Assert::IsTrue(value_t(1) < value_t(2));

         Assert::IsFalse(value_t(1) > value_t(2));
         Assert::IsFalse(value_t(2) < value_t(1));

         Assert::IsFalse(value_t(2) < value_t(L"hello"));
      }

      TEST_METHOD(value_constructors)
      {
         valid_ref_t o = object_t::make();
         data_t y;

         value_t e_u;
         value_t e_t1(text_t(L"text"));
         value_t e_t2(L"strptr");
         value_t e_c1('c');
         value_t e_c2(L'w');
         value_t e_b(true);
         value_t e_i2((int16_t)2);
         value_t e_i1((int32_t)1);
         value_t e_i3((int64_t)3);
         value_t e_u1((uint16_t)4u);
         value_t e_u2((uint32_t)5u);
         value_t e_u3((uint64_t)6u);
         value_t e_r1(7.0f);
         value_t e_r2(8.0);
         value_t e_a((array_t()));
         value_t e_d((dict_t()));
         value_t e_n(voc::rock);
         value_t e_o(o);
         value_t e_y(y);

         Assert::AreEqual(typeid(void), e_u.get_type());
         Assert::AreEqual(typeid(text_t), e_t1.get_type());
         Assert::AreEqual(typeid(text_t), e_t2.get_type());
         Assert::AreEqual(typeid(char), e_c1.get_type());
         Assert::AreEqual(typeid(wchar_t), e_c2.get_type());
         Assert::AreEqual(typeid(bool), e_b.get_type());
         Assert::AreEqual(typeid(int16_t), e_i2.get_type());
         Assert::AreEqual(typeid(int32_t), e_i1.get_type());
         Assert::AreEqual(typeid(int64_t), e_i3.get_type());
         Assert::AreEqual(typeid(uint16_t), e_u1.get_type());
         Assert::AreEqual(typeid(uint32_t), e_u2.get_type());
         Assert::AreEqual(typeid(uint64_t), e_u3.get_type());
         Assert::AreEqual(typeid(float), e_r1.get_type());
         Assert::AreEqual(typeid(double), e_r2.get_type());
         Assert::AreEqual(typeid(array_t), e_a.get_type());
         Assert::AreEqual(typeid(dict_t), e_d.get_type());
         Assert::AreEqual(typeid(name_t), e_n.get_type());
         Assert::AreEqual(typeid(ref_t<object_t>), e_o.get_type());
         Assert::AreEqual(typeid(data_t), e_y.get_type());
      }

      TEST_METHOD(value_assignments)
      {
         auto o = object_t::make();
         data_t y;

         value_t e_u;
         value_t e_t1;
         value_t e_t2;
         value_t e_c1;
         value_t e_c2;
         value_t e_b;
         value_t e_i2;
         value_t e_i1;
         value_t e_i3;
         value_t e_u1;
         value_t e_u2;
         value_t e_u3;
         value_t e_r1;
         value_t e_r2;
         value_t e_a;
         value_t e_d;
         value_t e_n;
         value_t e_o;
         value_t e_y;

         e_u  = value_t();
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

         Assert::AreEqual(typeid(void), e_u.get_type());
         Assert::AreEqual(typeid(text_t), e_t1.get_type());
         Assert::AreEqual(typeid(text_t), e_t2.get_type());
         Assert::AreEqual(typeid(char), e_c1.get_type());
         Assert::AreEqual(typeid(wchar_t), e_c2.get_type());
         Assert::AreEqual(typeid(bool), e_b.get_type());
         Assert::AreEqual(typeid(int16_t), e_i2.get_type());
         Assert::AreEqual(typeid(int32_t), e_i1.get_type());
         Assert::AreEqual(typeid(int64_t), e_i3.get_type());
         Assert::AreEqual(typeid(uint16_t), e_u1.get_type());
         Assert::AreEqual(typeid(uint32_t), e_u2.get_type());
         Assert::AreEqual(typeid(uint64_t), e_u3.get_type());
         Assert::AreEqual(typeid(float), e_r1.get_type());
         Assert::AreEqual(typeid(double), e_r2.get_type());
         Assert::AreEqual(typeid(array_t), e_a.get_type());
         Assert::AreEqual(typeid(dict_t), e_d.get_type());
         Assert::AreEqual(typeid(name_t), e_n.get_type());
         Assert::AreEqual(typeid(ref_t<object_t>), e_o.get_type());
         Assert::AreEqual(typeid(data_t), e_y.get_type());
      }

      TEST_METHOD(value_text_assignments)
      {
         value_t e1;

         e1 = L"hello";
         Assert::AreEqual<text_t>(text_t(L"hello"), e1);

         e1 = (str_ptr_t)nullptr;
         Assert::AreEqual<text_t>(text_t(), e1);

         e1 = L"bye";
         Assert::AreEqual<text_t>(text_t(L"bye"), e1);

         e1.reset(typeid(text_t));
         Assert::AreEqual<text_t>(text_t(), e1);

         e1 = L"bye";
         Assert::AreEqual<text_t>(text_t(L"bye"), e1);

         e1.verify(typeid(text_t));
         Assert::AreEqual<text_t>(text_t(L"bye"), e1);
      }

      TEST_METHOD(value_conversion)
      {
         auto o = object_t::make();
         data_t y;

         dict_t d;
         d[voc::rock] = 45;

         array_t a;
         a.grow() = 3.0;

         value_t e_u;
         value_t e_t1(text_t(L"text"));
         value_t e_t2(L"strptr");
         value_t e_c1('c');
         value_t e_c2(L'w');
         value_t e_b(true);
         value_t e_i2((int16_t)2);
         value_t e_i1((int32_t)1);
         value_t e_i3((int64_t)3);
         value_t e_u1((uint16_t)4u);
         value_t e_u2((uint32_t)5u);
         value_t e_u3((uint64_t)6u);
         value_t e_r1(7.0f);
         value_t e_r2(8.0);
         value_t e_a(a);
         value_t e_d(d);
         value_t e_n(voc::rock);
         value_t e_o(o);
         value_t e_y(y);

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
         Assert::AreEqual<ref_t<object_t>>(o, e_o);
         Assert::AreEqual<any_t>(any_t(y), e_y);

         Assert::IsFalse(e_i3[voc::rock].is_valid());
         Assert::IsFalse(e_i3[2].is_valid());

         Assert::AreEqual<int32_t>(45, e_d[voc::rock]);
         Assert::AreEqual<double>(3.0, e_a[0]);
      }

      TEST_METHOD(value_const_conversion)
      {
         auto o = object_t::make();
         data_t y;

         dict_t d;
         d[voc::rock] = 45;

         array_t a;
         a.grow() = 3.0;

         const value_t e_u;
         const value_t e_t1(text_t(L"text"));
         const value_t e_t2(L"strptr");
         const value_t e_c1('c');
         const value_t e_c2(L'w');
         const value_t e_b(true);
         const value_t e_i2((int16_t)2);
         const value_t e_i1((int32_t)1);
         const value_t e_i3((int64_t)3);
         const value_t e_u1((uint16_t)4u);
         const value_t e_u2((uint32_t)5u);
         const value_t e_u3((uint64_t)6u);
         const value_t e_r1(7.0f);
         const value_t e_r2(8.0);
         const value_t e_a(a);
         const value_t e_d(d);
         const value_t e_n(voc::rock);
         const value_t e_o(o);
         const value_t e_y(y);

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
         Assert::AreEqual<ref_t<object_t>>(o, e_o);
         Assert::AreEqual<any_t>(any_t(y), e_y);

         Assert::IsFalse(e_i3[voc::rock].is_valid());
         Assert::IsFalse(e_i3[2].is_valid());

         Assert::AreEqual<int32_t>(45, e_d[voc::rock]);
         Assert::AreEqual<double>(3.0, e_a[0]);
      }

      TEST_METHOD(value_unknown_assignments)
      {
         auto o = object_t::make();
         data_t y;

         value_t e_u;
         value_t e_t1(text_t(L"text"));
         value_t e_t2(L"strptr");
         value_t e_c1('c');
         value_t e_c2(L'w');
         value_t e_b(true);
         value_t e_i2((int16_t)2);
         value_t e_i1((int32_t)1);
         value_t e_i3((int64_t)3);
         value_t e_u1((uint16_t)4u);
         value_t e_u2((uint32_t)5u);
         value_t e_u3((uint64_t)6u);
         value_t e_r1(7.0f);
         value_t e_r2(8.0);
         value_t e_a((array_t()));
         value_t e_d((dict_t()));
         value_t e_n(voc::rock);
         value_t e_o(o);
         value_t e_y(y);

         // Assigning an empty value_t of type unknown
         // should set the type to unknown and reset the value.
         e_u = value_t();
         e_t1 = value_t();
         e_t2 = value_t();
         e_c1 = value_t();
         e_c2 = value_t();
         e_b = value_t();
         e_i2 = value_t();
         e_i1 = value_t();
         e_i3 = value_t();
         e_u1 = value_t();
         e_u2 = value_t();
         e_u3 = value_t();
         e_r1 = value_t();
         e_r2 = value_t();
         e_a = value_t();
         e_d = value_t();
         e_n = value_t();
         e_o = value_t();
         e_y = value_t();

         Assert::AreEqual(typeid(void), e_u.get_type());
         Assert::AreEqual(typeid(void), e_t1.get_type());
         Assert::AreEqual(typeid(void), e_t2.get_type());
         Assert::AreEqual(typeid(void), e_c1.get_type());
         Assert::AreEqual(typeid(void), e_c2.get_type());
         Assert::AreEqual(typeid(void), e_b.get_type());
         Assert::AreEqual(typeid(void), e_i2.get_type());
         Assert::AreEqual(typeid(void), e_i1.get_type());
         Assert::AreEqual(typeid(void), e_i3.get_type());
         Assert::AreEqual(typeid(void), e_u1.get_type());
         Assert::AreEqual(typeid(void), e_u2.get_type());
         Assert::AreEqual(typeid(void), e_u3.get_type());
         Assert::AreEqual(typeid(void), e_r1.get_type());
         Assert::AreEqual(typeid(void), e_r2.get_type());
         Assert::AreEqual(typeid(void), e_a.get_type());
         Assert::AreEqual(typeid(void), e_d.get_type());
         Assert::AreEqual(typeid(void), e_n.get_type());
         Assert::AreEqual(typeid(void), e_o.get_type());
         Assert::AreEqual(typeid(void), e_y.get_type());

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
         Assert::AreNotEqual<ref_t<object_t>>(o, e_o);
         Assert::AreNotEqual<any_t>(y, e_y);
      }

      TEST_METHOD(value_size)
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

         const value_t e_u;
         const value_t e_t1(text_t(L"text"));
         const value_t e_t2(L"strptr");
         const value_t e_c1('c');
         const value_t e_c2(L'w');
         const value_t e_b(true);
         const value_t e_i2((int16_t)2);
         const value_t e_i1((int32_t)1);
         const value_t e_i3((int64_t)3);
         const value_t e_u1((uint16_t)4u);
         const value_t e_u2((uint32_t)5u);
         const value_t e_u3((uint64_t)6u);
         const value_t e_r1(7.0f);
         const value_t e_r2(8.0);
         const value_t e_a(a);
         const value_t e_d(d);
         const value_t e_n(voc::rock);
         const value_t e_o(o);
         const value_t e_y(y);

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

      TEST_METHOD(value_compatible)
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

         const value_t e_u;
         const value_t e_t1(text_t(L"text"));
         const value_t e_t2(L"strptr");
         const value_t e_c1('c');
         const value_t e_c2(L'w');
         const value_t e_b(true);
         const value_t e_i2((int16_t)2);
         const value_t e_i1((int32_t)1);
         const value_t e_i3((int64_t)3);
         const value_t e_u1((uint16_t)4u);
         const value_t e_u2((uint32_t)5u);
         const value_t e_u3((uint64_t)6u);
         const value_t e_r1(7.0f);
         const value_t e_r2(8.0);
         const value_t e_a(a);
         const value_t e_d(d);
         const value_t e_n(voc::rock);
         const value_t e_o(o);
         const value_t e_y(y);

         Assert::IsTrue(e_t1.is_compatible(typeid(text_t)));
         Assert::IsTrue(e_t2.is_compatible(typeid(text_t)));
         Assert::IsTrue(e_c1.is_compatible(typeid(char)));
         Assert::IsTrue(e_c2.is_compatible(typeid(wchar_t)));
         Assert::IsTrue(e_b.is_compatible(typeid(bool)));
         Assert::IsTrue(e_i2.is_compatible(typeid(int16_t)));
         Assert::IsTrue(e_i1.is_compatible(typeid(int32_t)));
         Assert::IsTrue(e_i3.is_compatible(typeid(int64_t)));
         Assert::IsTrue(e_u1.is_compatible(typeid(uint16_t)));
         Assert::IsTrue(e_u2.is_compatible(typeid(uint32_t)));
         Assert::IsTrue(e_u3.is_compatible(typeid(uint64_t)));
         Assert::IsTrue(e_r1.is_compatible(typeid(float)));
         Assert::IsTrue(e_r2.is_compatible(typeid(double)));
         Assert::IsTrue(e_a.is_compatible(typeid(array_t)));
         Assert::IsTrue(e_d.is_compatible(typeid(dict_t)));
         Assert::IsTrue(e_n.is_compatible(typeid(name_t)));
         Assert::IsTrue(e_o.is_compatible(typeid(ref_t<object_t>)));
         Assert::IsTrue(e_y.is_compatible(typeid(data_t)));

         Assert::IsTrue(e_b.is_compatible(typeid(int64_t)));
         Assert::IsTrue(e_i2.is_compatible(typeid(bool)));
         Assert::IsTrue(e_i1.is_compatible(typeid(bool)));
         Assert::IsTrue(e_i3.is_compatible(typeid(bool)));
         Assert::IsTrue(e_u1.is_compatible(typeid(bool)));
         Assert::IsTrue(e_u2.is_compatible(typeid(bool)));
         Assert::IsTrue(e_u3.is_compatible(typeid(bool)));
         Assert::IsTrue(e_c1.is_compatible(typeid(double)));
         Assert::IsTrue(e_b.is_compatible(typeid(double)));
         Assert::IsTrue(e_u3.is_compatible(typeid(double)));
         Assert::IsTrue(e_r1.is_compatible(typeid(int64_t)));

         Assert::IsFalse(e_u.is_compatible(typeid(text_t)));
         Assert::IsFalse(e_t1.is_compatible(typeid(int64_t)));
         Assert::IsFalse(e_t2.is_compatible(typeid(int64_t)));
         Assert::IsFalse(e_i2.is_compatible(typeid(text_t)));
         Assert::IsFalse(e_i1.is_compatible(typeid(array_t)));
         Assert::IsFalse(e_i3.is_compatible(typeid(dict_t)));
         Assert::IsFalse(e_u1.is_compatible(typeid(name_t)));
         Assert::IsFalse(e_u2.is_compatible(typeid(ref_t<object_t>)));
         Assert::IsFalse(e_r2.is_compatible(typeid(name_t)));
         Assert::IsFalse(e_a.is_compatible(typeid(dict_t)));
         Assert::IsFalse(e_d.is_compatible(typeid(array_t)));
         Assert::IsFalse(e_n.is_compatible(typeid(int64_t)));
         Assert::IsFalse(e_o.is_compatible(typeid(int64_t)));
         Assert::IsFalse(e_y.is_compatible(typeid(int64_t)));
      }

      TEST_METHOD(value_reset)
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

         value_t e_u;
         value_t e_t1(text_t(L"text"));
         value_t e_t2(L"strptr");
         value_t e_c1('c');
         value_t e_c2(L'w');
         value_t e_b(true);
         value_t e_i2((int16_t)2);
         value_t e_i1((int32_t)1);
         value_t e_i3((int64_t)3);
         value_t e_u1((uint16_t)4u);
         value_t e_u2((uint32_t)5u);
         value_t e_u3((uint64_t)6u);
         value_t e_r1(7.0f);
         value_t e_r2(8.0);
         value_t e_a(a);
         value_t e_d(d);
         value_t e_n(voc::rock);
         value_t e_o(o);
         value_t e_y(y);

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

         Assert::AreEqual(typeid(void), e_u.get_type());
         Assert::AreEqual(typeid(void), e_t1.get_type());
         Assert::AreEqual(typeid(void), e_t2.get_type());
         Assert::AreEqual(typeid(void), e_c1.get_type());
         Assert::AreEqual(typeid(void), e_c2.get_type());
         Assert::AreEqual(typeid(void), e_b.get_type());
         Assert::AreEqual(typeid(void), e_i2.get_type());
         Assert::AreEqual(typeid(void), e_i1.get_type());
         Assert::AreEqual(typeid(void), e_i3.get_type());
         Assert::AreEqual(typeid(void), e_u1.get_type());
         Assert::AreEqual(typeid(void), e_u2.get_type());
         Assert::AreEqual(typeid(void), e_u3.get_type());
         Assert::AreEqual(typeid(void), e_r1.get_type());
         Assert::AreEqual(typeid(void), e_r2.get_type());
         Assert::AreEqual(typeid(void), e_a.get_type());
         Assert::AreEqual(typeid(void), e_d.get_type());
         Assert::AreEqual(typeid(void), e_n.get_type());
         Assert::AreEqual(typeid(void), e_o.get_type());
         Assert::AreEqual(typeid(void), e_y.get_type());

         e_u.reset(typeid(void));
         e_t1.reset(typeid(text_t));
         e_t2.reset(typeid(text_t));
         e_c1.reset(typeid(char));
         e_c2.reset(typeid(wchar_t));
         e_b.reset(typeid(bool));
         e_i2.reset(typeid(int16_t));
         e_i1.reset(typeid(int32_t));
         e_i3.reset(typeid(int64_t));
         e_u1.reset(typeid(uint16_t));
         e_u2.reset(typeid(uint32_t));
         e_u3.reset(typeid(uint64_t));
         e_r1.reset(typeid(float));
         e_r2.reset(typeid(double));
         e_a.reset(typeid(array_t));
         e_d.reset(typeid(dict_t));
         e_n.reset(typeid(name_t));
         e_o.reset(typeid(ref_t<object_t>));
         e_y.reset(typeid(data_t));

         Assert::AreEqual(typeid(void), e_u.get_type());
         Assert::AreEqual(typeid(text_t), e_t1.get_type());
         Assert::AreEqual(typeid(text_t), e_t2.get_type());
         Assert::AreEqual(typeid(char), e_c1.get_type());
         Assert::AreEqual(typeid(wchar_t), e_c2.get_type());
         Assert::AreEqual(typeid(bool), e_b.get_type());
         Assert::AreEqual(typeid(int16_t), e_i2.get_type());
         Assert::AreEqual(typeid(int32_t), e_i1.get_type());
         Assert::AreEqual(typeid(int64_t), e_i3.get_type());
         Assert::AreEqual(typeid(uint16_t), e_u1.get_type());
         Assert::AreEqual(typeid(uint32_t), e_u2.get_type());
         Assert::AreEqual(typeid(uint64_t), e_u3.get_type());
         Assert::AreEqual(typeid(float), e_r1.get_type());
         Assert::AreEqual(typeid(double), e_r2.get_type());
         Assert::AreEqual(typeid(array_t), e_a.get_type());
         Assert::AreEqual(typeid(dict_t), e_d.get_type());
         Assert::AreEqual(typeid(name_t), e_n.get_type());
         Assert::AreEqual(typeid(ref_t<object_t>), e_o.get_type());
         Assert::AreEqual(typeid(data_t), e_y.get_type());
      }

      TEST_METHOD(value_ensure)
      {
         value_t e_u;
         value_t e_t1;
         value_t e_t2;
         value_t e_c1;
         value_t e_c2;
         value_t e_b;
         value_t e_i2;
         value_t e_i1;
         value_t e_i3;
         value_t e_u1;
         value_t e_u2;
         value_t e_u3;
         value_t e_r1;
         value_t e_r2;
         value_t e_a;
         value_t e_d;
         value_t e_n;
         value_t e_o;
         value_t e_y;

         e_u.ensure(typeid(void));
         e_t1.ensure(typeid(text_t));
         e_t2.ensure(typeid(text_t));
         e_c1.ensure(typeid(char));
         e_c2.ensure(typeid(wchar_t));
         e_b.ensure(typeid(bool));
         e_i2.ensure(typeid(int16_t));
         e_i1.ensure(typeid(int32_t));
         e_i3.ensure(typeid(int64_t));
         e_u1.ensure(typeid(uint16_t));
         e_u2.ensure(typeid(uint32_t));
         e_u3.ensure(typeid(uint64_t));
         e_r1.ensure(typeid(float));
         e_r2.ensure(typeid(double));
         e_a.ensure(typeid(array_t));
         e_d.ensure(typeid(dict_t));
         e_n.ensure(typeid(name_t));
         e_o.ensure(typeid(ref_t<object_t>));
         e_y.ensure(typeid(data_t));

         Assert::AreEqual(typeid(void), e_u.get_type());
         Assert::AreEqual(typeid(text_t), e_t1.get_type());
         Assert::AreEqual(typeid(text_t), e_t2.get_type());
         Assert::AreEqual(typeid(char), e_c1.get_type());
         Assert::AreEqual(typeid(wchar_t), e_c2.get_type());
         Assert::AreEqual(typeid(bool), e_b.get_type());
         Assert::AreEqual(typeid(int16_t), e_i2.get_type());
         Assert::AreEqual(typeid(int32_t), e_i1.get_type());
         Assert::AreEqual(typeid(int64_t), e_i3.get_type());
         Assert::AreEqual(typeid(uint16_t), e_u1.get_type());
         Assert::AreEqual(typeid(uint32_t), e_u2.get_type());
         Assert::AreEqual(typeid(uint64_t), e_u3.get_type());
         Assert::AreEqual(typeid(float), e_r1.get_type());
         Assert::AreEqual(typeid(double), e_r2.get_type());
         Assert::AreEqual(typeid(array_t), e_a.get_type());
         Assert::AreEqual(typeid(dict_t), e_d.get_type());
         Assert::AreEqual(typeid(name_t), e_n.get_type());
         Assert::AreEqual(typeid(ref_t<object_t>), e_o.get_type());
         Assert::AreEqual(typeid(data_t), e_y.get_type());
      }

      TEST_METHOD(value_ensure_preserve_value)
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

         value_t e_u;
         value_t e_t1(text_t(L"text"));
         value_t e_t2(L"strptr");
         value_t e_c1('c');
         value_t e_c2(L'w');
         value_t e_b(true);
         value_t e_i2((int16_t)2);
         value_t e_i1((int32_t)1);
         value_t e_i3((int64_t)3);
         value_t e_u1((uint16_t)4u);
         value_t e_u2((uint32_t)5u);
         value_t e_u3((uint64_t)6u);
         value_t e_r1(7.0f);
         value_t e_r2(8.0);
         value_t e_a(a);
         value_t e_d(d);
         value_t e_n(voc::rock);
         value_t e_o(o);
         value_t e_y(y);

         // Ensuring the same type should not reset the value.
         e_u.ensure(typeid(void));
         e_t1.ensure(typeid(text_t));
         e_t2.ensure(typeid(text_t));
         e_c1.ensure(typeid(char));
         e_c2.ensure(typeid(wchar_t));
         e_b.ensure(typeid(bool));
         e_i2.ensure(typeid(int16_t));
         e_i1.ensure(typeid(int32_t));
         e_i3.ensure(typeid(int64_t));
         e_u1.ensure(typeid(uint16_t));
         e_u2.ensure(typeid(uint32_t));
         e_u3.ensure(typeid(uint64_t));
         e_r1.ensure(typeid(float));
         e_r2.ensure(typeid(double));
         e_a.ensure(typeid(array_t));
         e_d.ensure(typeid(dict_t));
         e_n.ensure(typeid(name_t));
         e_o.ensure(typeid(ref_t<object_t>));
         e_y.ensure(typeid(data_t));

         Assert::AreEqual(typeid(void), e_u.get_type());
         Assert::AreEqual(typeid(text_t), e_t1.get_type());
         Assert::AreEqual(typeid(text_t), e_t2.get_type());
         Assert::AreEqual(typeid(char), e_c1.get_type());
         Assert::AreEqual(typeid(wchar_t), e_c2.get_type());
         Assert::AreEqual(typeid(bool), e_b.get_type());
         Assert::AreEqual(typeid(int16_t), e_i2.get_type());
         Assert::AreEqual(typeid(int32_t), e_i1.get_type());
         Assert::AreEqual(typeid(int64_t), e_i3.get_type());
         Assert::AreEqual(typeid(uint16_t), e_u1.get_type());
         Assert::AreEqual(typeid(uint32_t), e_u2.get_type());
         Assert::AreEqual(typeid(uint64_t), e_u3.get_type());
         Assert::AreEqual(typeid(float), e_r1.get_type());
         Assert::AreEqual(typeid(double), e_r2.get_type());
         Assert::AreEqual(typeid(array_t), e_a.get_type());
         Assert::AreEqual(typeid(dict_t), e_d.get_type());
         Assert::AreEqual(typeid(name_t), e_n.get_type());
         Assert::AreEqual(typeid(ref_t<object_t>), e_o.get_type());
         Assert::AreEqual(typeid(data_t), e_y.get_type());

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
         Assert::AreEqual<ref_t<object_t>>(o, e_o);
         Assert::AreEqual<any_t>(y, e_y);

         // Ensuring a similar type should preserve most of the value.
         e_u.ensure(typeid(int64_t));
         e_t1.ensure(typeid(bool));
         e_t2.ensure(typeid(bool));
         e_c1.ensure(typeid(double));
         e_c2.ensure(typeid(double));
         e_b.ensure(typeid(double));
         e_i2.ensure(typeid(double));
         e_i1.ensure(typeid(double));
         e_i3.ensure(typeid(double));
         e_u1.ensure(typeid(double));
         e_u2.ensure(typeid(bool));
         e_u3.ensure(typeid(bool));
         e_r1.ensure(typeid(int64_t));
         e_r2.ensure(typeid(bool));
         e_a.ensure(typeid(bool));
         e_d.ensure(typeid(bool));
         e_n.ensure(typeid(bool));
         e_o.ensure(typeid(bool));
         e_y.ensure(typeid(bool));

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

      TEST_METHOD(value_verify)
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

         value_t e_u;
         value_t e_t1(text_t(L"text"));
         value_t e_t2(L"strptr");
         value_t e_c1('c');
         value_t e_c2(L'w');
         value_t e_b(true);
         value_t e_i2((int16_t)2);
         value_t e_i1((int32_t)1);
         value_t e_i3((int64_t)3);
         value_t e_u1((uint16_t)4u);
         value_t e_u2((uint32_t)5u);
         value_t e_u3((uint64_t)6u);
         value_t e_r1(7.0f);
         value_t e_r2(8.0);
         value_t e_a(a);
         value_t e_d(d);
         value_t e_n(voc::rock);
         value_t e_o(o);
         value_t e_y(y);

         // Verifying the same type should not reset the value.
         e_u.verify(typeid(void));
         e_t1.verify(typeid(text_t));
         e_t2.verify(typeid(text_t));
         e_c1.verify(typeid(char));
         e_c2.verify(typeid(wchar_t));
         e_b.verify(typeid(bool));
         e_i2.verify(typeid(int16_t));
         e_i1.verify(typeid(int32_t));
         e_i3.verify(typeid(int64_t));
         e_u1.verify(typeid(uint16_t));
         e_u2.verify(typeid(uint32_t));
         e_u3.verify(typeid(uint64_t));
         e_r1.verify(typeid(float));
         e_r2.verify(typeid(double));
         e_a.verify(typeid(array_t));
         e_d.verify(typeid(dict_t));
         e_n.verify(typeid(name_t));
         e_o.verify(typeid(ref_t<object_t>));
         e_y.verify(typeid(data_t));

         Assert::AreEqual(typeid(void), e_u.get_type());
         Assert::AreEqual(typeid(text_t), e_t1.get_type());
         Assert::AreEqual(typeid(text_t), e_t2.get_type());
         Assert::AreEqual(typeid(char), e_c1.get_type());
         Assert::AreEqual(typeid(wchar_t), e_c2.get_type());
         Assert::AreEqual(typeid(bool), e_b.get_type());
         Assert::AreEqual(typeid(int16_t), e_i2.get_type());
         Assert::AreEqual(typeid(int32_t), e_i1.get_type());
         Assert::AreEqual(typeid(int64_t), e_i3.get_type());
         Assert::AreEqual(typeid(uint16_t), e_u1.get_type());
         Assert::AreEqual(typeid(uint32_t), e_u2.get_type());
         Assert::AreEqual(typeid(uint64_t), e_u3.get_type());
         Assert::AreEqual(typeid(float), e_r1.get_type());
         Assert::AreEqual(typeid(double), e_r2.get_type());
         Assert::AreEqual(typeid(array_t), e_a.get_type());
         Assert::AreEqual(typeid(dict_t), e_d.get_type());
         Assert::AreEqual(typeid(name_t), e_n.get_type());
         Assert::AreEqual(typeid(ref_t<object_t>), e_o.get_type());
         Assert::AreEqual(typeid(data_t), e_y.get_type());

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
         Assert::AreEqual<ref_t<object_t>>(o, e_o);
         Assert::AreEqual<any_t>(y, e_y);
      }

      TEST_METHOD(value_int64_operators)
      {
         value_t e;

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

      TEST_METHOD(value_double_operators)
      {
         value_t e;

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

      TEST_METHOD(value_bool_operator)
      {
         auto o = object_t::make();
         data_t y;

         value_t e_u;
         value_t e_t1(L"");
         value_t e_t2(text_t(L""));
         value_t e_c1('\0');
         value_t e_c2(L'\0');
         value_t e_b(false);
         value_t e_i2((int16_t)0);
         value_t e_i1((int32_t)0);
         value_t e_i3((int64_t)0);
         value_t e_u1((uint16_t)0);
         value_t e_u2((uint32_t)0);
         value_t e_u3((uint64_t)0);
         value_t e_r1(0.f);
         value_t e_r2(0.);
         value_t e_a(array_t::empty);
         value_t e_d(dict_t::empty);
         value_t e_n((voc::rock));
         value_t e_o(o);
         value_t e_y(y);

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

         e_u = value_t();
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

      TEST_METHOD(value_array)
      {
         array_t a;
         a.grow() = 55;
         a.grow() = 66.;
         a.grow() = 77.f;

         value_t e;

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

      TEST_METHOD(value_dict)
      {
         dict_t d;
         d[voc::rock] = 33.;
         d[voc::pebble] = 4;
         d[voc::sand] = 5.f;

         value_t e;

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
