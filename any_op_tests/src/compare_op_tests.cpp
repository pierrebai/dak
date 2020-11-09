#include <CppUnitTest.h>

#include <dak/any_op/all.h>
#include <dak/any_op/tests/helpers.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace dak::any_op;

namespace dak::any_op::tests
{		
   TEST_CLASS(compare_op_tests)
	{
	public:
		TEST_METHOD(element_base)
		{
         std::any e;

         Assert::AreEqual(e, std::any());
         Assert::AreEqual(e, std::any());
         Assert::AreNotEqual(e, std::any(1));

         Assert::IsTrue( e == std::any());
         Assert::IsTrue(e == std::any());
         Assert::IsFalse(e != std::any());

         Assert::IsFalse(e == std::any(1));
         Assert::IsFalse(std::any() == std::any(1));
         Assert::IsTrue(e != std::any(1));
      }

      TEST_METHOD(element_constructors)
      {
         std::any e_u;
         std::any e_t1(text_t(L"text_t"));
         std::any e_t2(L"strptr");
         std::any e_c1('c');
         std::any e_c2(L'w');
         std::any e_b(true);
         std::any e_i2((int16_t)2);
         std::any e_i1((int32_t)1);
         std::any e_i3((int64_t)3);
         std::any e_u1((uint16_t)4u);
         std::any e_u2((uint32_t)5u);
         std::any e_u3((uint64_t)6u);
         std::any e_r1(7.0f);
         std::any e_r2(8.0);

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

      TEST_METHOD(element_assignments)
      {
         std::any e_u;
         std::any e_t1;
         std::any e_t2;
         std::any e_c1;
         std::any e_c2;
         std::any e_b;
         std::any e_i2;
         std::any e_i1;
         std::any e_i3;
         std::any e_u1;
         std::any e_u2;
         std::any e_u3;
         std::any e_r1;
         std::any e_r2;

         e_u  = std::any();
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

      TEST_METHOD(var_text_assignments)
      {
         std::any e1;

         e1 = L"hello";
         Assert::AreEqual<std::any>(std::any(L"hello"), e1);

         e1 = (str_ptr_t)nullptr;
         Assert::AreEqual<std::any>(text_t(L""), e1);

         e1 = L"bye";
         Assert::AreEqual<std::any>(text_t(L"bye"), e1);
      }

      TEST_METHOD(element_conversion)
      {
         std::any e_u;
         std::any e_t1(text_t(L"text_t"));
         std::any e_t2(L"strptr");
         std::any e_c1('c');
         std::any e_c2(L'w');
         std::any e_b(true);
         std::any e_i2((int16_t)2);
         std::any e_i1((int32_t)1);
         std::any e_i3((int64_t)3);
         std::any e_u1((uint16_t)4u);
         std::any e_u2((uint32_t)5u);
         std::any e_u3((uint64_t)6u);
         std::any e_r1(7.0f);
         std::any e_r2(8.0);

         Assert::AreEqual<std::any>(std::any(), e_u);
         Assert::AreEqual<std::any>(text_t(L"text_t"), e_t1);
         Assert::AreEqual<std::any>(L"strptr", e_t2);
         Assert::AreEqual<std::any>('c', e_c1);
         Assert::AreEqual<std::any>(L'w', e_c2);
         Assert::AreEqual<std::any>(true, e_b);
         Assert::AreEqual<std::any>((int16_t)2, e_i2);
         Assert::AreEqual<std::any>((int32_t)1, e_i1);
         Assert::AreEqual<std::any>((int64_t)3, e_i3);
         Assert::AreEqual<std::any>((uint16_t)4u, e_u1);
         Assert::AreEqual<std::any>((uint32_t)5u, e_u2);
         Assert::AreEqual<std::any>((uint64_t)6u, e_u3);
         Assert::AreEqual<std::any>(7.0f, e_r1);
         Assert::AreEqual<std::any>(8.0, e_r2);
      }

      TEST_METHOD(element_const_conversion)
      {
         const std::any e_u;
         const std::any e_t1(text_t(L"text_t"));
         const std::any e_t2(L"strptr");
         const std::any e_c1('c');
         const std::any e_c2(L'w');
         const std::any e_b(true);
         const std::any e_i2((int16_t)2);
         const std::any e_i1((int32_t)1);
         const std::any e_i3((int64_t)3);
         const std::any e_u1((uint16_t)4u);
         const std::any e_u2((uint32_t)5u);
         const std::any e_u3((uint64_t)6u);
         const std::any e_r1(7.0f);
         const std::any e_r2(8.0);

         Assert::AreEqual<std::any>(std::any(), e_u);
         Assert::AreEqual<std::any>(text_t(L"text_t"), e_t1);
         Assert::AreEqual<std::any>(L"strptr", e_t2);
         Assert::AreEqual<std::any>('c', e_c1);
         Assert::AreEqual<std::any>(L'w', e_c2);
         Assert::AreEqual<std::any>(true, e_b);
         Assert::AreEqual<std::any>((int16_t)2, e_i2);
         Assert::AreEqual<std::any>((int32_t)1, e_i1);
         Assert::AreEqual<std::any>((int64_t)3, e_i3);
         Assert::AreEqual<std::any>((uint16_t)4u, e_u1);
         Assert::AreEqual<std::any>((uint32_t)5u, e_u2);
         Assert::AreEqual<std::any>((uint64_t)6u, e_u3);
         Assert::AreEqual<std::any>(7.0f, e_r1);
         Assert::AreEqual<std::any>(8.0, e_r2);
      }

      TEST_METHOD(element_unknown_assignments)
      {
         std::any e_u;
         std::any e_t1(text_t(L"text_t"));
         std::any e_t2(L"strptr");
         std::any e_c1('c');
         std::any e_c2(L'w');
         std::any e_b(true);
         std::any e_i2((int16_t)2);
         std::any e_i1((int32_t)1);
         std::any e_i3((int64_t)3);
         std::any e_u1((uint16_t)4u);
         std::any e_u2((uint32_t)5u);
         std::any e_u3((uint64_t)6u);
         std::any e_r1(7.0f);
         std::any e_r2(8.0);

         // Assigning an empty std::any of type void
         // should set the type to void and reset the value.
         e_u = std::any();
         e_t1 = std::any();
         e_t2 = std::any();
         e_c1 = std::any();
         e_c2 = std::any();
         e_b = std::any();
         e_i2 = std::any();
         e_i1 = std::any();
         e_i3 = std::any();
         e_u1 = std::any();
         e_u2 = std::any();
         e_u3 = std::any();
         e_r1 = std::any();
         e_r2 = std::any();

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

      TEST_METHOD(element_reset)
      {
         std::any e_u;
         std::any e_t1(text_t(L"text_t"));
         std::any e_t2(L"strptr");
         std::any e_c1('c');
         std::any e_c2(L'w');
         std::any e_b(true);
         std::any e_i2((int16_t)2);
         std::any e_i1((int32_t)1);
         std::any e_i3((int64_t)3);
         std::any e_u1((uint16_t)4u);
         std::any e_u2((uint32_t)5u);
         std::any e_u3((uint64_t)6u);
         std::any e_r1(7.0f);
         std::any e_r2(8.0);

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
