#pragma once

#ifndef DAK_TRANSATION_TRANSATION_H
#define DAK_TRANSATION_TRANSATION_H

#include <dak/utility/types.h>
#include <dak/object/object.h>

#include <map>

namespace dak::utility
{
   class undo_stack_t;
}

namespace dak::object
{
   USING_DAK_UTILITY_TYPES;
   using utility::undo_stack_t;

   //////////////////////////////////////////////////////////////////////////
   //
   // Transation. Keep modified objects are create an undo when commited
   // or undo the changes if canceled.

   struct transaction_t
   {
      using modified_objects_t = std::map<ref_t<object_t>, ref_t<object_t>>;

      // Constructors.
      transaction_t() = default;
      transaction_t(const transaction_t &) = delete;

      // Assignment. Copy the whole transaction.
      transaction_t& operator =(const transaction_t &) = delete;

      // Add an object to the transaction.
      // Automatically done when an object is modified.
      modifiable_object_t* add(const ref_t<object_t>& an_object);

      // Commit and cancel.
      void commit(undo_stack_t&);
      void cancel();

   protected:
      void forget();

      static void awaken_objects(const modified_objects_t& objects);

      modified_objects_t my_modified_objects;
   };
}

#endif /* DAK_TRANSATION_TRANSATION_H */
