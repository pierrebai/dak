#pragma once

#ifndef DAK_OBJECT_TRANSACTION_H
#define DAK_OBJECT_TRANSACTION_H

#include <dak/utility/types.h>

#include <map>

namespace dak::object
{
   USING_DAK_UTILITY_TYPES;
   struct timeline_t;
   struct object_t;
   template <class T> struct edit_ref_t;

   //////////////////////////////////////////////////////////////////////////
   //
   // Transation. Keep modified objects are create an undo when commited
   // or undo the changes if canceled.

   struct transaction_t
   {
      using modified_objects_t = std::map<edit_ref_t<object_t>, object_t>;

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

      // Internal implementation of adding an object to the transaction.
      void add_stuff(const edit_ref_t<object_t>& an_object);

      // Swaps saved objects with current objects, implements undo/redo.
      static void undo_redo_objects(modified_objects_t& objects);

      modified_objects_t my_modified_objects;

      friend struct timeline_t;
   };

   template <class T>
   void transaction_t::add(const edit_ref_t<T>& an_object)
   {
      // TODO: support name_stuff_t and namespace_t.
      if constexpr (std::is_base_of<object_t, T>())
      {
         return add_stuff(an_object);
      }
   }
}

#endif /* DAK_OBJECT_TRANSACTION_H */
