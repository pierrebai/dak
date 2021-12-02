#include "CppUnitTest.h"

#include "dak/object/name.h"
#include "dak/object/transaction.h"
#include "dak/object/timeline.h"
#include "dak/object/voc.h"
#include "dak/object/tests/helpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace dak::object;
using namespace dak::object::voc;
using namespace std;

namespace dak::object::tests
{		
   TEST_CLASS(name_tests)
	{
	public:
		TEST_METHOD(name_base)
		{
         name_t n;

         Assert::IsFalse(n.is_valid());

         Assert::AreEqual(n, name_t());
         Assert::AreNotEqual(n, (const name_t&)rock);

         Assert::IsTrue(n == name_t());
         Assert::IsFalse(n != name_t());

         Assert::IsFalse(n <  name_t());
         Assert::IsTrue( n <= name_t());
         Assert::IsFalse(n >  name_t());
         Assert::IsTrue( n >= name_t());

         Assert::IsFalse(n == rock);
         Assert::IsTrue( n != rock);

         // A valid namespace ref is returned even for invalid name, but it is empty.
         Assert::IsTrue(n.get_namespace().is_valid());
         Assert::AreEqual<size_t>(0, n.get_namespace()->get_names().size());

         // A valid metadat container ref is returned even for invalid name, but it is empty.
         Assert::AreEqual<size_t>(0, n.get_metadata().size());

         Assert::IsFalse(r.has_metadata(voc::acceleration));

         transaction_t trans;
         n.remove_metadata(name_t(), trans);
         Assert::IsFalse(r.has_metadata(voc::acceleration));
         Assert::IsFalse(r.has_metadata(name_t()));
      }

      TEST_METHOD(name_derived)
      {
         const name_t r = rock;

         Assert::IsTrue(r.is_valid());

         Assert::AreNotEqual(r, name_t());
         Assert::AreEqual<name_t>(r, rock);

         Assert::IsTrue( r == rock);
         Assert::IsFalse(r != rock);

         Assert::IsFalse(r < rock);
         Assert::IsTrue( r <= rock);
         Assert::IsFalse(r > rock);
         Assert::IsTrue( r >= rock);

         Assert::IsFalse(r == name_t());
         Assert::IsTrue(r != name_t());
      }


      TEST_METHOD(name_metadata)
      {
         name_t r = rock;

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
