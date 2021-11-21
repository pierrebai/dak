#include "dak/object/transaction.h"

#include <deque>

namespace dak::object
{
   //static
   void transaction_t::undo_redo_objects(const modified_objects_t& objects)
   {
      transaction_t undo_transaction;
      for (const auto& [dest, saved] : objects)
      {
         object_t& mod_dest = dest->modify(undo_transaction);
         object_t& mod_saved = saved->modify(undo_transaction);
         mod_dest.swap(mod_saved);
      }
      undo_transaction.forget();
   }

   void transaction_t::add(const valid_ref_t<object_t>& an_object)
   {
      if (!an_object)
         return;

      const auto pos = my_modified_objects.find(an_object);
      if (pos == my_modified_objects.end())
      {
         auto saved_copy = object_t::make(*an_object);
         my_modified_objects.insert(std::pair(an_object, saved_copy));
      }
   }

   void transaction_t::forget()
   {
      my_modified_objects.clear();
   }

   // Commit and cancel.
   void transaction_t::commit(commited_transactions_t& commited)
   {
      commited.commit(std::move(my_modified_objects));
      forget();
   }

   void transaction_t::cancel()
   {
      undo_redo_objects(my_modified_objects);
      forget();
   }

   commited_transactions_t::commited_transactions_t()
   : my_top_commit(my_commits.end())
   {

   }

   // Commmit modified objects.
   void commited_transactions_t::commit(modified_objects_t&& objects)
   {
      if (has_redo())
         my_commits.erase(my_top_commit + 1, my_commits.end());

      my_commits.emplace_back(objects);

      my_top_commit = my_commits.end();
   }

   void commited_transactions_t::undo()
   {
      if (!has_undo())
         return;

      --my_top_commit;
      transaction_t::undo_redo_objects(*my_top_commit);
   }

   void commited_transactions_t::redo()
   {
      if (!has_redo())
         return;

      transaction_t::undo_redo_objects(*my_top_commit);
      ++my_top_commit;
   }
}
