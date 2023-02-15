#pragma once

#ifndef DAK_COMMAND_COMMAND_H
#define DAK_COMMAND_COMMAND_H

#include <dak/object/object.h>
#include <dak/object/types.h>
#include <dak/object/voc.h>

namespace dak::object
{
   struct transaction_t;
   struct value_t;
}

namespace dak::command
{
   USING_DAK_OBJECT_TYPES;

   //////////////////////////////////////////////////////////////////////////
   //
   // Command object. Do some processing.
   //
   // The processing is implemented as a function taking the command,
   // inputs and a transaction and producing outputs. The action is kept
   // in the command under the 'action' name.
   // 
   // The command parameters default are kept within the command
   // in a dict under the 'inputs' name.
   // 
   // The outputs of the command are kept within the command
   // in a dict under the 'outputs' name.
   //
   // A concrete command should be provided as a constant_t prototype
   // containing the execute function already filled. The inputs and
   // outputs dictionary should also be filled with default values.
   // This documents what the command expects as inputs and what
   // will be produced as outputs once executed.
   // 
   // To call a concrete command, a copy the prototype inputs into a dict
   // and call execute on the command.

   struct command_t : constant_t
   {
      DAK_OBJECT_REF_COUNTED(command_t);

      // Retrieve the inputs dictionary of the command.
      // 
      // Inputs to the command.
      static const name_t& inputs;
      using inputs_t = dict_t;
      const inputs_t get_inputs() const;

      // Retrieve the action function of the command.
      //
      // The action function signature of the executed command.
      static const name_t& action;
      using action_t = std::function<dict_t(const valid_ref_t<command_t>&, const inputs_t&, transaction_t&)>;
      action_t get_action() const;

      // Retrieve the outputs dictionary of the command.
      // 
      // Outputs of the command.
      static const name_t& outputs;
      using outputs_t = dict_t;
      const outputs_t get_outputs() const;

      // Execute the command in the given transaction.
      dict_t execute(const inputs_t&, transaction_t&);
      static dict_t execute(const valid_ref_t<command_t>&, const inputs_t&, transaction_t&);

      // Prototype of a command: contains an empty execute function,
      // empty inputs and empty outputs. You can copy this command
      // constant to make a specific command prototype.
      static const command_t& get_prototype();

   private:
      static command_t create_prototype();
   };

   //////////////////////////////////////////////////////////////////////////
   //
   // Register any_op operations on command_t, command_tree_t, command_t::action_t.

   void register_command_ops();

}

#endif /* DAK_COMMAND_COMMAND_H */
