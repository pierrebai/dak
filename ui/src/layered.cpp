#include <dak/ui/layered.h>
#include <dak/ui/drawing.h>

namespace dak
{
   namespace ui
   {
      void layered_t::set_layers(const layers& l)
      {
         _layers = l;
      }

      void layered_t::draw(drawing_t& drw)
      {
         const auto end = _layers.rend();
         for (auto i = _layers.rbegin(); i != end; ++i)
         {
            drw.push_transform();
            drw.compose(trf);
            (*i)->draw(drw);
            drw.pop_transform();
         }
      }

      const transform_t& layered_t::get_transform() const
      {
         return trf;
      }

      layered_t& layered_t::set_transform(const transform_t& t)
      {
         trf = t;
         return *this;
      }

      layered_t& layered_t::compose(const transform_t& t)
      {
         trf = trf.compose(t);
         return *this;
      }
   }
}

// vim: sw=3 : sts=3 : et : sta : 
