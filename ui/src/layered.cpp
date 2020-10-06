#include <dak/ui/layered.h>
#include <dak/ui/drawing.h>

namespace dak
{
   namespace ui
   {
      void layered_t::set_layers(const layers_t& l)
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

      void draw_layered(drawing_t& drw, layered_t* layered)
      {
         drw.set_color(color_t::white());
         drw.fill_rect(drw.get_bounds().apply(drw.get_transform().invert()));

         if (!layered)
            return;

         drw.set_color(color_t::black());
         drw.set_stroke(stroke_t(1.2));
         layered->draw(drw);
         drw.set_stroke(stroke_t(1));
      }
   }
}

// vim: sw=3 : sts=3 : et : sta : 
