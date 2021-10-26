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

      bool layer_t::operator==(const layer_t& other) const
      {
         return trf == other.trf;
      }

      void layer_t::draw(drawing_t& drw)
      {
         if (!is_drawn)
            return;

         drw.push_transform();
         drw.compose(trf);
         internal_draw(drw);
         drw.pop_transform();
      }

      const transform_t& layer_t::get_transform() const
      {
         return trf;
      }

      layer_t& layer_t::set_transform(const transform_t& t)
      {
         if (is_moving)
            trf = t;
         return *this;
      }

      layer_t& layer_t::compose(const transform_t& t)
      {
         if (is_moving)
            trf = trf.compose(t);
         return *this;
      }
   }
}

// vim: sw=3 : sts=3 : et : sta : 
