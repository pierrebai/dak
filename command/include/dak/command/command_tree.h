#pragma once

#ifndef DAK_COMMAND_COMMAND_TREE_H
#define DAK_COMMAND_COMMAND_TREE_H

#include <dak/command/command.h>
#include <dak/object/voc.h>

namespace dak::command
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Complex command made of a tree of sub-commands, with commands
   // outputs connected to other commands inputs.
   //
   // The inputs and outputs inherited by the base command class are the
   // initial inputs and final outputs of the tree of commands.
   //
   // The execute action is always the same (by default at least): figure
   // out the order of execution of commands based on the output/input
   // connections and execute the commands in the correct order.
   //
   // Note that a given output can be mapped to multiple inputs.
   // It could even be mapped to multiple inputs of a single other command.

   struct command_tree_t : command_t
   {
      DAK_OBJECT_REF_COUNTED(command_tree_t);

      // The commands that will be executed, each given a name.
      static const name_t& commands;
      using commands_t = dict_t;
      const commands_t get_commands() const;

      // Single connection decription.
      //
      // Dictionary mapping a previous command output to the input of
      // a subsequent command.
      // 
      // The source command is called `from`, the destination command
      // is called 'dest'. The output name is kept under 'output' and
      // the input name is kept under 'input'.
      //
      // If the 'from' command name is empty, then it refers to the inputs
      // of the overall command-tree. If the 'dest' command name is empty,
      // then it refers to the outputs of the overall command-tree.
      static const name_t& from;
      static const name_t& output;
      static const name_t& dest;
      static const name_t& input;
      using connection_t = dict_t;

      // The connections: array of mappings.
      // 
      static const name_t& connections;
      using connections_t = array_t;
      const connections_t get_connections() const;

      // Prototype of a commands tree: contains the default execute function,
      // empty inputs, empty outputs and empty connections. You can copy this
      // commands tree constant to make a specific command tree prototype.
      static const command_tree_t& get_prototype();

      // Prototype of a single inter-command connection.
      static connection_t get_connection_prototype();

   private:
      static command_tree_t create_prototype();
      static dict_t create_connection_prototype();
   };
}

#endif /* DAK_COMMAND_COMMAND_TREE_H */
