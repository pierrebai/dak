#include <dak/object/command_tree.h>

#include <dak/object/array.h>
#include <dak/object/dict.h>

namespace dak::object
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Well-known names making up a command tree.

   const name_t& command_tree_t::commands    = voc::commands;
   const name_t& command_tree_t::from        = voc::from;
   const name_t& command_tree_t::output      = voc::output;
   const name_t& command_tree_t::dest        = voc::dest;
   const name_t& command_tree_t::input       = voc::input;
   const name_t& command_tree_t::connections = voc::connections;

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
      proto.my_values[action ] = action_t();
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
