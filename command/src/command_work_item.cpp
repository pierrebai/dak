#include <dak/command/command_work_item.h>

#include <stdexcept>

namespace dak::command
{
   command_work_item_t::~command_work_item_t()
   {
   }

   // Execute the command.
   void command_work_item_t::execute()
   {
      command->execute(inputs, transaction);
   }

   // static
   std::shared_ptr<command_work_item_t> command_work_item_t::make(valid_ref_t<command_t> a_command, const inputs_t some_inputs)
   {
      return std::shared_ptr<command_work_item_t>(new command_work_item_t(std::move(a_command), std::move(some_inputs)));
   }

   command_work_item_t::command_work_item_t(valid_ref_t<command_t> a_command, inputs_t some_inputs)
   : command(std::move(a_command))
   , inputs(std::move(some_inputs))
   {
   }

}
