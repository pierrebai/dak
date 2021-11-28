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
   // The transaction data that is kept when a transaction is commited.

   struct transaction_item_t
   {
      template <class T>
      transaction_item_t(const edit_ref_t<T>& an_object)
         : _swapper(make_swapper(an_object))
      {
      }

      // Swap current and saved objects.
      void undo_redo() const { _swapper(); }

   private:
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
   // Transation. Keep modified objects are create an undo when commited
   // or undo the changes if canceled.

   struct transaction_t
   {
      using modified_objects_t = std::unordered_map<const ref_counted_t*, transaction_item_t>;

      // Constructors.
      transaction_t() = default;
      transaction_t(const transaction_t&) = delete;

      // Assignment. Copy the whole transaction.
      transaction_t& operator =(const transaction_t&) = delete;

      // Add an object to the transaction.
      // Automatically done when an object is modified.
      template <class T>
      void add(const edit_ref_t<T>& an_object);

      // Commit and cancel. Both empty the tracked modified objects.
      void commit(struct timeline_t&);
      void cancel();

   private:
      void forget();

      // Verifies if the transaction already has the given object.
      bool has(const ref_counted_t* an_object);

      // Internal implementation of adding an object to the transaction.
      void add_stuff(const ref_counted_t* an_object, transaction_item_t&& item);

      // Swaps saved objects with current objects, implements undo/redo.
      static void undo_redo_objects(modified_objects_t& objects);

      modified_objects_t my_modified_objects;

      friend struct timeline_t;
   };

   template <class T>
   void transaction_t::add(const edit_ref_t<T>& an_object)
   {
      if (has(an_object))
         return;

      return add_stuff(an_object, transaction_item_t(an_object));
   }
}

#endif /* DAK_OBJECT_TRANSACTION_H */
