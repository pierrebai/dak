#include <CppUnitTest.h>

#include <dak/command/command_tree.h>

#include <dak/object/transaction.h>
#include <dak/utility/text.h>

#include <dak/command/tests/helpers.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace dak::command::tests
{		
   TEST_CLASS(command_tree_tests)
   {
   public:
      command_tree_tests()
      {
         any_op::register_ops();
         object::register_object_ops();
         command::register_command_ops();
      }

      TEST_METHOD(empty_command_tree)
      {
         edit_ref_t<command_tree_t> tree = command_tree_t::make();

         transaction_t trans;
         dict_t inputs;

         try
         {
            tree->execute(inputs, trans);
         }
         catch (const std::exception& e)
         {
            Assert::Fail((text_t(L"command threw an exception: ") + utility::convert(e.what())).c_str());
         }
      }
   };
}
