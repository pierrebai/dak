#include "CppUnitTest.h"

#include "dak/object/object.h"
#include "dak/object/timeline.h"
#include "dak/object/voc.h"
#include "dak/object/tests/helpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace dak::object::voc;

namespace dak::object::tests
{
   TEST_CLASS(object_tests)
	{
	public:
      object_tests()
      {
         any_op::register_ops();
         register_object_ops();
      }

      TEST_METHOD(object_base)
		{
         auto ro1 = object_t::make();

         transaction_t t1;
         auto& o1 = *ro1->modify(t1);

         Assert::AreEqual<index_t>(0, o1.size());

         o1[voc::rock] = 3;
         o1[voc::pebble] = 4;
         o1[voc::sand] = 5.0;
         o1[voc::hello] = L"6";
         o1[voc::world] = voc::rock;

         Assert::AreEqual<index_t>(5, o1.size());

         Assert::AreEqual<int32_t>(3, o1[rock]);
         Assert::AreEqual<int64_t>(4, o1[pebble]);
         Assert::AreEqual<double>(5.0, o1[sand]);
         Assert::AreEqual<text_t>(L"6", o1[hello]);
         Assert::AreEqual<name_t>(rock, o1[world]);

         Assert::IsTrue(o1.erase(rock));
         Assert::IsTrue(o1.erase(pebble));
         Assert::IsTrue(o1.erase(world));
         Assert::IsTrue(o1.erase(hello));
         Assert::IsTrue(o1.erase(sand));
         Assert::IsFalse(o1.erase(rock));

         Assert::AreEqual<index_t>(0, o1.size());

         auto ro2 = object_t::make(*ro1);

         Assert::AreEqual(*ro2, *ro1);

         auto ro3 = object_t::make(*ro1);

         Assert::AreEqual(*ro3, *ro1);
      }

      TEST_METHOD(object_append)
      {
         auto ro1 = object_t::make();

         transaction_t t1;
         auto& o1 = *ro1->modify(t1);

         o1[rock] = 3;
         o1[pebble] = 4;
         o1[sand] = 5.0;
         o1[hello][world] = rock;

         auto ro2 = object_t::make();
         auto& o2 = *ro2->modify(t1);

         o2 += o1;

         Assert::AreEqual<index_t>(4, o1.size());
         Assert::AreEqual<index_t>(4, o2.size());

         Assert::AreEqual<int32_t>(3, o2[rock]);
         Assert::AreEqual<int64_t>(4, o2[pebble]);
         Assert::AreEqual<double>(5.0, o2[sand]);
         Assert::AreEqual<name_t>(rock, o2[hello][world]);

         Assert::IsTrue(o2.contains(rock));
         Assert::IsTrue(o2.contains(pebble));
         Assert::IsTrue(o2.contains(sand));
         Assert::IsTrue(o2.contains(hello));
         Assert::IsTrue(o2.contains(hello));
         Assert::IsTrue(o2[hello].contains(world));

         Assert::AreEqual(o1, o2);
      }

      TEST_METHOD(object_iterator)
      {
         auto ro1 = object_t::make();

         transaction_t t1;
         auto& o1 = *ro1->modify(t1);

         o1[rock] = 3;
         o1[pebble] = 4;
         o1[sand] = 5.0;
         o1[hello] = L"6";

         int32_t count = 0;
         for (const auto& i : o1)
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

      TEST_METHOD(object_const)
      {
         valid_ref_t ro1 = object_t::make();
         Assert::AreEqual<index_t>(0, ro1->size());

         timeline_t undo_redo;

         {
            transaction_t t1;

            object_t& o1 = *ro1->modify(t1);

            o1[voc::rock] = 3;
            o1[voc::pebble] = 4;
            o1[voc::sand] = 5.0;
            o1[voc::hello] = L"6";
            o1[voc::world] = voc::rock;

            t1.commit(undo_redo);
         }

         Assert::AreEqual<index_t>(5, ro1->size());

         Assert::AreEqual<int32_t>(3, ro1[rock]);
         Assert::AreEqual<int64_t>(4, ro1[pebble]);
         Assert::AreEqual<double>(5.0, ro1[sand]);
         Assert::AreEqual<text_t>(L"6", ro1[hello]);
         Assert::AreEqual<name_t>(rock, ro1[world]);

         Assert::AreEqual<int32_t>(3, ro1->get(rock));
         Assert::AreEqual<int64_t>(4, ro1->get(pebble));
         Assert::AreEqual<double>(5.0, ro1->get(sand));
         Assert::AreEqual<text_t>(L"6", ro1->get(hello));
         Assert::AreEqual<name_t>(rock, ro1->get(world));
         //Assert::AreEqual<const datatype_t&>(typeid(void), ro1->get(absent).get_type());

         {
            transaction_t t2;

            auto& o1 = *ro1->modify(t2);

            o1[voc::rock] = 33;
            o1[voc::pebble] = 44;
            o1[voc::sand] = 55.0;
            o1[voc::hello] = L"66";
            o1[voc::world] = voc::age;

            t2.commit(undo_redo);
         }

         Assert::AreEqual<index_t>(5, ro1->size());

         Assert::AreEqual<int32_t>(33, ro1->get(rock));
         Assert::AreEqual<int64_t>(44, ro1->get(pebble));
         Assert::AreEqual<double>(55.0, ro1->get(sand));
         Assert::AreEqual<text_t>(L"66", ro1->get(hello));
         Assert::AreEqual<name_t>(age, ro1->get(world));
      }

   };
}
