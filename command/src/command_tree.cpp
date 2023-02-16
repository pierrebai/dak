#include <dak/command/command_tree.h>

#include <dak/object/array.h>
#include <dak/object/dict.h>
#include <dak/utility/containers.h>
#include <dak/utility/text.h>

#include <map>
#include <set>
#include <stdexcept>

namespace dak::command
{
   namespace
   {
      using dak::utility::contains;
      using dak::utility::format;
      using dak::utility::join;
      using dak::utility::narrow_text;
      using dak::utility::L;

      struct command_tree_analysis_t
      {
         // Map from names of the commands to the commands.
         using all_commands_t = std::map<name_t, ref_t<command_t>>;

         // Ordered list of input or output parameters and their default values.
         using params_t = std::map<name_t, any_t>;

         // Map from names of the commands that do not depend on other commands to the commands.
         using root_commands_t = std::set<name_t>;

         // Map from command names to the sub-commands that depends on them.
         using sub_commands_t = std::map<name_t, std::vector<name_t>>;

         // A command name and an input parameter name as a pair.
         using command_param_t = std::pair<name_t, name_t>;

         // Map from command parameter name to the list of pairs of command names
         // and parameter names to which that parameter is connected. If the
         // command name is empty, then it is connected to the global command-tree
         // parameters.
         using param_connections_t = std::map<name_t, std::vector<command_param_t>>;

         // Map from command names to the connections of their inputs or outputs.
         // If the command name is empty, then the connections are from the inputs
         // or outputs of the global command-tree.
         using command_connections_t = std::map<name_t, param_connections_t>;

         // List of errors.
         using errors_t = std::vector<text_t>;

         all_commands_t          all_commands;
         params_t                input_params;
         params_t                output_params;

         root_commands_t         root_commands;
         sub_commands_t          sub_commands;

         // Note: we keep both connections indexed by inputs and outputs
         //       even though it is redundant, for simplicity. It makes
         //       easier to fill inputs from outputs and easier to verify
         //       and gather all inputs for a command.
         command_connections_t   inputs_connections;
         command_connections_t   outputs_connections;

         errors_t                errors;

         // Analyse the command tree to build the tree of commands
         // and validate that it is valid.
         void analyze(const command_tree_t& tree)
         {
            fill_all_commands(tree);
            fill_io_params(tree, command_tree_t::inputs, input_params);
            fill_io_params(tree, command_tree_t::outputs, output_params);

            fill_connections(tree);
         }

         command_t::outputs_t execute(const command_t::inputs_t& inputs, transaction_t& trans)
         {
            command_t::outputs_t outputs;

            // Accumulate the actual values of the inputs of commands.
            using commands_input_values_t = std::map<name_t, dict_t>;
            commands_input_values_t commands_input_values;

            // Initialize each command input with its default values.
            for (const auto& [sub_cmd_name, sub_cmd] : all_commands)
               commands_input_values[sub_cmd_name] = valid_ref_t<command_t>(sub_cmd)->get_inputs();

            // Ovedrwrite each command input with the global inputs parameter
            // it may be connected to.
            for (const auto& [sub_cmd_name, inputs_conns] : inputs_connections)
            {
               for (const auto& [input_param_name, output_conns] : inputs_connections)
               {
                  if (!inputs.contains(input_param_name))
                     continue;

                  const any_t value = inputs[input_param_name];
                  commands_input_values[sub_cmd_name][input_param_name] = value;
               }
            }

            // Loop over roots commands and fill the inputs of connected commands.
            // When a command no longer has input connections, move it to the
            // root commands.

            while (root_commands.size() > 0)
            {
               // Retrieve the next command to execute.
               const name_t sub_cmd_name = *root_commands.begin();
               root_commands.erase(sub_cmd_name);
               const valid_ref_t<command_t> sub_cmd(all_commands[sub_cmd_name]);

               // Prepare the inputs and outputs and execute the command.
               const dict_t sub_cmd_inputs = commands_input_values[sub_cmd_name];
               dict_t sub_cmd_outputs = sub_cmd->get_outputs();
               sub_cmd_outputs.append(sub_cmd->execute(sub_cmd_inputs, trans));

               // Transfer the output parameters values to the connected inputs.
               // Erase that inputs and if a sub-commands has no pending inputs,
               // then add it to the root commands.
               for (const auto& [output_param_name, output_conns] : outputs_connections[sub_cmd_name])
               {
                  for (const auto& [child_cmd_name, input_param_name] : output_conns)
                  {
                     const any_t value = sub_cmd_outputs[output_param_name];
                     if (child_cmd_name.is_valid())
                     {
                        commands_input_values[child_cmd_name][input_param_name] = value;
                        inputs_connections[child_cmd_name].erase(input_param_name);
                        if (inputs_connections[child_cmd_name].size() == 0)
                        {
                           sub_commands.erase(child_cmd_name);
                           root_commands.insert(child_cmd_name);
                        }
                     }
                     else
                     {
                        outputs[input_param_name] = value;
                     }
                  }
               }
            }

            return outputs;
         }

