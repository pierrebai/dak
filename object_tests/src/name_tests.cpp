#include "CppUnitTest.h"

#include "dak/object/name.h"
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

         // Root is valid.
         Assert::IsTrue(n.is_valid());

         // Note: two roots are not equal.
         Assert::AreNotEqual(n, name_t());
         Assert::AreNotEqual(n, (const name_t&)rock);

         // Note: two roots are not equal.
         Assert::IsFalse(n == name_t());
         Assert::IsTrue( n != name_t());

         // We cannot predict the address the sub-names will be.
         //Assert::IsFalse(n <  name_t());
         //Assert::IsTrue( n <= name_t());
         //Assert::IsFalse(n >  name_t());
         //Assert::IsTrue( n >= name_t());

         Assert::IsFalse(n == rock);
         Assert::IsTrue( n != rock);
      }

      TEST_METHOD(name_derived)
      {
         rock_n r;

         Assert::IsTrue(r.is_valid());

         Assert::AreNotEqual((const name_t&)r, name_t());
         Assert::AreEqual<name_t>(r, rock);

         Assert::IsTrue( r == rock);
         Assert::IsFalse(r != rock);

         // We cannot predict the address the sub-names will be.
         //Assert::IsFalse(r < rock);
         //Assert::IsTrue( r <= rock);
         //Assert::IsFalse(r > rock);
         //Assert::IsTrue( r >= rock);

         Assert::IsFalse(r == name_t());
         Assert::IsTrue(r != name_t());
      }

   };
}
