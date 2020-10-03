#include <dak/ui/layer.h>
#include <dak/ui/drawing.h>

namespace dak
{
   namespace ui
   {
      void layer_t::make_similar(const layer_t& other)
      {
         trf = other.trf;
      }

      void layer_t::draw(drawing_t& drw)
      {
         if (hide)
            return;

         drw.push_transform();
         drw.compose(trf);
         internal_draw(drw);
         drw.pop_transform();
      }
   }
}

// vim: sw=3 : sts=3 : et : sta : 
