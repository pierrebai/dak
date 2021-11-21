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

   };
}
