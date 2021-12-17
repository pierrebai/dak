#include <dak/utility/undo_stack.h>

#include <CppUnitTest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace dak::utility;
using namespace std;

namespace dak::utility::tests
{		
	TEST_CLASS(undo_stack_tests)
	{
	public:
		
      TEST_METHOD(undo_stack_undo_redo)
      {
         undo_stack_t undo;

         int change_count = 0;
         undo.changed = [&change_count](undo_stack_t&) { change_count++; };

         Assert::IsFalse(undo.has_undo());
         Assert::IsFalse(undo.has_redo());

         Assert::AreEqual<size_t>(0, undo.contents().size());

         struct data
         {
            data(double a) : a(a), a_squared(a*a) { }

            double a = 0.;
            double a_squared = 0.;
         };

         data my_data(7.);

         Assert::AreEqual(7., my_data.a);
         Assert::AreEqual(49., my_data.a_squared);

         auto commit = [&]()
         {
            undo.commit(
            {
               my_data,
               [&](any_t& d)
               {
                  std::any_cast<data&>(d).a_squared = 0.;
               },
               [&my_data=my_data](const any_t& d)
               {
                  my_data = std::any_cast<const data&>(d);
                  my_data.a_squared = my_data.a * my_data.a;
               }
            });
         };

         commit();

         Assert::IsFalse(undo.has_undo());
         Assert::IsFalse(undo.has_redo());
         Assert::AreEqual(1, change_count);

         Assert::AreEqual(7., my_data.a);
         Assert::AreEqual(49., my_data.a_squared);

         Assert::AreEqual<size_t>(1, undo.contents().size());
         Assert::AreEqual(7., std::any_cast<const data&>(undo.contents().back().data).a);
         Assert::AreEqual(0., std::any_cast<const data&>(undo.contents().back().data).a_squared);

         my_data = data(9.);

         commit();

         Assert::IsTrue(undo.has_undo());
         Assert::IsFalse(undo.has_redo());
         Assert::AreEqual(2, change_count);

         Assert::AreEqual(9., my_data.a);
         Assert::AreEqual(81., my_data.a_squared);

         Assert::AreEqual<size_t>(2, undo.contents().size());
         Assert::AreEqual(9., std::any_cast<const data&>(undo.contents().back().data).a);
         Assert::AreEqual(0., std::any_cast<const data&>(undo.contents().back().data).a_squared);

         undo.undo();

         Assert::IsFalse(undo.has_undo());
         Assert::IsTrue(undo.has_redo());
         Assert::AreEqual(3, change_count);

         Assert::AreEqual(7., my_data.a);
         Assert::AreEqual(49., my_data.a_squared);

         undo.redo();

         Assert::IsTrue(undo.has_undo());
         Assert::IsFalse(undo.has_redo());
         Assert::AreEqual(4, change_count);

         Assert::AreEqual(9., my_data.a);
         Assert::AreEqual(81., my_data.a_squared);

         undo.clear();

         Assert::IsFalse(undo.has_undo());
         Assert::IsFalse(undo.has_redo());
         Assert::AreEqual(5, change_count);
      }

      TEST_METHOD(undo_stack_without_deaded_awaken)
      {
         undo_stack_t undo;

         undo.commit({ { 1.5 } });
         undo.commit({ { 3.5 } });

         Assert::IsTrue(undo.has_undo());
         Assert::IsFalse(undo.has_redo());

         undo.undo();

         Assert::IsFalse(undo.has_undo());
         Assert::IsTrue(undo.has_redo());

         undo.undo();

         Assert::IsFalse(undo.has_undo());
         Assert::IsTrue(undo.has_redo());

         undo.redo();

         Assert::IsTrue(undo.has_undo());
         Assert::IsFalse(undo.has_redo());

         undo.redo();

         Assert::IsTrue(undo.has_undo());
         Assert::IsFalse(undo.has_redo());
      }

      TEST_METHOD(undo_stack_empty_noop)
      {
         undo_stack_t undo;

         undo.undo();
         undo.undo();
         undo.undo();

         undo.redo();
         undo.redo();
         undo.redo();
         undo.redo();
         undo.redo();
         undo.redo();
         undo.redo();

         undo.undo();
         undo.undo();

         undo.redo();
         undo.redo();

         undo.commit({ { 1.5 } });
         undo.commit({ { 3.5 } });

         undo.redo();
         undo.redo();

         undo.undo();
         undo.undo();
         undo.undo();

         undo.redo();
         undo.redo();
         undo.redo();
         undo.redo();
         undo.redo();
         undo.redo();
         undo.redo();

         undo.undo();
         undo.undo();

         undo.redo();
         undo.redo();
      }

      TEST_METHOD(undo_stack_commit_clip_redo)
      {
         undo_stack_t undo;

         undo.commit({ { 1.5 } });
         undo.commit({ { 3.5 } });

         Assert::IsTrue(undo.has_undo());
         Assert::IsFalse(undo.has_redo());
         Assert::AreEqual<size_t>(2, undo.contents().size());

         undo.undo();

         Assert::IsFalse(undo.has_undo());
         Assert::IsTrue(undo.has_redo());
         Assert::AreEqual<size_t>(2, undo.contents().size());

         // This will clip the redo.
         undo.commit({ { 3.5 } });

         Assert::IsTrue(undo.has_undo());
         Assert::IsFalse(undo.has_redo());
         // Still two because one redo weas clipped.
         Assert::AreEqual<size_t>(2, undo.contents().size());
      }
   };
}
