#pragma once

#ifndef DAK_OBJECT_TRANSACTION_H
#define DAK_OBJECT_TRANSACTION_H

#include <dak/utility/types.h>
#include <dak/object/object.h>

#include <map>

namespace dak::object
{
   USING_DAK_UTILITY_TYPES;
   struct timeline_t;

   //////////////////////////////////////////////////////////////////////////
   //
   // Transation. Keep modified objects are create an undo when commited
   // or undo the changes if canceled.

   struct transaction_t
   {
      using modified_objects_t = std::map<valid_ref_t<object_t>, valid_ref_t<object_t>>;

      // Constructors.
      transaction_t() = default;
      transaction_t(const transaction_t &) = delete;

      // Assignment. Copy the whole transaction.
      transaction_t& operator =(const transaction_t &) = delete;

      // Add an object to the transaction.
      // Automatically done when an object is modified.
      void add(const valid_ref_t<object_t>& an_object);

      // Commit and cancel. Both empty the tracked modified objects.
      void commit(struct timeline_t&);
      void cancel();

   private:
      void forget();

      // Swaps saved objects with current objects, implements undo/redo.
      static void undo_redo_objects(const modified_objects_t& objects);

      modified_objects_t my_modified_objects;

      friend struct timeline_t;
   };
}

#endif /* DAK_OBJECT_TRANSACTION_H */
