#include "dak/object/transaction.h"
#include "dak/utility/undo_stack.h"

namespace dak::object
{
   void transaction_t::add(const ref_t<const object_t>& an_object)
   {
      if (!an_object)
         return;

      const auto pos = my_modified_objects.find(an_object);
      if (pos == my_modified_objects.end())
      {
         auto saved_copy = object_t::make(*an_object);
         my_modified_objects[an_object] = saved_copy;
      }
   }

   void transaction_t::forget()
   {
      my_modified_objects.clear();
   }

   void transaction_t::awaken_objects(const modified_objects_t& objects)
   {
      transaction_t undo_transaction;
      for (const auto& [dest, saved] : objects)
      {
         object_t* mod_dest = dest->modify(undo_transaction);
         object_t* mod_saved = saved->modify(undo_transaction);
         mod_dest->swap(*mod_saved);
      }
      undo_transaction.forget();
   }

   // Commit and cancel.
   void transaction_t::commit(undo_stack_t& undo_stack)
   {
      utility::undo_data_t data
      {
         std::move(my_modified_objects),
         [](std::any&) {},
         [](const std::any& objects) { awaken_objects(std::any_cast<modified_objects_t>(objects)); }
      };
      undo_stack.simple_commit(data);
      forget();
   }

   void transaction_t::cancel()
   {
      awaken_objects(my_modified_objects);
      forget();
   }
}
