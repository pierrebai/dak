#include <CppUnitTest.h>

#include <dak/object/make_op.h>
#include "dak/object/tests/helpers.h"

#include <dak/any_op/all.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace dak::any_op;
using namespace dak::object;

namespace dak::object::tests
{		
   TEST_CLASS(construct_op_tests)
	{
	public:
		TEST_METHOD(make_test)
		{
         construct_op_t::register_ops();
         register_object_ops();

         Assert::AreEqual(any_t(array_t()             ), construct(typeid(array_t             )));
         Assert::AreEqual(any_t(dict_t()              ), construct(typeid(dict_t              )));
         Assert::AreEqual(any_t(name_t()              ), construct(typeid(name_t              )));
         Assert::AreEqual(any_t(value_t()             ), construct(typeid(value_t             )));
         Assert::AreEqual(any_t(ref_t<object_t>()     ), construct(typeid(ref_t<object_t>     )));
         Assert::AreEqual(any_t(weak_ref_t<object_t>()), construct(typeid(weak_ref_t<object_t>)));

         ref_t<object_t   > ro = as<ref_t<object_t   >>(make(typeid(object_t   )));
         ref_t<namespace_t> rn = as<ref_t<namespace_t>>(make(typeid(namespace_t)));

         Assert::IsTrue(ro.is_valid());
         Assert::IsTrue(rn.is_valid());

         Assert::AreEqual(object_t()   , *valid_ref_t(ro));
         Assert::AreEqual(namespace_t(), *valid_ref_t(rn));
      }
   };
}
