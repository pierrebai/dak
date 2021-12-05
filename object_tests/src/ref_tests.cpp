#include "CppUnitTest.h"

#include "dak/object/edit_ref.h"
#include "dak/object/object.h"
#include "dak/object/timeline.h"
#include "dak/object/voc.h"
#include "dak/object/tests/helpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace dak::object::tests
{
   int32_t clear_count = 0;
   int32_t destroy_count = 0;

   void reset_counts()
   {
      clear_count = 0;
      destroy_count = 0;
   }

   struct detector_t : object_t
   {
      DAK_OBJECT_REF_COUNTED(detector_t);

      ~detector_t()
      {
         destroy_count += 1;
      }

      void clear() override
      {
         clear_count += 1;
         object_t::clear();
      }
   };

   TEST_CLASS(ref_tests)
	{
	public:
      TEST_METHOD_INITIALIZE(init)
      {
         reset_counts();
      }

		TEST_METHOD(weak_ref)
		{
         weak_ref_t<object_t> wro1;
         weak_ref_t<object_t> wro2;

         // Two object mutually strong-referencing each other
         // will prevent destruction and clearing.
         {
            auto ro1 = detector_t::make();
            auto ro2 = detector_t::make();

            wro1 = ro1;
            wro2 = ro2;

            {
               timeline_t timeline;
               transaction_t tr;
               auto& o1 = *ro1->modify(tr);

               o1[voc::other] = ro2;

               auto& o2 = *ro2->modify(tr);
               o2[voc::other] = ro1;

               tr.commit(timeline);
            }
         }

         Assert::AreEqual<int32_t>(0, clear_count);
         Assert::AreEqual<int32_t>(0, destroy_count);

         // Recreate a strong ref to one object and
         // modify it's reference to the other to be
         // weak: we will have double clearing.
         {
            valid_ref_t<object_t> ro1{ ref_t<object_t>(wro1) };

            timeline_t timeline;
            transaction_t tr;

            auto& o1 = *ro1->modify(tr);

            o1[voc::other] = wro2;

            tr.commit(timeline);
         }

         Assert::AreEqual<int32_t>(2, clear_count);
         Assert::AreEqual<int32_t>(0, destroy_count);

         // Clear the weak references: both obejct will be destroyed.
         wro1 = weak_ref_t<object_t>();
         wro2 = weak_ref_t<object_t>();

         Assert::AreEqual<int32_t>(2, clear_count);
         Assert::AreEqual<int32_t>(2, destroy_count);
      }

   };
}
