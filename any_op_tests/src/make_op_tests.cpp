#include <CppUnitTest.h>

#include <dak/any_op/all.h>
#include <dak/any_op/tests/helpers.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace dak::any_op;

namespace dak::any_op::tests
{		
   TEST_CLASS(make_op_tests)
	{
	public:
		TEST_METHOD(make_test)
		{
         make_op_t::register_ops();

         Assert::AreEqual<text_t   >(L"", make<text_t   >());
         Assert::AreEqual<char     >(0, make<char     >());
         Assert::AreEqual<wchar_t  >(0, make<wchar_t  >());
         Assert::AreEqual<bool     >(0, make<bool     >());
         Assert::AreEqual<int16_t  >(0, make<int16_t  >());
         Assert::AreEqual<int32_t  >(0, make<int32_t  >());
         Assert::AreEqual<int64_t  >(0, make<int64_t  >());
         Assert::AreEqual<uint16_t >(0, make<uint16_t >());
         Assert::AreEqual<uint32_t >(0, make<uint32_t >());
         Assert::AreEqual<uint64_t >(0, make<uint64_t >());
         Assert::AreEqual<float    >(0, make<float    >());
         Assert::AreEqual<double   >(0, make<double   >());
      }
   };
}
