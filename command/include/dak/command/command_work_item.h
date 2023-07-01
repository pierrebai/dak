#pragma once

#ifndef DAK_COMMAND_COMMAND_WORK_ITEM_H
#define DAK_COMMAND_COMMAND_WORK_ITEM_H

#include <dak/command/command.h>
#include <dak/object/transaction.h>
#include <dak/utility/work_item.h>

#include <memory>

namespace dak::command
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Work item to execute a command executed in a transaction.

   struct command_work_item_t : utility::work_item_t
   {
      using inputs_t = command_t::inputs_t;

      const valid_ref_t<command_t>  command;       // Executed command.
      const inputs_t                inputs;        // Inputs for the command.
      transaction_t                 transaction;   // Transaction where the command is executed.

      // Destroy the command work item.
      ~command_work_item_t() override;

      // Execute the command in the transaction held by this work item.
      // The transaction will not be commited. The receiver of the work
      // item result should commit it where it wants.
      void execute() override;

      // Create a command work item for the given command and inputs.
      // 
      // The command will be executed in the transaction help by this
      // work item. The transaction will not be commited. The receiver
      // of the work item result should commit it where it wants.
      static std::shared_ptr<command_work_item_t> make(valid_ref_t<command_t>, inputs_t);

   private:
      command_work_item_t(valid_ref_t<command_t>, inputs_t);
   };

}

#endif /* DAK_COMMAND_COMMAND_WORK_ITEM_H */
