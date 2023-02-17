#include <CppUnitTest.h>

#include <dak/any_op/all.h>
#include <dak/any_op/tests/helpers.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace dak::any_op;

namespace dak::any_op::tests
{
   namespace
   {
      struct a_t {};
      struct b_t : a_t {};
      struct c_t {};
      struct d_t : b_t, c_t {};
   }

   TEST_CLASS(supers_of_op_tests)
	{
	public:
		TEST_METHOD(supers_of_test)
		{
         register_ops();

         supers_of_op_t::make<a_t>::op<supers_t>(make_supers_of([]() -> supers_t { return {                            }; }));
         supers_of_op_t::make<b_t>::op<supers_t>(make_supers_of([]() -> supers_t { return { &typeid(a_t)               }; }));
         supers_of_op_t::make<d_t>::op<supers_t>(make_supers_of([]() -> supers_t { return { &typeid(b_t), &typeid(c_t) }; }));

         Assert::AreEqual(supers_t(), supers_of<bool>());
         Assert::AreEqual(supers_t(), supers_of<uint64_t>());
         Assert::AreEqual(supers_t(), supers_of<a_t>());
         Assert::AreEqual(supers_t(), supers_of<c_t>());
         Assert::AreEqual(supers_t({ &typeid(a_t) }), supers_of<b_t>());
         Assert::AreEqual(supers_t({ &typeid(b_t), &typeid(c_t) }), supers_of<d_t>());
         Assert::AreEqual(supers_t({ &typeid(a_t) }), supers_of(*supers_of<d_t>()[0]));
      }
   };
}
