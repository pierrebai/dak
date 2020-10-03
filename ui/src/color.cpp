#include <dak/ui/color.h>

namespace dak
{
   namespace ui
   {
      color_t::channel random_colors::next_color()
      {
         return color_t::channel(80. + 175. * rand() / (double) rand.max());
      };

      color_t random_colors::any()
      {
         return color_t(next_color(), next_color(), next_color(), 255);
      }

      color_t random_colors::red()
      {
         return color_t(next_color(), 0, 0, 255);
      }

      color_t random_colors::green()
      {
         return color_t(0, next_color(), 0, 255);
      }

      color_t random_colors::blue()
      {
         return color_t(0, 0, next_color(), 255);
      }

      color_t random_colors::cyan()
      {
         return color_t(0, next_color(), next_color(), 255);
      }

      color_t random_colors::yellow()
      {
         return color_t(next_color(), next_color(), 0, 255);
      }

      color_t random_colors::magenta()
      {
         return color_t(next_color(), 0, next_color(), 255);
      }

      color_t random_colors::grey()
      {
         const color_t::channel c = next_color();
         return color_t(c, c, c, 255);
      }
   }
}

// vim: sw=3 : sts=3 : et : sta : 
