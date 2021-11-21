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
   // Commited transations. Keep modified objects are create an undo when commited
   // or undo the changes if canceled.

   struct timeline_t
   {
      using modified_objects_t = transaction_t::modified_objects_t;
      using commits_t = std::deque<modified_objects_t>;

      timeline_t();

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

#endif /* DAK_OBJECT_TIMELINE_H */
