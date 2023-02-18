#include <CppUnitTest.h>

#include <dak/object/value.h>
#include <dak/object/object.h>
#include <dak/object/voc.h>
#include <dak/object/tests/helpers.h>
#include <dak/object/tests/data.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace dak::any_op;

namespace dak::object::tests
{	
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

         Assert::AreEqual(typeid(void), e_u.get_type_info());
         Assert::AreEqual(typeid(text_t), e_t1.get_type_info());
         Assert::AreEqual(typeid(text_t), e_t2.get_type_info());
         Assert::AreEqual(typeid(char), e_c1.get_type_info());
         Assert::AreEqual(typeid(wchar_t), e_c2.get_type_info());
         Assert::AreEqual(typeid(bool), e_b.get_type_info());
         Assert::AreEqual(typeid(int16_t), e_i2.get_type_info());
         Assert::AreEqual(typeid(int32_t), e_i1.get_type_info());
         Assert::AreEqual(typeid(int64_t), e_i3.get_type_info());
         Assert::AreEqual(typeid(uint16_t), e_u1.get_type_info());
         Assert::AreEqual(typeid(uint32_t), e_u2.get_type_info());
         Assert::AreEqual(typeid(uint64_t), e_u3.get_type_info());
         Assert::AreEqual(typeid(float), e_r1.get_type_info());
         Assert::AreEqual(typeid(double), e_r2.get_type_info());
         Assert::AreEqual(typeid(array_t), e_a.get_type_info());
         Assert::AreEqual(typeid(dict_t), e_d.get_type_info());
         Assert::AreEqual(typeid(name_t), e_n.get_type_info());
         Assert::AreEqual(typeid(ref_t<object_t>), e_o.get_type_info());
         Assert::AreEqual(typeid(data_t), e_y.get_type_info());
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

         Assert::AreEqual(typeid(void), e_u.get_type_info());
         Assert::AreEqual(typeid(text_t), e_t1.get_type_info());
         Assert::AreEqual(typeid(text_t), e_t2.get_type_info());
         Assert::AreEqual(typeid(char), e_c1.get_type_info());
         Assert::AreEqual(typeid(wchar_t), e_c2.get_type_info());
         Assert::AreEqual(typeid(bool), e_b.get_type_info());
         Assert::AreEqual(typeid(int16_t), e_i2.get_type_info());
         Assert::AreEqual(typeid(int32_t), e_i1.get_type_info());
         Assert::AreEqual(typeid(int64_t), e_i3.get_type_info());
         Assert::AreEqual(typeid(uint16_t), e_u1.get_type_info());
         Assert::AreEqual(typeid(uint32_t), e_u2.get_type_info());
         Assert::AreEqual(typeid(uint64_t), e_u3.get_type_info());
         Assert::AreEqual(typeid(float), e_r1.get_type_info());
         Assert::AreEqual(typeid(double), e_r2.get_type_info());
         Assert::AreEqual(typeid(array_t), e_a.get_type_info());
         Assert::AreEqual(typeid(dict_t), e_d.get_type_info());
         Assert::AreEqual(typeid(name_t), e_n.get_type_info());
         Assert::AreEqual(typeid(ref_t<object_t>), e_o.get_type_info());
         Assert::AreEqual(typeid(data_t), e_y.get_type_info());
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

         Assert::AreEqual(typeid(void), e_u.get_type_info());
         Assert::AreEqual(typeid(void), e_t1.get_type_info());
         Assert::AreEqual(typeid(void), e_t2.get_type_info());
         Assert::AreEqual(typeid(void), e_c1.get_type_info());
         Assert::AreEqual(typeid(void), e_c2.get_type_info());
         Assert::AreEqual(typeid(void), e_b.get_type_info());
         Assert::AreEqual(typeid(void), e_i2.get_type_info());
         Assert::AreEqual(typeid(void), e_i1.get_type_info());
         Assert::AreEqual(typeid(void), e_i3.get_type_info());
         Assert::AreEqual(typeid(void), e_u1.get_type_info());
         Assert::AreEqual(typeid(void), e_u2.get_type_info());
         Assert::AreEqual(typeid(void), e_u3.get_type_info());
         Assert::AreEqual(typeid(void), e_r1.get_type_info());
         Assert::AreEqual(typeid(void), e_r2.get_type_info());
         Assert::AreEqual(typeid(void), e_a.get_type_info());
         Assert::AreEqual(typeid(void), e_d.get_type_info());
         Assert::AreEqual(typeid(void), e_n.get_type_info());
         Assert::AreEqual(typeid(void), e_o.get_type_info());
         Assert::AreEqual(typeid(void), e_y.get_type_info());

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

         Assert::AreEqual(typeid(void), e_u.get_type_info());
         Assert::AreEqual(typeid(void), e_t1.get_type_info());
         Assert::AreEqual(typeid(void), e_t2.get_type_info());
         Assert::AreEqual(typeid(void), e_c1.get_type_info());
         Assert::AreEqual(typeid(void), e_c2.get_type_info());
         Assert::AreEqual(typeid(void), e_b.get_type_info());
         Assert::AreEqual(typeid(void), e_i2.get_type_info());
         Assert::AreEqual(typeid(void), e_i1.get_type_info());
         Assert::AreEqual(typeid(void), e_i3.get_type_info());
         Assert::AreEqual(typeid(void), e_u1.get_type_info());
         Assert::AreEqual(typeid(void), e_u2.get_type_info());
         Assert::AreEqual(typeid(void), e_u3.get_type_info());
         Assert::AreEqual(typeid(void), e_r1.get_type_info());
         Assert::AreEqual(typeid(void), e_r2.get_type_info());
         Assert::AreEqual(typeid(void), e_a.get_type_info());
         Assert::AreEqual(typeid(void), e_d.get_type_info());
         Assert::AreEqual(typeid(void), e_n.get_type_info());
         Assert::AreEqual(typeid(void), e_o.get_type_info());
         Assert::AreEqual(typeid(void), e_y.get_type_info());

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

         Assert::AreEqual(typeid(void), e_u.get_type_info());
         Assert::AreEqual(typeid(text_t), e_t1.get_type_info());
         Assert::AreEqual(typeid(text_t), e_t2.get_type_info());
         Assert::AreEqual(typeid(char), e_c1.get_type_info());
         Assert::AreEqual(typeid(wchar_t), e_c2.get_type_info());
         Assert::AreEqual(typeid(bool), e_b.get_type_info());
         Assert::AreEqual(typeid(int16_t), e_i2.get_type_info());
         Assert::AreEqual(typeid(int32_t), e_i1.get_type_info());
         Assert::AreEqual(typeid(int64_t), e_i3.get_type_info());
         Assert::AreEqual(typeid(uint16_t), e_u1.get_type_info());
         Assert::AreEqual(typeid(uint32_t), e_u2.get_type_info());
         Assert::AreEqual(typeid(uint64_t), e_u3.get_type_info());
         Assert::AreEqual(typeid(float), e_r1.get_type_info());
         Assert::AreEqual(typeid(double), e_r2.get_type_info());
         Assert::AreEqual(typeid(array_t), e_a.get_type_info());
         Assert::AreEqual(typeid(dict_t), e_d.get_type_info());
         Assert::AreEqual(typeid(name_t), e_n.get_type_info());
         Assert::AreEqual(typeid(ref_t<object_t>), e_o.get_type_info());
         Assert::AreEqual(typeid(data_t), e_y.get_type_info());
      }
   };
}
