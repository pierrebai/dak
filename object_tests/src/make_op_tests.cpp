#include <CppUnitTest.h>

#include <dak/object/make_object_op.h>
#include <dak/any_op/make_op.h>
#include "dak/object/tests/helpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace dak::any_op;
using namespace dak::object;

namespace dak::object::tests
{		
   TEST_CLASS(make_op_tests)
	{
	public:
		TEST_METHOD(make_test)
		{
         make_op_t::register_ops();
         register_object_ops();

         Assert::AreEqual<array_t             >(array_t()             , make<array_t             >());
         Assert::AreEqual<dict_t              >(dict_t()              , make<dict_t              >());
         Assert::AreEqual<name_t              >(name_t()              , make<name_t              >());
         Assert::AreEqual<value_t             >(value_t()             , make<value_t             >());
         Assert::AreEqual<ref_t<object_t>     >(ref_t<object_t>()     , make<ref_t<object_t>     >());
         Assert::AreEqual<weak_ref_t<object_t>>(weak_ref_t<object_t>(), make<weak_ref_t<object_t>>());

         ref_t<object_t   > ro = make_object<object_t   >();
         ref_t<namespace_t> rn = make_object<namespace_t>();

         Assert::IsTrue(ro.is_valid());
         Assert::IsTrue(rn.is_valid());

         Assert::AreEqual(object_t()   , *valid_ref_t(ro));
         Assert::AreEqual(namespace_t(), *valid_ref_t(rn));
      }
   };
}
