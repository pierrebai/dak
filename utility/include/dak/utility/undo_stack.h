#pragma once

#ifndef DAK_UTILITY_UNDO_STACK_H
#define DAK_UTILITY_UNDO_STACK_H

#include <any>
#include <vector>
#include <functional>

namespace dak::utility
{
   ////////////////////////////////////////////////////////////////////////////
   //
   // Data kept in an undo transaction_t.

   class undo_data_t
   {
   public:
      // The actual data kept in the undo stack for the application.
      std::any data;

      // Remove non-essential data that can be recreated.
      // Called during commit to put the data to sleep.
      std::function<void(std::any&)> deaden;

      // Recreate the non-essential data and emplace the data in the application.
      // Called during undo or redo to awaken the data.
      std::function<void(const std::any&)> awaken;
   };

   ////////////////////////////////////////////////////////////////////////////
   //
   // An object tracking data changing transactions_t and undo / redo stack.
   //
   // You initially commit the data that you want to be able to undo back
   // to a transaction_t object.
   //
   // ***  You cannot undo if the stack is empty, so don't forget  ***
   // ***  that initial commit!                                    ***
   //
   // Call commit with a transaction_t filled with the new data in order
   // to commit that data to the undo stack.
   //
   // The undo function awakens the data that was saved before
   // that last commit. If there are not commit, nothing happens.
   //
   // The redo function awakens the data that was saved. It does nothing
   // if the my_top_transaction the stack is reached.

   class undo_stack_t
   {
   public:
      // The transaction_t data type and list of all undo transactions_t.
      typedef std::vector<undo_data_t> transaction_t;
      typedef std::vector<transaction_t> transactions_t;

      // Create an empty undo stack.
      undo_stack_t();

      // Clear the undo stack.
      void clear();

      // Commit the given modified data to the undo stack.
      // Deaden the transaction_t data.
      void commit(const transaction_t& a_tr);

      // Undo awakens the previous transaction_t data. (The one before the last commit.)
      // Does nothing if at the start of the undo stack.
      void undo();

      // Redo awakens the next transaction_t data that was committed.
      // Does nothing if at the end of the undo stack.
      void redo();

      // Verify if there is anything to undo.
      bool has_undo() const { return my_top_transaction != my_undos.begin(); }

      // Verify if there is anything to redo.
      bool has_redo() const { return my_top_transaction != my_undos.end() && my_top_transaction != my_undos.end() - 1; }

      // Return the current full contents of the undo stack.
      const transactions_t& contents() const { return my_undos; }

   private:
      // Deaden the current my_top_transaction transaction_t data.
      void deaden_top();

      // Awaken the current my_top_transaction transaction_t data.
      void awaken_top() const;

      transactions_t my_undos;
      transactions_t::iterator my_top_transaction;
   };
}

#endif

// vim: sw=3 : sts=3 : et : sta : 

