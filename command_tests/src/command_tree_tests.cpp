#include <CppUnitTest.h>

#include <dak/command/command_tree.h>

#include <dak/object/transaction.h>
#include <dak/object/voc.h>
#include <dak/utility/text.h>

#include <dak/command/tests/helpers.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace dak::object;

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
         command_tree_t tree;

         try
         {
            transaction_t trans;
            const dict_t exe_inputs;
            const dict_t exe_outputs = tree.execute(exe_inputs, trans);
            Assert::AreEqual(index_t(0), exe_outputs.size());
         }
         catch (const std::exception& e)
         {
            Assert::Fail((text_t(L"command threw an exception: ") + utility::widen_text(e.what())).c_str());
         }
      }

      TEST_METHOD(simple_command_tree_default_values)
      {
         command_t::action_t action =
            [](const command_t& cmd, const command_t::inputs_t& inputs, transaction_t& trans) -> command_t::outputs_t
            {
               command_t::outputs_t outputs;
               outputs[voc::distance] = inputs[voc::time].as_real() * inputs[voc::speed].as_real();
               return outputs;
            };

         command_tree_t::inputs_t inputs;
         inputs[voc::speed] = 10.;
         inputs[voc::time] = 2.;

         command_tree_t::outputs_t outputs;
         outputs[voc::distance] = 0.;

         ref_t<command_t> sub_cmd = command_t::make(action, inputs, outputs);

         command_tree_t::commands_t commands;
         commands[voc::c1] = sub_cmd;

         command_tree_t::connections_t connections;
         connections.append(value_t(command_tree_t::make_connection(name_t(), voc::speed, voc::c1, voc::speed)));
         connections.append(value_t(command_tree_t::make_connection(name_t(), voc::time, voc::c1, voc::time)));
         connections.append(value_t(command_tree_t::make_connection(voc::c1, voc::distance, name_t(), voc::distance)));

         command_tree_t tree(commands, inputs, outputs, connections);

         try
         {
            transaction_t trans;
            const dict_t exe_inputs;
            const dict_t exe_outputs = tree.execute(exe_inputs, trans);
            Assert::AreEqual(index_t(1), exe_outputs.size());
            Assert::AreEqual(20.0, exe_outputs[voc::distance].as_real());
         }
         catch (const std::exception& e)
         {
            Assert::Fail((text_t(L"command threw an exception: ") + utility::widen_text(e.what())).c_str());
         }
      }

      TEST_METHOD(simple_command_tree_custom_values)
      {
         command_t::action_t action =
            [](const command_t& cmd, const command_t::inputs_t& inputs, transaction_t& trans) -> command_t::outputs_t
         {
            command_t::outputs_t outputs;
            const double time = inputs[voc::time].as_real();
            const double speed = inputs[voc::speed].as_real();
            outputs[voc::distance] = time * speed;
            return outputs;
         };

         command_tree_t::inputs_t inputs;
         inputs[voc::speed] = 10.;
         inputs[voc::time] = 2.;

         command_tree_t::outputs_t outputs;
         outputs[voc::distance] = 0.;

         ref_t<command_t> sub_cmd = command_t::make(action, inputs, outputs);

         command_tree_t::commands_t commands;
         commands[voc::c1] = sub_cmd;

         command_tree_t::connections_t connections;
         connections.append(value_t(command_tree_t::make_connection(name_t(), voc::speed, voc::c1, voc::speed)));
         connections.append(value_t(command_tree_t::make_connection(voc::c1, voc::distance, name_t(), voc::distance)));

         command_tree_t tree(commands, inputs, outputs, connections);

         try
         {
            transaction_t trans;

            dict_t exe_inputs;
            exe_inputs[voc::speed] = 3.;

            const dict_t exe_outputs = tree.execute(exe_inputs, trans);
            Assert::AreEqual(index_t(1), exe_outputs.size());
            Assert::AreEqual(6.0, exe_outputs[voc::distance].as_real());
         }
         catch (const std::exception& e)
         {
            Assert::Fail((text_t(L"command threw an exception: ") + utility::widen_text(e.what())).c_str());
         }
      }
   };
}
