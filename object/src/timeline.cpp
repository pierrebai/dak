#include <dak/object/timeline.h>

namespace dak::object
{
   namespace
   {
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // timeline.

   timeline_t::timeline_t()
   : my_top_commit(my_commits.end())
   {

   }

   // Commmit modified objects.
   void timeline_t::commit(modified_objects_t&& objects)
   {
      if (has_redo())
         my_commits.erase(my_top_commit, my_commits.end());

      my_commits.emplace_back(objects);

      my_top_commit = my_commits.end();
   }

   // static
   void timeline_t::undo_redo_objects(modified_objects_t& objects)
   {
      for (auto& [dest, item] : objects)
      {
         item.undo_redo();
      }
   }

   void timeline_t::undo()
   {
      if (!has_undo())
         return;

      --my_top_commit;
      undo_redo_objects(*my_top_commit);
   }

   void timeline_t::redo()
   {
      if (!has_redo())
         return;

      undo_redo_objects(*my_top_commit);
      ++my_top_commit;
   }
}
