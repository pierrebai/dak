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
            (*i)->draw(drw);
            drw.pop_transform();
         }
      }

      const transform_t& layered_t::get_transform() const
      {
         for (const auto& layer : _layers)
            if (layer->is_moving)
               return layer->get_transform();

         static const transform_t none = transform_t::identity();
         return none;
      }

      layered_t& layered_t::set_transform(const transform_t& t)
      {
         for (auto& layer : _layers)
            if (layer->is_moving)
               layer->set_transform(t);

         return *this;
      }

      layered_t& layered_t::compose(const transform_t& t)
      {
         for (auto& layer : _layers)
            if (layer->is_moving)
               layer->compose(t);

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
