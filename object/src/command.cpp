#include <dak/object/command.h>
#include <dak/object/dict.h>

namespace dak::object
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Well-known names making up a command.

   const name_t& command_t::inputs = voc::inputs;
   const name_t& command_t::action = voc::action;
   const name_t& command_t::outputs = voc::outputs;

   //////////////////////////////////////////////////////////////////////////
   //
   // Execution

   dict_t command_t::execute(const inputs_t& inputs, transaction_t& trans)
   {
      return execute(valid_ref_t<command_t>(this), inputs, trans);
   }

   dict_t command_t::execute(const valid_ref_t<command_t>& cmd, const inputs_t& inputs, transaction_t& trans)
   {
      action_t action = cmd->get_action();
      return action(cmd, inputs, trans);
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Helpers

   command_t::action_t command_t::get_action() const
   {
      return (*this)[action].as<action_t>();
   }

   const command_t::inputs_t command_t::get_inputs() const
   {
      return (*this)[inputs].as<inputs_t>();

   }

   const command_t::outputs_t command_t::get_outputs() const
   {
      return (*this)[outputs].as<outputs_t>();
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Prototype

   command_t command_t::create_prototype()
   {
      command_t proto;
      proto.my_values[action ] = action_t();
      proto.my_values[inputs ] = inputs_t();
      proto.my_values[outputs] = outputs_t();
      return proto;
   }

   const command_t& command_t::get_prototype()
   {
      static const command_t prototype = create_prototype();
      return prototype;
   }

}