         bool is_valid() const
         {
            return errors.size() == 0 && (all_commands.size() == 0 || root_commands.size() > 0);
         }

      private:

         // Gather all commands used by the command tree.
         // Also fill the root commands with all commands. They will be filtered afterward.
         void fill_all_commands(const command_tree_t& tree)
         {
            for (auto [name, command] : tree.get_commands())
            {
               ref_t<command_t> cmd = command.as<ref_t<command_t>>();
               if (cmd.is_null())
               {
                  errors.push_back(format(L::t(L"missing command named %s"), name.to_str_ptr()));
                  continue;
               }

               ref_t<command_tree_t> sub_tree = cmd;
               if (sub_tree.is_valid())
               {
                  command_tree_analysis_t sub_tree_analysis;
                  sub_tree_analysis.analyze(*valid_ref_t<command_tree_t>(sub_tree));
                  errors.insert(errors.end(), sub_tree_analysis.errors.begin(), sub_tree_analysis.errors.end());
               }

               all_commands[name] = cmd;
               root_commands.insert(name);
            }
         }

         // Gather all global input or output parameters of the command tree.
         void fill_io_params(const command_tree_t& tree, const name_t& io_type_name, params_t& glonbal_params)
         {
            const dict_t& params = tree[io_type_name].as_dict();
            for (const auto& [name, value] : params)
            {
               glonbal_params[name] = value;
            }
         }

         // Gather and validate all connections between commands.
         // Also, remove commands that have their inputs connected to
         // another command from the root commands set.
         void fill_connections(const command_tree_t& tree)
         {
            for (const dict_t& connection : tree.get_connections())
            {
               const name_t from = connection[command_tree_t::from];
               const name_t output = connection[command_tree_t::output];
               const name_t dest = connection[command_tree_t::dest];
               const name_t input = connection[command_tree_t::input];

               verify_connection(from, output, command_t::outputs);
               verify_connection(dest, input, command_t::inputs);

               sub_commands[from].push_back(dest);
               outputs_connections[from][output].emplace_back(dest, input);
               inputs_connections[dest][input].emplace_back(from, output);

               // TODO: validate that the inputs and outputs parametert actually exist in the connected command.

               if (inputs_connections[dest][input].size() == 2)
                  errors.emplace_back(
                     format(L::t(L"parameter named %s of command named %s receives data from multiple connections"),
                        input.to_str_ptr(), dest.to_str_ptr()));

               // If the connection is between two commands, as opposed
               // to between global inputs or global outputs and a command,
               // then remove the destination from the roots.
               if (from.is_valid() && dest.is_valid())
                  root_commands.erase(dest);
            }
         }

         // Verify that the command has the required parameter.
         void verify_connection(const name_t& cmd_name, const name_t& param_name, const name_t& io_name)
         {
            if (cmd_name.is_valid())
            {
               const auto cmd_iter = all_commands.find(cmd_name);
               if (cmd_iter == all_commands.end())
               {
                  errors.emplace_back(format(L::t(L"missing command named %s"), cmd_name.to_str_ptr()));
                  return;
               }

               const valid_ref_t<command_t> cmd(cmd_iter->second);
               const bool has_param = (*cmd)[io_name].as_dict().contains(param_name);
               if (!has_param)
               {
                  errors.emplace_back(format(L::t(
                     L"missing %s parameter named %s in command named %s"),
                     io_name.to_str_ptr(), param_name.to_str_ptr(), cmd_name.to_str_ptr()));
               }
            }
            else
            {
               const bool is_input = (io_name == command_tree_t::inputs);
               const bool has_param = contains(is_input ? input_params : output_params, param_name);
               if (!has_param)
               {
                  errors.emplace_back(format(L::t(
                     L"missing %s global parameter named %s"),
                     io_name.to_str_ptr(), param_name.to_str_ptr()
                  ));
               }
            }
         }

