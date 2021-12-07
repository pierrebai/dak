#include "dak/object/transaction.h"
#include "dak/object/object.h"
#include "dak/object/timeline.h"

namespace dak::object
{
   namespace
   {
      void undo_redo_objects(transaction_t::modified_objects_t& objects)
      {
         for (auto& [dest, item] : objects)
         {
            item.undo_redo();
         }
      }
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // transaction

   //static
   bool transaction_t::has(const ref_counted_t* an_object)
   {
      return my_modified_objects.find(an_object) != my_modified_objects.end();
   }

   void transaction_t::add_stuff(const ref_counted_t* an_object, transaction_item_t&& item)
   {
      my_modified_objects.insert(std::pair(an_object, std::move(item)));
   }

   void transaction_t::forget()
   {
      my_modified_objects.clear();
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Commit and cancel.

   void transaction_t::commit(timeline_t& commited)
   {
      commited.commit(std::move(my_modified_objects));
      forget();
   }

   void transaction_t::sub_commit(struct transaction_t& parent)
   {
      // Note: be sure to call insert() here, as that function guarantees
      //       that if an object was already inserted, it won't be inserted
      //       again, so we keep only the earlier one.
      //
      //       This assumes that all modifications done in the sub-transaction
      //       have occured in one block after the ones in the parent transaction.
      //       In other words the transaction are sequential, not interweaved.
      //       (Although the parent transaction can resume doing more modifications
      //        afterward.)
      for (auto&& item : my_modified_objects)
         parent.my_modified_objects.insert(item);
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
         my_commits.erase(my_top_commit, my_commits.end());

      my_commits.emplace_back(objects);

      my_top_commit = my_commits.end();
   }

   void timeline_t::undo()
   {
      if (!has_undo())
         return;

      --my_top_commit;
      undo_redo_objects(*my_top_commit);
   }

   void timeline_t::redo()
   {
      if (!has_redo())
         return;

      undo_redo_objects(*my_top_commit);
      ++my_top_commit;
   }
}
