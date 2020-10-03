#include <dak/utility/undo_stack.h>

namespace dak::utility
{
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
   }

   // Deaden the current my_top_transaction transaction_t data.
   void undo_stack_t::deaden_top()
   {
      for (auto& data : *my_top_transaction)
         if (data.deaden)
            data.deaden(data.data);
   }

   // Awaken the current my_top_transaction transaction_t data.
   void undo_stack_t::awaken_top() const
   {
      for (const auto& data : *my_top_transaction)
         if (data.awaken)
            data.awaken(data.data);
   }

   // Commit the given modified data to the undo stack.
   // Deaden the transaction_t data.
   void undo_stack_t::commit(const transaction_t& a_tr)
   {
      // If there were undone transactions_t, erase them now that we're commiting a new timeline.
      if (has_redo())
         my_undos.erase(my_top_transaction + 1, my_undos.end());

      my_undos.emplace_back(a_tr);
      my_top_transaction = my_undos.end() - 1;
      deaden_top();
   }

   // Undo awakens the previous transaction_t data. (The one before the last commit.)
   // Does nothing if at the start of the undo stack.
   void undo_stack_t::undo()
   {
      if (!has_undo())
         return;
      --my_top_transaction;
      awaken_top();
   }

   // Redo awakens the next transaction_t data that was commited.
   // Does nothing if at the end of the undo stack.
   void undo_stack_t::redo()
   {
      if (!has_redo())
         return;
      ++my_top_transaction;
      awaken_top();
   }
}

// vim: sw=3 : sts=3 : et : sta : 

