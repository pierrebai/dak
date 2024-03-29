#pragma once

#ifndef DAK_UTILITY_UNDO_STACK_H
#define DAK_UTILITY_UNDO_STACK_H

#include <dak/utility/types.h>

#include <vector>
#include <functional>

namespace dak::utility
{
   USING_DAK_UTILITY_TYPES;

   ////////////////////////////////////////////////////////////////////////////
   //
   // Data kept in an undo transaction.

   class undo_data_t
   {
   public:
      // The actual data kept in the undo stack for the application.
      any_t data;

      // Remove non-essential data that can be recreated.
      // Called during commit to put the data to sleep.
      // Can be empty if there is no data to put to sleep.
      std::function<void(any_t&)> deaden;

      // Recreate the non-essential data and emplace the data in the application.
      // Called during undo or redo to awaken the data.
      std::function<void(const any_t&)> awaken;
   };

   ////////////////////////////////////////////////////////////////////////////
   //
   // An object tracking data changing transactions and undo / redo stack.
   //
   // You initially commit the data that you want to be able to undo back
   // to a transaction object.
   //
   // ***  You cannot undo if the stack is empty, so don't forget  ***
   // ***  that initial commit!                                    ***
   //
   // Call commit with a undo_data_t filled with the new data in order
   // to commit that data to the undo stack.
   //
   // The undo function awakens the data that was saved before
   // that last commit. If there are not commit, nothing happens.
   //
   // The redo function awakens the data that was saved. It does nothing
   // if the top of the stack is reached.

   class undo_stack_t
   {
   public:
      // The list of all undo transactions.
      typedef std::vector<undo_data_t> transactions_t;

      // The function called when the undo stack changed (clear, commit, undo or redo called).
      std::function<void(undo_stack_t&)> changed;

      // Create an empty undo stack.
      undo_stack_t();

      // Clear the undo stack.
      void clear();

      // Commit the given modified data to the undo stack.
      // Deaden the transaction data.
      void commit(const undo_data_t& a_tr);

      // Undo awakens the previous transaction data. (The one before the last commit.)
      // Does nothing if at the start of the undo stack.
      void undo();

      // Redo awakens the next transaction data that was committed.
      // Does nothing if at the end of the undo stack.
      void redo();

      // Verify if there is anything to undo.
      bool has_undo() const { return my_top_transaction != my_undos.begin(); }

      // Verify if there is anything to redo.
      bool has_redo() const { return my_top_transaction != my_undos.end() && my_top_transaction != my_undos.end() - 1; }

      // Verify if an commit/undo/redo operation is underway.
      bool is_undoing() const { return my_is_undoing; }

      // Return the current full contents of the undo stack.
      const transactions_t& contents() const { return my_undos; }

   private:
      // Deaden the current my_top_transaction transaction data.
      void deaden_top();

      // Awaken the current my_top_transaction transaction data.
      void awaken_top() const;

      transactions_t my_undos;
      transactions_t::iterator my_top_transaction;
      bool my_is_undoing = false;
   };
}

#endif

// vim: sw=3 : sts=3 : et : sta : 

