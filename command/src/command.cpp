#include <dak/command/command.h>

#include <dak/object/dict.h>

#include <stdexcept>

namespace dak::command
{
   namespace
   {
      command_t::outputs_t do_nothing(const valid_ref_t<command_t>&, const command_t::inputs_t&, transaction_t&)
      {
         return {};
      }
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Well-known names making up a command.

   const name_t& command_t::inputs = dak::object::voc::inputs;
   const name_t& command_t::action = dak::object::voc::action;
   const name_t& command_t::outputs = dak::object::voc::outputs;

   //////////////////////////////////////////////////////////////////////////
   //
   // Execution

   dict_t command_t::execute(const inputs_t& inputs, transaction_t& trans) const
   {
      return execute(valid_ref_t<command_t>(this), inputs, trans);
   }

   dict_t command_t::execute(const valid_ref_t<command_t>& cmd, const inputs_t& inputs, transaction_t& trans)
   {
      action_t action = cmd->get_action();
      if (!action)
         throw std::runtime_error("command contains no action");


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
   // Prototype of a command: contains an empty execute function,
   // empty inputs and empty outputs.

   command_t::command_t()
      : command_t(do_nothing, inputs_t(), outputs_t())
   {
   }

   command_t::command_t(const action_t& an_action, const inputs_t& some_inputs, const outputs_t& some_outputs)
      : constant_t()
   {
      my_values[action]  = an_action;
      my_values[inputs]  = some_inputs;
      my_values[outputs] = some_outputs;
   }

}
