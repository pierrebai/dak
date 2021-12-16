#include <CppUnitTest.h>

#include <dak/object/name.h>
#include <dak/object/transaction.h>
#include <dak/object/timeline.h>
#include <dak/object/voc.h>
#include <dak/object/tests/helpers.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace dak::object;
using namespace std;

namespace dak::object::tests
{		
   TEST_CLASS(name_tests)
	{
	public:
      name_tests()
      {
         any_op::register_ops();
         register_object_ops();
      }

      TEST_METHOD(name_base)
		{
         name_t n;

         Assert::IsFalse(n.is_valid());

         Assert::AreEqual(n, name_t());
         Assert::AreNotEqual(n, (const name_t&)voc::rock);

         Assert::IsTrue(n == name_t());
         Assert::IsFalse(n != name_t());

         Assert::IsFalse(n <  name_t());
         Assert::IsTrue( n <= name_t());
         Assert::IsFalse(n >  name_t());
         Assert::IsTrue( n >= name_t());

         Assert::IsFalse(n == voc::rock);
         Assert::IsTrue( n != voc::rock);

         // Even the invalid name has a valid namespace.
         Assert::IsTrue(n.get_namespace().is_valid());

         // A valid metadat container ref is returned even for invalid name, but it is empty.
         Assert::AreEqual<size_t>(0, n.get_metadata().size());

         Assert::IsFalse(n.has_metadata(voc::acceleration));

         transaction_t trans;
         n.remove_metadata(name_t(), trans);
         Assert::IsFalse(n.has_metadata(voc::acceleration));
         Assert::IsFalse(n.has_metadata(name_t()));
      }

      TEST_METHOD(name_derived)
      {
         const name_t r = voc::rock;

         Assert::IsTrue(r.is_valid());

         Assert::AreNotEqual(r, name_t());
         Assert::AreEqual<name_t>(r, voc::rock);

         Assert::IsTrue( r == voc::rock);
         Assert::IsFalse(r != voc::rock);

         Assert::IsFalse(r < voc::rock);
         Assert::IsTrue( r <= voc::rock);
         Assert::IsFalse(r > voc::rock);
         Assert::IsTrue( r >= voc::rock);

         Assert::IsFalse(r == name_t());
         Assert::IsTrue(r != name_t());
      }


      TEST_METHOD(name_metadata)
      {
         auto ns = namespace_t::make(voc::get_namespace(), L"custom");
         name_t r = name_t(ns, voc::rock);

         Assert::IsTrue(r.is_valid());
         Assert::AreEqual<size_t>(0, r.get_metadata().size());

         Assert::IsFalse(r.has_metadata(name_t()));
         Assert::IsFalse(r.has_metadata(voc::acceleration));

         {
            transaction_t trans;

            r.add_metadata(voc::acceleration, trans);
            Assert::IsTrue(r.has_metadata(voc::acceleration));

            r.remove_metadata(name_t(), trans);
            Assert::IsTrue(r.has_metadata(voc::acceleration));

            r.remove_metadata(voc::acceleration, trans);
            Assert::IsFalse(r.has_metadata(voc::acceleration));

            trans.cancel();
         }

         timeline_t timeline;

         {
            transaction_t trans;

            r.add_metadata(voc::acceleration, trans);
            Assert::IsTrue(r.has_metadata(voc::acceleration));

            trans.commit(timeline);
         }

         Assert::IsTrue(r.has_metadata(voc::acceleration));

         timeline.undo();

         Assert::IsFalse(r.has_metadata(voc::acceleration));

         timeline.redo();

         Assert::IsTrue(r.has_metadata(voc::acceleration));
      }
   };
}
