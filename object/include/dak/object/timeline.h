#pragma once

#ifndef DAK_OBJECT_TIMELINE_H
#define DAK_OBJECT_TIMELINE_H

#include <dak/object/transaction.h>

#include <deque>

namespace dak::object
{
   USING_DAK_UTILITY_TYPES;

   //////////////////////////////////////////////////////////////////////////
   //
   // Commited transations. Keeps the given modified objects when commited.
   // Can undo and redo the commited transactions.

   struct timeline_t
   {
      using modified_objects_t = transaction_t::modified_objects_t;
      using commits_t = std::deque<modified_objects_t>;

      // Constructor.
      timeline_t();

      // Commmit modified objects.
      void commit(modified_objects_t&&);

      // Undo / redo
      bool has_undo() const { return my_top_commit != my_commits.begin(); }
      bool has_redo() const { return my_top_commit != my_commits.end(); }

      void undo();
      void redo();

      // Undo/redo helper: switch between the saved/modified states of the objects.
      // Can thus do both undo and redo.
      static void undo_redo_objects(modified_objects_t& objects);

   private:
      commits_t my_commits;
      commits_t::iterator my_top_commit;
   };

}

#endif /* DAK_OBJECT_TIMELINE_H */
