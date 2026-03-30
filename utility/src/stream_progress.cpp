#include <dak/utility/stream_progress.h>

namespace dak::utility
{
   ////////////////////////////////////////////////////////////////////////////
   //
   // Report progress of work to a std::ostream.

   stream_progress_t::~stream_progress_t()
   {
      try
      {
         flush_progress();
      }
      catch (std::exception&)
      {
         // Dont'let exceptions out of the destructor.
      }
   }

   void stream_progress_t::update_progress(size_t a_total_count_so_far)
   {
      if (!my_stream)
         return;

      if (a_total_count_so_far < 2 * 1000)
         *my_stream << a_total_count_so_far << "\r";
      else if (a_total_count_so_far < 10 * 1000 * 1000)
         *my_stream << (a_total_count_so_far / 1000) << " thousands        \r";
      else if (a_total_count_so_far < 10 * 1000 * 1000 * 1000)
         *my_stream << (a_total_count_so_far / (1000 * 1000)) << " millions        \r";
      else
         *my_stream << (a_total_count_so_far / (1000 * 1000 * 1000)) << " billions        \r";
      
   }
}

