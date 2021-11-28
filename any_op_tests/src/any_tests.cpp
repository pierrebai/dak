#include <CppUnitTest.h>

#include <dak/any_op/all.h>
#include <dak/any_op/tests/helpers.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace dak::any_op;

namespace dak::any_op::tests
{		
   TEST_CLASS(any_tests)
	{
	public:
		TEST_METHOD(any_default)
		{
         any_t e;

         Assert::AreEqual(e, any_t());
         Assert::AreEqual(e, any_t());
         Assert::AreNotEqual(e, any_t(1));

         Assert::IsTrue( e == any_t());
         Assert::IsTrue(e == any_t());
         Assert::IsFalse(e != any_t());

         Assert::IsFalse(e == any_t(1));
         Assert::IsFalse(any_t() == any_t(1));
         Assert::IsTrue(e != any_t(1));
      }

      TEST_METHOD(any_constructors)
      {
         any_t e_u;
         any_t e_t1(text_t(L"text_t"));
         any_t e_t2(L"strptr");
         any_t e_c1('c');
         any_t e_c2(L'w');
         any_t e_b(true);
         any_t e_i2((int16_t)2);
         any_t e_i1((int32_t)1);
         any_t e_i3((int64_t)3);
         any_t e_u1((uint16_t)4u);
         any_t e_u2((uint32_t)5u);
         any_t e_u3((uint64_t)6u);
         any_t e_r1(7.0f);
         any_t e_r2(8.0);

         Assert::AreEqual(typeid(void), e_u.type());
         Assert::AreEqual(typeid(text_t), e_t1.type());
         Assert::AreEqual(typeid(str_ptr_t), e_t2.type());
         Assert::AreEqual(typeid(char), e_c1.type());
         Assert::AreEqual(typeid(wchar_t), e_c2.type());
         Assert::AreEqual(typeid(bool), e_b.type());
         Assert::AreEqual(typeid(int16_t), e_i2.type());
         Assert::AreEqual(typeid(int32_t), e_i1.type());
         Assert::AreEqual(typeid(int64_t), e_i3.type());
         Assert::AreEqual(typeid(uint16_t), e_u1.type());
         Assert::AreEqual(typeid(uint32_t), e_u2.type());
         Assert::AreEqual(typeid(uint64_t), e_u3.type());
         Assert::AreEqual(typeid(float), e_r1.type());
         Assert::AreEqual(typeid(double), e_r2.type());
      }

      TEST_METHOD(any_assignments)
      {
         any_t e_u;
         any_t e_t1;
         any_t e_t2;
         any_t e_c1;
         any_t e_c2;
         any_t e_b;
         any_t e_i2;
         any_t e_i1;
         any_t e_i3;
         any_t e_u1;
         any_t e_u2;
         any_t e_u3;
         any_t e_r1;
         any_t e_r2;

         e_u  = any_t();
         e_t1 = text_t(L"text_t");
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

         Assert::AreEqual(typeid(void), e_u.type());
         Assert::AreEqual(typeid(text_t), e_t1.type());
         Assert::AreEqual(typeid(str_ptr_t), e_t2.type());
         Assert::AreEqual(typeid(char), e_c1.type());
         Assert::AreEqual(typeid(wchar_t), e_c2.type());
         Assert::AreEqual(typeid(bool), e_b.type());
         Assert::AreEqual(typeid(int16_t), e_i2.type());
         Assert::AreEqual(typeid(int32_t), e_i1.type());
         Assert::AreEqual(typeid(int64_t), e_i3.type());
         Assert::AreEqual(typeid(uint16_t), e_u1.type());
         Assert::AreEqual(typeid(uint32_t), e_u2.type());
         Assert::AreEqual(typeid(uint64_t), e_u3.type());
         Assert::AreEqual(typeid(float), e_r1.type());
         Assert::AreEqual(typeid(double), e_r2.type());
      }

      TEST_METHOD(any_text_assignments)
      {
         any_t e1;

         e1 = L"hello";
         Assert::AreEqual<any_t>(any_t(L"hello"), e1);

         e1 = (str_ptr_t)nullptr;
         Assert::AreEqual<any_t>(text_t(L""), e1);

         e1 = L"bye";
         Assert::AreEqual<any_t>(text_t(L"bye"), e1);
      }

      TEST_METHOD(any_conversion)
      {
         any_t e_u;
         any_t e_t1(text_t(L"text_t"));
         any_t e_t2(L"strptr");
         any_t e_c1('c');
         any_t e_c2(L'w');
         any_t e_b(true);
         any_t e_i2((int16_t)2);
         any_t e_i1((int32_t)1);
         any_t e_i3((int64_t)3);
         any_t e_u1((uint16_t)4u);
         any_t e_u2((uint32_t)5u);
         any_t e_u3((uint64_t)6u);
         any_t e_r1(7.0f);
         any_t e_r2(8.0);

         Assert::AreEqual<any_t>(any_t(), e_u);
         Assert::AreEqual<any_t>(text_t(L"text_t"), e_t1);
         Assert::AreEqual<any_t>(L"strptr", e_t2);
         Assert::AreEqual<any_t>('c', e_c1);
         Assert::AreEqual<any_t>(L'w', e_c2);
         Assert::AreEqual<any_t>(true, e_b);
         Assert::AreEqual<any_t>((int16_t)2, e_i2);
         Assert::AreEqual<any_t>((int32_t)1, e_i1);
         Assert::AreEqual<any_t>((int64_t)3, e_i3);
         Assert::AreEqual<any_t>((uint16_t)4u, e_u1);
         Assert::AreEqual<any_t>((uint32_t)5u, e_u2);
         Assert::AreEqual<any_t>((uint64_t)6u, e_u3);
         Assert::AreEqual<any_t>(7.0f, e_r1);
         Assert::AreEqual<any_t>(8.0, e_r2);
      }

      TEST_METHOD(any_const_conversion)
      {
         const any_t e_u;
         const any_t e_t1(text_t(L"text_t"));
         const any_t e_t2(L"strptr");
         const any_t e_c1('c');
         const any_t e_c2(L'w');
         const any_t e_b(true);
         const any_t e_i2((int16_t)2);
         const any_t e_i1((int32_t)1);
         const any_t e_i3((int64_t)3);
         const any_t e_u1((uint16_t)4u);
         const any_t e_u2((uint32_t)5u);
         const any_t e_u3((uint64_t)6u);
         const any_t e_r1(7.0f);
         const any_t e_r2(8.0);

         Assert::AreEqual<any_t>(any_t(), e_u);
         Assert::AreEqual<any_t>(text_t(L"text_t"), e_t1);
         Assert::AreEqual<any_t>(L"strptr", e_t2);
         Assert::AreEqual<any_t>('c', e_c1);
         Assert::AreEqual<any_t>(L'w', e_c2);
         Assert::AreEqual<any_t>(true, e_b);
         Assert::AreEqual<any_t>((int16_t)2, e_i2);
         Assert::AreEqual<any_t>((int32_t)1, e_i1);
         Assert::AreEqual<any_t>((int64_t)3, e_i3);
         Assert::AreEqual<any_t>((uint16_t)4u, e_u1);
         Assert::AreEqual<any_t>((uint32_t)5u, e_u2);
         Assert::AreEqual<any_t>((uint64_t)6u, e_u3);
         Assert::AreEqual<any_t>(7.0f, e_r1);
         Assert::AreEqual<any_t>(8.0, e_r2);
      }

      TEST_METHOD(any_unknown_assignments)
      {
         any_t e_u;
         any_t e_t1(text_t(L"text_t"));
         any_t e_t2(L"strptr");
         any_t e_c1('c');
         any_t e_c2(L'w');
         any_t e_b(true);
         any_t e_i2((int16_t)2);
         any_t e_i1((int32_t)1);
         any_t e_i3((int64_t)3);
         any_t e_u1((uint16_t)4u);
         any_t e_u2((uint32_t)5u);
         any_t e_u3((uint64_t)6u);
         any_t e_r1(7.0f);
         any_t e_r2(8.0);

         // Assigning an empty any_t of type void
         // should set the type to void and reset the value.
         e_u = any_t();
         e_t1 = any_t();
         e_t2 = any_t();
         e_c1 = any_t();
         e_c2 = any_t();
         e_b = any_t();
         e_i2 = any_t();
         e_i1 = any_t();
         e_i3 = any_t();
         e_u1 = any_t();
         e_u2 = any_t();
         e_u3 = any_t();
         e_r1 = any_t();
         e_r2 = any_t();

         Assert::AreEqual(typeid(void), e_u.type());
         Assert::AreEqual(typeid(void), e_t1.type());
         Assert::AreEqual(typeid(void), e_t2.type());
         Assert::AreEqual(typeid(void), e_c1.type());
         Assert::AreEqual(typeid(void), e_c2.type());
         Assert::AreEqual(typeid(void), e_b.type());
         Assert::AreEqual(typeid(void), e_i2.type());
         Assert::AreEqual(typeid(void), e_i1.type());
         Assert::AreEqual(typeid(void), e_i3.type());
         Assert::AreEqual(typeid(void), e_u1.type());
         Assert::AreEqual(typeid(void), e_u2.type());
         Assert::AreEqual(typeid(void), e_u3.type());
         Assert::AreEqual(typeid(void), e_r1.type());
         Assert::AreEqual(typeid(void), e_r2.type());
      }

      TEST_METHOD(any_reset)
      {
         any_t e_u;
         any_t e_t1(text_t(L"text_t"));
         any_t e_t2(L"strptr");
         any_t e_c1('c');
         any_t e_c2(L'w');
         any_t e_b(true);
         any_t e_i2((int16_t)2);
         any_t e_i1((int32_t)1);
         any_t e_i3((int64_t)3);
         any_t e_u1((uint16_t)4u);
         any_t e_u2((uint32_t)5u);
         any_t e_u3((uint64_t)6u);
         any_t e_r1(7.0f);
         any_t e_r2(8.0);

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

         Assert::AreEqual(typeid(void), e_u.type());
         Assert::AreEqual(typeid(void), e_t1.type());
         Assert::AreEqual(typeid(void), e_t2.type());
         Assert::AreEqual(typeid(void), e_c1.type());
         Assert::AreEqual(typeid(void), e_c2.type());
         Assert::AreEqual(typeid(void), e_b.type());
         Assert::AreEqual(typeid(void), e_i2.type());
         Assert::AreEqual(typeid(void), e_i1.type());
         Assert::AreEqual(typeid(void), e_i3.type());
         Assert::AreEqual(typeid(void), e_u1.type());
         Assert::AreEqual(typeid(void), e_u2.type());
         Assert::AreEqual(typeid(void), e_u3.type());
         Assert::AreEqual(typeid(void), e_r1.type());
         Assert::AreEqual(typeid(void), e_r2.type());
      }

   };
}
