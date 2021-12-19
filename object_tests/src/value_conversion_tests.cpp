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
   TEST_CLASS(value_conversion_tests)
	{
	public:
      value_conversion_tests()
      {
         register_data_ops();
         any_op::register_ops();
         register_object_ops();
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
