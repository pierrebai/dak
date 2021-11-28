#include <CppUnitTest.h>

#include <dak/any_op/all.h>
#include <dak/any_op/tests/helpers.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace dak::any_op;

namespace dak::any_op::tests
{		
   TEST_CLASS(size_op_tests)
	{
	public:
		TEST_METHOD(size_test)
		{
         size_op_t::register_ops();

         any_t e_t1(text_t(L"text_t"));
         any_t e_t2(L"strptr");
         any_t e_c1('c');
         any_t e_c2(L'w');
         any_t e_b (true);
         any_t e_i2((int16_t)2);
         any_t e_i1((int32_t)1);
         any_t e_i3((int64_t)3);
         any_t e_u1((uint16_t)4u);
         any_t e_u2((uint32_t)5u);
         any_t e_u3((uint64_t)6u);
         any_t e_r1(7.0f);
         any_t e_r2(8.0);

         Assert::AreEqual<uint64_t>(6, size(e_t1));
         Assert::AreEqual<uint64_t>(6, size(e_t2));
         Assert::AreEqual<uint64_t>(0, size(e_c1));
         Assert::AreEqual<uint64_t>(0, size(e_c2));
         Assert::AreEqual<uint64_t>(0, size(e_b ));
         Assert::AreEqual<uint64_t>(0, size(e_i2));
         Assert::AreEqual<uint64_t>(0, size(e_i1));
         Assert::AreEqual<uint64_t>(0, size(e_i3));
         Assert::AreEqual<uint64_t>(0, size(e_u1));
         Assert::AreEqual<uint64_t>(0, size(e_u2));
         Assert::AreEqual<uint64_t>(0, size(e_u3));
         Assert::AreEqual<uint64_t>(0, size(e_r1));
         Assert::AreEqual<uint64_t>(0, size(e_r2));
      }
   };
}