         using parents_t = std::set<name_t>;

         void detect_command_loops(const command_tree_t& tree)
         {
            // If there are commands and yet none are roots, then it means
            // they were all connected to each others.
            if (all_commands.size() > 0 && root_commands.size() == 0)
            {
               errors.emplace_back(L::t(L"all commands form loops"));
            }

            // Otherwise, descent into each root and verify we never meet a parent
            // as a child.
            for (const name_t& root_name : root_commands)
            {
               // Track the parents as we traverse the command tree in order to
               // detect loops in the directed graph of commands that depend on
               // other commands.
               parents_t parents;
               detect_command_loop(root_name, parents);
            }
         }

         void detect_command_loop(const name_t& cmd_name, parents_t& parents)
         {
            if (contains(parents, cmd_name))
            {
               errors.emplace_back(format(L::t(
                  L"loop formed by command named %s"), cmd_name.to_str_ptr()));

               // Do not continue: there is a loop, we would recurse infinitely.
               return;
            }

            parents.insert(cmd_name);

            for (const auto& [output_name, sub_connections] : outputs_connections[cmd_name])
            {
               for (const auto& [sub_name, input_name] : sub_connections)
               {
                  detect_command_loop(sub_name, parents);
               }
            }

            parents.erase(cmd_name);
         }

      };

      command_t::outputs_t execute_command_tree(const valid_ref_t<command_t>& cmd, const command_t::inputs_t& inputs, transaction_t& trans)
      {
         valid_ref_t<command_tree_t> tree = cmd;

         command_tree_analysis_t analysis;

         analysis.analyze(*tree);
         if (!analysis.is_valid())
            throw std::runtime_error(narrow_text(join(analysis.errors)).c_str());

         command_t::outputs_t outputs = tree->get_outputs();
         outputs.append(analysis.execute(inputs, trans));
         return outputs;
      }
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Well-known names making up a command tree.

   const name_t& command_tree_t::commands = dak::object::voc::commands;
   const name_t& command_tree_t::from = dak::object::voc::from;
   const name_t& command_tree_t::output = dak::object::voc::output;
   const name_t& command_tree_t::dest = dak::object::voc::dest;
   const name_t& command_tree_t::input = dak::object::voc::input;
   const name_t& command_tree_t::connections = dak::object::voc::connections;

   //////////////////////////////////////////////////////////////////////////
   //
   // Helpers

   const command_tree_t::commands_t command_tree_t::get_commands() const
   {
      return (*this)[commands].as<commands_t>();
   }

   const command_tree_t::connections_t command_tree_t::get_connections() const
   {
      return (*this)[connections].as<connections_t>();
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Prototypes

   command_tree_t::connection_t command_tree_t::create_connection_prototype()
   {
      dict_t conn;
      conn[from] = name_t();
      conn[output] = name_t();
      conn[dest] = name_t();
      conn[input] = name_t();
      return conn;
   }

   command_tree_t::connection_t command_tree_t::get_connection_prototype()
   {
      static const connection_t conn = create_connection_prototype();
      return conn;
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Prototype of a commands tree: contains the default execute function,
   // empty inputs, empty outputs and empty connections.

   command_tree_t::command_tree_t()
      : command_tree_t(commands_t(), inputs_t(), outputs_t(), connections_t())
   {
   }

   command_tree_t::command_tree_t(
      const commands_t& some_commands,
      const inputs_t& some_inputs, const outputs_t& some_outputs,
      const connections_t& some_connections)
      : command_t(execute_command_tree, some_inputs, some_outputs)
   {
      my_values[commands]    = some_commands;
      my_values[connections] = some_connections;
   }
}
