#include <dak/utility/stopwatch.h>

#include <sstream>


namespace dak::utility
{
   // Create a stopwatch to measure elapsed time.
   // Optionally will fill a buffer when elapsed time is measured.
   stopwatch_t::stopwatch_t(double* a_seconds_buffer,
                            std::string* a_formatted_time_buffer,
                            std::wstring* a_wide_formatted_time_buffer)
   : my_seconds_buffer(a_seconds_buffer)
   , my_wide_formatted_time(a_wide_formatted_time_buffer)
   , my_formatted_time(a_formatted_time_buffer)
   {
      start();
   }

   // Destroy the stopwatch. Do a final measures if not stopped.
   // Updates all linked buffers that were given in constructors if not previously stopped.
   stopwatch_t::~stopwatch_t()
   {
      elapsed();
   }

   // Start a new measurement of time.
   void stopwatch_t::start()
   {
      my_begin_time = clock_t::now();
   }

   // Stop all measures and return the elapsed time.
   // Updates all linked buffers that were given in constructors if not previously stopped.
   double stopwatch_t::stop()
   {
      const double seconds = elapsed();

      my_seconds_buffer = nullptr;
      my_wide_formatted_time = nullptr;
      my_formatted_time = nullptr;

      return seconds;
   }

   template <class STREAM_TYPE>
   static auto format_time(double some_seconds)
   {
      STREAM_TYPE stream;

      const int seconds = static_cast<int>(std::floor(some_seconds));
      const int milliseconds = static_cast<int>((some_seconds - seconds) * 1000);

      if (seconds < 2 * 60)
         stream << seconds << "s " << (milliseconds % 1000) << "ms";
      else if (seconds < 60 * 60)
         stream << (seconds / 60) << "m " << (seconds % 60) << "s " << (milliseconds % 1000) << "ms";
      else
         stream << (seconds / 3600) << "h " << ((seconds / 60) % 60) << "m " << (seconds % 60) << "s " << (milliseconds % 1000) << "ms";

      return stream.str();
   }

   // Return the elapsed time so far but continue to measure time.
   // Updates all linked buffers that were given in constructors if not previously stopped.
   double stopwatch_t::elapsed()
   {
      const auto end_time = clock_t::now();

      set_elapsed(std::chrono::duration_cast<std::chrono::milliseconds>(end_time - my_begin_time).count() / 1000.);

      return my_seconds;
   }

   // Set the elapsed time.
   // Updates all linked buffers that were given in constructors if not previously stopped.
   void stopwatch_t::set_elapsed(double seconds)
   {
      my_seconds = seconds;

      if (my_seconds_buffer)
         *my_seconds_buffer = my_seconds;

      if (my_formatted_time)
         *my_formatted_time = format_time<std::ostringstream>(my_seconds);

      if (my_wide_formatted_time)
         *my_wide_formatted_time = format_time<std::wostringstream>(my_seconds);
   }
}

