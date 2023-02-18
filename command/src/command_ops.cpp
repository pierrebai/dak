#include <dak/command/command.h>
#include <dak/command/command_tree.h>

#include <dak/any_op/op_makers.h>
#include <dak/object/dict.h>
#include <dak/object/op_makers.h>

#include <dak/utility/type_info.h>

namespace dak::command
{
   namespace
   {
      using namespace any_op;
      using namespace object;
      using action_t = command_t::action_t;

      bool to_bool(const command_t& cmd) { return bool(cmd.get_action()); }
      bool to_bool(const command_tree_t& cmd) { return bool(cmd.get_action()); }
      bool to_bool(const command_t::action_t& action) { return bool(action); }

      struct command_ops_init_t
      {
         command_ops_init_t()
         {
            supers_of_op_t::make<command_t     >::op<supers_t>(make_supers_of([]() -> supers_t { return { &typeid(object_t) }; }));
            supers_of_op_t::make<command_tree_t>::op<supers_t>(make_supers_of([]() -> supers_t { return { &typeid(command_t)  }; }));

            DAK_ANY_OP_COMPARABLE_MAKERS(dak::command::command_t);
            DAK_OBJECT_OP_MAKERS(dak::command::command_t);

            DAK_OBJECT_REF_OP_MAKERS(dak::command::command_t, dak::object::object_t);
            DAK_OBJECT_REF_OP_MAKERS(dak::object::object_t,   dak::command::command_t);

            DAK_ANY_OP_COMPARABLE_MAKERS(dak::command::command_tree_t);
            DAK_OBJECT_OP_MAKERS(dak::command::command_tree_t);

            DAK_OBJECT_REF_OP_MAKERS(dak::command::command_tree_t, dak::command::command_t);
            DAK_OBJECT_REF_OP_MAKERS(dak::command::command_tree_t, dak::object::object_t);
            DAK_OBJECT_REF_OP_MAKERS(dak::command::command_t,      dak::command::command_tree_t);
            DAK_OBJECT_REF_OP_MAKERS(dak::object::object_t,        dak::command::command_tree_t);

            DAK_ANY_OP_COMPARABLE_MAKERS(dak::command::command_t::action_t);

            size_op_t::make<>::op<index_t, command_tree_t>(
               [](const command_tree_t& arg) -> uint64_t
               { return arg.get_commands().size(); });

            //////////////////////////////////////////////////////////////////////////
            //
            // Mixed types

            is_compatible_op_t::make<command_t, command_tree_t>::op<bool>(details::yes);

            convert_op_t::make<command_t>::op<command_t, command_tree_t>(
               [](const command_tree_t& arg) -> command_t { return arg; });
         }
      };

      command_ops_init_t command_ops_init;
   }

   void register_command_ops()
   {
      // Needed so that the global operations are initialized in the tests.
      // All that is needed is to enter this file to create the globals.
   }
}
