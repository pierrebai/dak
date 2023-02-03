#pragma once

#ifndef DAK_OBJECT_TRANSACTION_H
#define DAK_OBJECT_TRANSACTION_H

#include <dak/utility/types.h>

#include <unordered_map>
#include <functional>

namespace dak::object
{
   USING_DAK_UTILITY_TYPES;
   struct timeline_t;
   struct object_t;
   struct ref_counted_t;
   template <class T> struct edit_ref_t;

   //////////////////////////////////////////////////////////////////////////
   //
   // A transaction item, tracking an object that got modified during a
   // transaction. The initial state and final state of an object can
   // be swapped by calling undo_redo().

   struct transaction_item_t
   {
      // Constructor taking a modifiable object.
      // 
      // The current state of the object is kept in a copy and 
      // a function that can swap the saved state in and out is kept alongside.
      template <class T>
      transaction_item_t(const edit_ref_t<T>& an_object)
         : _swapper(make_swapper(an_object))
      {
      }

      // Swaps the current and saved object state.
      void undo_redo() const { _swapper(); }

   private:
      // Creates a swapper function that keeps the saved state and can swap
      // between the current state and the saved state.
      template <class T>
      std::function<void()> make_swapper(edit_ref_t<T> an_object)
      {
         T saved_object(*an_object);

         std::function<void()> swapper = [an_object, saved_object]() mutable
         {
            saved_object.swap(*an_object);
         };

         return std::move(swapper);
      }

      std::function<void()> _swapper;
   };


   //////////////////////////////////////////////////////////////////////////
   //
   // Transation. Keeps track of modified objects. Creates an undo entry in
   // a timeline when commited. Reverts the changes if canceled.

   struct transaction_t
   {
      // The objects modified during the transation.
      // Only ony copy of the object is kept.
      // If an object is modified mlutiple times, only the first copy is kept.
      using modified_objects_t = std::unordered_map<const ref_counted_t*, transaction_item_t>;

      // Constructors.
      transaction_t() = default;

      // Do not allow copy, allow transfer.
      transaction_t(const transaction_t&) = delete;
      transaction_t(transaction_t&&) = default;

      // Do not allow copy, allow transfer.
      transaction_t& operator =(const transaction_t&) = delete;
      transaction_t& operator =(transaction_t&&) = default;

      // Add an object to the transaction.
      // Automatically called when an edit_ref_t is created.
      // As such, you should not need to call this by hand.
      template <class T>
      void add(const edit_ref_t<T>& an_object);

      // Commits all modified objects to the given timeline.
      // Empties the tracked modified objects.
      void commit(struct timeline_t&);

      // Transfers all modified objects to the given parent transaction.
      // Empties the tracked modified objects of this transaction.
      // 
      // sub-commit assumes that all modifications done in the sub-transaction
      // have occured in one block after the ones in the parent transaction.
      // In other words the transaction are sequential, not interweaved.
      // (Although the parent transaction can resume doing more modifications
      // afterward.)
      void sub_commit(struct transaction_t&);

      // Cancel all modified objects and restore their original tracked state.
      // Empties the tracked modified objects.
      void cancel();

   private:
      void forget();

      // Verifies if the transaction already has the given object.
      bool has(const ref_counted_t* an_object);

      // Internal implementation of adding an object to the transaction.
      void add_stuff(const ref_counted_t* an_object, transaction_item_t&& item);

      modified_objects_t my_modified_objects;
   };


   //////////////////////////////////////////////////////////////////////////
   //
   template <class T>
   void transaction_t::add(const edit_ref_t<T>& an_object)
   {
      if (has(an_object))
         return;

      return add_stuff(an_object, transaction_item_t(an_object));
   }
}

#endif /* DAK_OBJECT_TRANSACTION_H */
