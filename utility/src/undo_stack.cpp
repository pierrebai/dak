#include <dak/utility/undo_stack.h>

namespace dak::utility
{
   namespace
   {
      // Keeps track if we are in the middle of an undo/redo operation.
      struct undoing_t
      {
         undoing_t(bool& f) : my_f(f) { my_f = true; }

         ~undoing_t() { my_f = false; }

      private:
         bool& my_f;
      };
   }

   // Create an empty undo stack.
   undo_stack_t::undo_stack_t()
   : my_top_transaction(my_undos.end())
   {
   }

   // Clear the undo stack.
   void undo_stack_t::clear()
   {
      my_undos.clear();
      my_top_transaction = my_undos.end();

      if (changed)
         changed(*this);
   }

   // Deaden the current my_top_transaction transaction data.
   void undo_stack_t::deaden_top()
   {
      for (auto& data : *my_top_transaction)
         if (data.deaden)
            data.deaden(data.data);
   }

   // Awaken the current my_top_transaction transaction data.
   void undo_stack_t::awaken_top() const
   {
      for (const auto& data : *my_top_transaction)
         if (data.awaken)
            data.awaken(data.data);
   }

   // Commit the given modified data to the undo stack.
   // Deaden the transaction data.
   void undo_stack_t::commit(const transaction_t& a_tr)
   {
      // Refuse to commit during undo/redo/commit.
      if (my_is_undoing)
         return;

      // If there were undone transactions, erase them now that we're commiting a new timeline.
      if (has_redo())
         my_undos.erase(my_top_transaction + 1, my_undos.end());

      undoing_t undoing(my_is_undoing);

      my_undos.emplace_back(a_tr);
      my_top_transaction = my_undos.end() - 1;
      deaden_top();

      if (changed)
         changed(*this);
   }

   void undo_stack_t::simple_commit(const simple_transaction_t& tr)
   {
      commit({ tr });
   }

   // Undo awakens the previous transaction data. (The one before the last commit.)
   // Does nothing if at the start of the undo stack.
   void undo_stack_t::undo()
   {
      if (!has_undo())
         return;

      undoing_t undoing(my_is_undoing);

      --my_top_transaction;
      awaken_top();

      if (changed)
         changed(*this);
   }

   // Redo awakens the next transaction data that was commited.
   // Does nothing if at the end of the undo stack.
   void undo_stack_t::redo()
   {
      if (!has_redo())
         return;

      undoing_t undoing(my_is_undoing);

      ++my_top_transaction;
      awaken_top();

      if (changed)
         changed(*this);
   }
}

// vim: sw=3 : sts=3 : et : sta : 

