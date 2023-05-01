#include <dak/object/transaction.h>
#include <dak/object/timeline.h>
#include <dak/object/object.h>

namespace dak::object
{
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

   void transaction_t::commit_into(timeline_t& timeline)
   {
      timeline.commit(std::move(my_modified_objects));
      forget();
   }

   void transaction_t::commit_into(struct transaction_t& parent)
   {
      // Note: be sure to call insert() here, as that function guarantees
      //       that if an object was already inserted, it won't be inserted
      //       again, so we keep the earlier one.
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
      timeline_t::undo_redo_objects(my_modified_objects);
      forget();
   }
}
