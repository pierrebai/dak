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
   TEST_CLASS(value_ensure_tests)
	{
	public:
      value_ensure_tests()
      {
         register_data_ops();
         any_op::register_ops();
         register_object_ops();
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
   };
}
