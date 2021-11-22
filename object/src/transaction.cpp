#include "dak/object/transaction.h"
#include "dak/object/ref.h"
#include "dak/object/object.h"
#include "dak/object/timeline.h"

namespace dak::object
{
   //////////////////////////////////////////////////////////////////////////
   //
   // transaction

   //static
   void transaction_t::undo_redo_objects(modified_objects_t& objects)
   {
      transaction_t undo_transaction;
      for (auto& [dest, saved] : objects)
      {
         object_t& mod_dest = dest->modify(undo_transaction);
         mod_dest.swap(saved);
      }
      undo_transaction.forget();
   }

   void transaction_t::add(const edit_ref_t<object_t>& an_object)
   {
      const auto pos = my_modified_objects.find(an_object);
      if (pos == my_modified_objects.end())
      {
         my_modified_objects.insert(std::pair(an_object, object_t(*an_object)));
      }
   }

   void transaction_t::forget()
   {
      my_modified_objects.clear();
   }

   // Commit and cancel.
   void transaction_t::commit(timeline_t& commited)
   {
      commited.commit(std::move(my_modified_objects));
      forget();
   }

   void transaction_t::cancel()
   {
      undo_redo_objects(my_modified_objects);
      forget();
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // timeline.

   timeline_t::timeline_t()
   : my_top_commit(my_commits.end())
   {

   }

   // Commmit modified objects.
   void timeline_t::commit(modified_objects_t&& objects)
   {
      if (has_redo())
         my_commits.erase(my_top_commit + 1, my_commits.end());

      my_commits.emplace_back(objects);

      my_top_commit = my_commits.end();
   }

   void timeline_t::undo()
   {
      if (!has_undo())
         return;

      --my_top_commit;
      transaction_t::undo_redo_objects(*my_top_commit);
   }

   void timeline_t::redo()
   {
      if (!has_redo())
         return;

      transaction_t::undo_redo_objects(*my_top_commit);
      ++my_top_commit;
   }
}
