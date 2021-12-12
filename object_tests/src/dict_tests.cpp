#include "CppUnitTest.h"

#include "dak/object/dict.h"
#include "dak/object/voc.h"
#include "dak/object/tests/helpers.h"

#include "dak/any_op/size_op.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace dak::object::voc;

namespace dak::object::tests
{
   TEST_CLASS(dict_tests)
	{
	public:

      dict_tests()
      {
         any_op::register_ops();
         register_object_ops();
      }

		TEST_METHOD(dict_base)
		{
         dict_t d1;

         Assert::AreEqual<index_t>(0, d1.size());

         d1[voc::rock] = 3;
         d1[voc::pebble] = 4;
         d1[voc::sand] = 5.0;
         d1[voc::hello] = L"6";
         d1[voc::world] = voc::rock;

         Assert::AreEqual<index_t>(5, d1.size());

         Assert::AreEqual<int32_t>(3, d1[rock]);
         Assert::AreEqual<int64_t>(4, d1[pebble]);
         Assert::AreEqual<double>(5.0, d1[sand]);
         Assert::AreEqual<text_t>(L"6", d1[hello]);
         Assert::AreEqual<name_t>(rock, d1[world]);

         Assert::IsTrue(d1.erase(rock));
         Assert::IsTrue(d1.erase(pebble));
         Assert::IsTrue(d1.erase(world));
         Assert::IsTrue(d1.erase(hello));
         Assert::IsTrue(d1.erase(sand));
         Assert::IsFalse(d1.erase(rock));

         Assert::AreEqual<index_t>(0, d1.size());
      }

      TEST_METHOD(dict_const)
      {
         dict_t d1;

         Assert::AreEqual<index_t>(0, d1.size());

         d1[voc::rock] = 3;
         d1[voc::pebble] = 4;
         d1[voc::sand] = 5.0;
         d1[voc::hello] = L"6";
         d1[voc::world] = voc::rock;

         const dict_t& const_d1 = d1;

         Assert::AreEqual<index_t>(5, d1.size());

         Assert::AreEqual<int32_t>(3, const_d1[rock]);
         Assert::AreEqual<int64_t>(4, const_d1[pebble]);
         Assert::AreEqual<double>(5.0, const_d1[sand]);
         Assert::AreEqual<text_t>(L"6", const_d1[hello]);
         Assert::AreEqual<name_t>(rock, const_d1[world]);
         Assert::AreEqual<const datatype_t&>(typeid(void), const_d1[absent].get_type());
      }

      TEST_METHOD(dict_append)
      {
         dict_t d1;

         d1[rock] = 3;
         d1[pebble] = 4;
         d1[sand] = 5.0;
         d1[hello][world] = rock;

         dict_t d2;

         d2 += d1;

         Assert::AreEqual<index_t>(4, d1.size());
         Assert::AreEqual<index_t>(4, d2.size());

         Assert::AreEqual<int32_t>(3, d2[rock]);
         Assert::AreEqual<int64_t>(4, d2[pebble]);
         Assert::AreEqual<double>(5.0, d2[sand]);
         Assert::AreEqual<name_t>(rock, d2[hello][world]);

         Assert::IsTrue(d2.contains(rock));
         Assert::IsTrue(d2.contains(pebble));
         Assert::IsTrue(d2.contains(sand));
         Assert::IsTrue(d2.contains(hello));
         Assert::IsTrue(d2.contains(hello));
         Assert::IsTrue(d2[hello].contains(world));

         Assert::AreEqual(d1, d2);
      }

      TEST_METHOD(dict_iterator)
      {
         dict_t d1;

         d1[rock] = 3;
         d1[pebble] = 4;
         d1[sand] = 5.0;
         d1[hello] = L"6";

         int32_t count = 0;
         for (const auto& i : d1)
         {
            count += 1;
            if (i.first == rock)
               Assert::AreEqual<int32_t>(3, i.second);
            if (i.first == pebble)
               Assert::AreEqual<int64_t>(4, i.second);
            if (i.first == sand)
               Assert::AreEqual<double>(5.0, i.second);
            if (i.first == hello)
               Assert::AreEqual<text_t>(L"6", i.second);
         }

         Assert::AreEqual<int32_t>(4, count);
      }
   };
}
