#pragma once

#ifndef DAK_TRANSATION_TRANSATION_H
#define DAK_TRANSATION_TRANSATION_H

#include <dak/utility/types.h>
#include <dak/object/object.h>

#include <map>
#include <deque>

namespace dak::utility
{
   class undo_stack_t;
}

namespace dak::object
{
   USING_DAK_UTILITY_TYPES;
   struct commited_transactions_t;

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
      void commit(struct commited_transactions_t&);
      void cancel();

   private:
      void forget();

      static void undo_redo_objects(const modified_objects_t& objects);

      modified_objects_t my_modified_objects;

      friend struct commited_transactions_t;
   };


   //////////////////////////////////////////////////////////////////////////
   //
   // Commited transations. Keep modified objects are create an undo when commited
   // or undo the changes if canceled.

   struct commited_transactions_t
   {
      using modified_objects_t = transaction_t::modified_objects_t;
      using commits_t = std::deque<modified_objects_t>;

      commited_transactions_t();

      // Commmit modified objects.
      void commit(modified_objects_t&&);

      // Undo / redo
      bool has_undo() const { return my_top_commit != my_commits.begin(); }
      bool has_redo() const { return my_top_commit != my_commits.end(); }

      void undo();
      void redo();

   private:
      commits_t my_commits;
      commits_t::iterator my_top_commit;
   };

}

#endif /* DAK_TRANSATION_TRANSATION_H */
