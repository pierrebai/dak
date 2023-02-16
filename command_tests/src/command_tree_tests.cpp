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
   namespace
   {
      command_tree_t::inputs_t get_speed_time_inputs()
      {
         command_tree_t::inputs_t inputs;
         inputs[voc::speed] = 10.;
         inputs[voc::time] = 2.;
         return inputs;
      }

      command_tree_t::outputs_t get_distance_outputs()
      {
         command_tree_t::outputs_t outputs;
         outputs[voc::distance] = 0.;
         return outputs;
      }

      command_t::action_t get_distance_action()
      {
         command_t::action_t action =
            [](const command_t& cmd, const command_t::inputs_t& inputs, transaction_t& trans) -> command_t::outputs_t
         {
            command_t::outputs_t outputs;
            outputs[voc::distance] = inputs[voc::time].as_real() * inputs[voc::speed].as_real();
            return outputs;
         };

         return action;
      }

      ref_t<command_t> make_distance_command()
      {
         return command_t::make(get_distance_action(), get_speed_time_inputs(), get_distance_outputs());
      }

      command_tree_t::inputs_t get_acceleration_time_inputs()
      {
         command_tree_t::inputs_t inputs;
         inputs[voc::acceleration] = 1.;
         inputs[voc::time] = 1.;
         return inputs;
      }

      command_tree_t::outputs_t get_speed_outputs()
      {
         command_tree_t::outputs_t outputs;
         outputs[voc::speed] = 0.;
         return outputs;
      }

      command_t::action_t get_speed_action()
      {
         command_t::action_t action =
            [](const command_t& cmd, const command_t::inputs_t& inputs, transaction_t& trans) -> command_t::outputs_t
         {
            command_t::outputs_t outputs;
            outputs[voc::speed] = inputs[voc::time].as_real() * inputs[voc::acceleration].as_real();
            return outputs;
         };

         return action;
      }

      ref_t<command_t> make_speed_command()
      {
         return command_t::make(get_speed_action(), get_acceleration_time_inputs(), get_speed_outputs());
      }

      command_tree_t get_distance_from_speed_command_tree()
      {
         command_tree_t::commands_t commands;
         commands[voc::c1] = make_distance_command();

         command_tree_t::connections_t connections;
         connections.append(value_t(command_tree_t::make_connection(name_t(), voc::speed, voc::c1, voc::speed)));
         connections.append(value_t(command_tree_t::make_connection(name_t(), voc::time, voc::c1, voc::time)));
         connections.append(value_t(command_tree_t::make_connection(voc::c1, voc::distance, name_t(), voc::distance)));

         return command_tree_t(commands, get_speed_time_inputs(), get_distance_outputs(), connections);
      }

      command_tree_t get_distance_from_acceleration_command_tree()
      {
         // Note: yeah, yeah, distance from acceleration over time would be more complex.
         //       What we are modeling here is that we accelerate for a given time, then
         //       when we reached the final speed, we start to measure the distance from
         //       that point as we continue on for the same amount of time.
         // 
         //       That is why we can multiply the final speed by the time to get the distance.
         //
         //       Look, we're writing tests here, not doing integrals.

         command_tree_t::commands_t commands;
         commands[voc::c1] = make_speed_command();
         commands[voc::c2] = make_distance_command();

         command_tree_t::connections_t connections;
         connections.append(value_t(command_tree_t::make_connection(name_t(), voc::acceleration, voc::c1, voc::acceleration)));
         connections.append(value_t(command_tree_t::make_connection(name_t(), voc::time, voc::c1, voc::time)));
         connections.append(value_t(command_tree_t::make_connection(name_t(), voc::time, voc::c2, voc::time)));
         connections.append(value_t(command_tree_t::make_connection(voc::c1, voc::speed, voc::c2, voc::speed)));
         connections.append(value_t(command_tree_t::make_connection(voc::c2, voc::distance, name_t(), voc::distance)));

         return command_tree_t(commands, get_acceleration_time_inputs(), get_distance_outputs(), connections);
      }
   }


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
         command_tree_t tree = get_distance_from_speed_command_tree();

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
         command_tree_t tree = get_distance_from_speed_command_tree();

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

      TEST_METHOD(two_commands_tree_custom_values)
      {
         command_tree_t tree = get_distance_from_acceleration_command_tree();

         try
         {
            transaction_t trans;

            dict_t exe_inputs;
            exe_inputs[voc::acceleration] = 4.;
            exe_inputs[voc::time] = 2.;

            const dict_t exe_outputs = tree.execute(exe_inputs, trans);
            Assert::AreEqual(index_t(1), exe_outputs.size());
            Assert::AreEqual(16.0, exe_outputs[voc::distance].as_real());
         }
         catch (const std::exception& e)
         {
            Assert::Fail((text_t(L"command threw an exception: ") + utility::widen_text(e.what())).c_str());
         }
      }

      TEST_METHOD(command_tree_missing_cmd_inputs)
      {
         command_tree_t::commands_t commands;
         commands[voc::c1] = make_distance_command();

         command_tree_t::connections_t connections;
         connections.append(value_t(command_tree_t::make_connection(name_t(), voc::time, voc::c1, voc::rock)));

         command_tree_t tree(commands, get_speed_time_inputs(), get_distance_outputs(), connections);

         try
         {
            transaction_t trans;

            dict_t exe_inputs;
            const dict_t exe_outputs = tree.execute(exe_inputs, trans);
            Assert::Fail(L"command should have thrown an exception");
         }
         catch (const std::exception& e)
         {
            Assert::IsTrue(std::string(e.what()).find("missing inputs parameter named rock in command named c1") != std::string::npos);
         }
      }

      TEST_METHOD(command_tree_missing_global_inputs)
      {
         command_tree_t::commands_t commands;
         commands[voc::c1] = make_distance_command();

         command_tree_t::connections_t connections;
         connections.append(value_t(command_tree_t::make_connection(name_t(), voc::rock, voc::c1, voc::time)));

         command_tree_t tree(commands, get_speed_time_inputs(), get_distance_outputs(), connections);

         try
         {
            transaction_t trans;

            dict_t exe_inputs;
            const dict_t exe_outputs = tree.execute(exe_inputs, trans);
            Assert::Fail(L"command should have thrown an exception");
         }
         catch (const std::exception& e)
         {
            Assert::IsTrue(std::string(e.what()).find("missing global inputs parameter named rock") != std::string::npos);
         }
      }

      TEST_METHOD(command_tree_missing_cmd_outputs)
      {
         command_tree_t::commands_t commands;
         commands[voc::c1] = make_distance_command();

         command_tree_t::connections_t connections;
         connections.append(value_t(command_tree_t::make_connection(voc::c1, voc::rock, name_t(), voc::distance)));

         command_tree_t tree(commands, get_speed_time_inputs(), get_distance_outputs(), connections);

         try
         {
            transaction_t trans;

            dict_t exe_inputs;
            const dict_t exe_outputs = tree.execute(exe_inputs, trans);
            Assert::Fail(L"command should have thrown an exception");
         }
         catch (const std::exception& e)
         {
            Assert::IsTrue(std::string(e.what()).find("missing outputs parameter named rock in command named c1") != std::string::npos);
         }
      }

      TEST_METHOD(command_tree_missing_global_outputs)
      {
         command_tree_t::commands_t commands;
         commands[voc::c1] = make_distance_command();

         command_tree_t::connections_t connections;
         connections.append(value_t(command_tree_t::make_connection(voc::c1, voc::distance, name_t(), voc::rock)));

         command_tree_t tree(commands, get_speed_time_inputs(), get_distance_outputs(), connections);

         try
         {
            transaction_t trans;

            dict_t exe_inputs;
            const dict_t exe_outputs = tree.execute(exe_inputs, trans);
            Assert::Fail(L"command should have thrown an exception");
         }
         catch (const std::exception& e)
         {
            Assert::IsTrue(std::string(e.what()).find("missing global outputs parameter named rock") != std::string::npos);
         }
      }

      TEST_METHOD(command_tree_all_commands_loop)
      {
         command_tree_t::commands_t commands;
         commands[voc::c1] = make_distance_command();

         command_tree_t::connections_t connections;
         connections.append(value_t(command_tree_t::make_connection(voc::c1, voc::distance, voc::c1, voc::time)));

         command_tree_t tree(commands, get_speed_time_inputs(), get_distance_outputs(), connections);

         try
         {
            transaction_t trans;

            dict_t exe_inputs;
            const dict_t exe_outputs = tree.execute(exe_inputs, trans);
            Assert::Fail(L"command should have thrown an exception");
         }
         catch (const std::exception& e)
         {
            Assert::IsTrue(std::string(e.what()).find("all commands form loops") != std::string::npos);
         }
      }

      TEST_METHOD(command_tree_one_loop)
      {
         command_tree_t::commands_t commands;
         commands[voc::c1] = make_distance_command();
         commands[voc::c2] = make_speed_command();

         command_tree_t::connections_t connections;
         connections.append(value_t(command_tree_t::make_connection(name_t(), voc::time, voc::c1, voc::time)));
         connections.append(value_t(command_tree_t::make_connection(voc::c1, voc::distance, voc::c1, voc::speed)));
         connections.append(value_t(command_tree_t::make_connection(name_t(), voc::time, voc::c2, voc::time)));

         command_tree_t tree(commands, get_speed_time_inputs(), get_distance_outputs(), connections);

         try
         {
            transaction_t trans;

            dict_t exe_inputs;
            const dict_t exe_outputs = tree.execute(exe_inputs, trans);
            Assert::Fail(L"command should have thrown an exception");
         }
         catch (const std::exception& e)
         {
            Assert::IsTrue(std::string(e.what()).find("loop formed by command named c1") != std::string::npos);
         }
      }
   };
}
