#include <CppUnitTest.h>

#include <dak/any_op/all.h>
#include <dak/any_op/tests/helpers.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace dak::any_op;

namespace dak::any_op::tests
{		
   TEST_CLASS(construct_op_tests)
	{
	public:
		TEST_METHOD(make_test)
		{
         construct_op_t::register_ops();

         Assert::AreEqual(any_t(L""         ), construct(typeid(text_t   )));
         Assert::AreEqual(any_t(char     (0)), construct(typeid(char     )));
         Assert::AreEqual(any_t(wchar_t  (0)), construct(typeid(wchar_t  )));
         Assert::AreEqual(any_t(bool     (0)), construct(typeid(bool     )));
         Assert::AreEqual(any_t(int16_t  (0)), construct(typeid(int16_t  )));
         Assert::AreEqual(any_t(int32_t  (0)), construct(typeid(int32_t  )));
         Assert::AreEqual(any_t(int64_t  (0)), construct(typeid(int64_t  )));
         Assert::AreEqual(any_t(uint16_t (0)), construct(typeid(uint16_t )));
         Assert::AreEqual(any_t(uint32_t (0)), construct(typeid(uint32_t )));
         Assert::AreEqual(any_t(uint64_t (0)), construct(typeid(uint64_t )));
         Assert::AreEqual(any_t(float    (0)), construct(typeid(float    )));
         Assert::AreEqual(any_t(double   (0)), construct(typeid(double   )));
      }
   };
}
