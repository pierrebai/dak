#include <dak/command/command_tree.h>

#include <dak/object/array.h>
#include <dak/object/dict.h>
#include <dak/utility/containers.h>
#include <dak/utility/text.h>

#include <map>
#include <set>

namespace dak::command
{
   namespace
   {
      using dak::utility::contains;
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

         // Map from command output name to the list of pair of command name and input name
         // to which that output is connected. If the command name is empty, then it is
         // connected to the named outputs of the global command-tree.
         using output_connections_t = std::map<name_t, std::vector<command_param_t>>;

         // Map from command names to the connections of their output.
         // If the command name is empty, then the connections are from the inputs
         // of the global command-tree.
         using command_connections_t = std::map<name_t, output_connections_t>;

         // List of errors.
         using errors_t = std::vector<text_t>;

         all_commands_t          all_commands;
         params_t                input_params;
         params_t                output_params;

         root_commands_t         root_commands;
         sub_commands_t          sub_commands;
         command_connections_t   connections;
         errors_t                errors;

         void analyze(const command_tree_t& tree)
         {
            fill_all_commands(tree);
            fill_io_params(tree, command_tree_t::inputs, input_params);
            fill_io_params(tree, command_tree_t::outputs, output_params);

            fill_connections(tree);
         }

         // Gather all commands used by the command tree.
         // Also fill the root commands with all commands. They will be filtered afterward.
         void fill_all_commands(const command_tree_t& tree)
         {
            for (auto [name, command] : tree.get_commands())
            {
               // TODO: should we sub-analyse this command when it's a command_tree_t?
               all_commands[name] = command.as<ref_t<command_t>>();
               root_commands.insert(name);
            }
         }

         // Gather all global input or output parameters of the command tree.
         void fill_io_params(const command_tree_t& tree, const name_t& io_type_name, params_t& to_fill)
         {
            const dict_t& params = tree[io_type_name].as_dict();
            for (const auto& [name, value] : params)
            {
               to_fill[name] = value;
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
               connections[from][output].emplace_back(dest, input);

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
                  errors.emplace_back(L::t(text_t(L"missing command named ") + cmd_name.to_text()));
                  return;
               }

               const valid_ref_t<command_t> cmd(cmd_iter->second);
               const bool has_param = (*cmd)[io_name].as_dict().contains(param_name);
               if (!has_param)
               {
                  errors.emplace_back(L::t(
                     text_t(L"missing ") + io_name.to_text() + text_t(L" parameter named ") + param_name.to_text() +
                     text_t(L" in command named ") + cmd_name.to_text()
                  ));
               }
            }
            else
            {
               const bool is_input = (io_name == command_tree_t::inputs);
               const bool has_param = contains(is_input ? input_params : output_params, param_name);
               if (!has_param)
               {
                  errors.emplace_back(L::t(
                     text_t(L"missing ") + io_name.to_text() + text_t(L" global parameter named ") + param_name.to_text()
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
               errors.emplace_back(L::t(text_t(L"loop formed by command named ") + cmd_name.to_text()));
               // Do not continue: there is a loop, we would recurse infinitely.
               return;
            }

            for (const auto& [output_name, sub_connections] : connections[cmd_name])
            {
               for (const auto& [sub_name, input_name] : sub_connections)
               {
                  detect_command_loop(sub_name, parents);
               }
            }
         }

      };

      command_t::outputs_t execute_command_tree(const valid_ref_t<command_t>& cmd, const command_t::inputs_t& inputs, transaction_t& trans)
      {
         valid_ref_t<command_tree_t> tree = cmd;

         command_tree_analysis_t analysis;

         analysis.analyze(*tree);

         // TODO: verify errors, call all commands in the right order.

         return command_t::outputs_t();
      }
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Well-known names making up a command tree.

   const name_t& command_tree_t::commands    = dak::object::voc::commands;
   const name_t& command_tree_t::from        = dak::object::voc::from;
   const name_t& command_tree_t::output      = dak::object::voc::output;
   const name_t& command_tree_t::dest        = dak::object::voc::dest;
   const name_t& command_tree_t::input       = dak::object::voc::input;
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

   command_tree_t command_tree_t::create_prototype()
   {
      command_tree_t proto;
      proto.my_values[action ] = action_t(execute_command_tree);
      proto.my_values[inputs ] = inputs_t();
      proto.my_values[outputs] = outputs_t();
      proto.my_values[commands] = commands_t();
      proto.my_values[connections] = connections_t();
      return proto;
   }

   const command_tree_t& command_tree_t::get_prototype()
   {
      static const command_tree_t prototype = create_prototype();
      return prototype;
   }

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
}
