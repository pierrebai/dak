#include <dak/ui/layered.h>
#include <dak/ui/drawing.h>

namespace dak
{
   namespace ui
   {
      void layered_t::set_layers(const layers_t& l)
      {
         my_layers = l;
      }

      bool layered_t::are_all_moving() const
      {
         for (const auto& layer : my_layers)
            if (!layer->is_moving)
               return false;

         return true;
      }

      bool layered_t::are_not_moving() const
      {
         for (const auto& layer : my_layers)
            if (layer->is_moving)
               return false;

         return true;
      }

      void layered_t::make_similar(const layered_t& other)
      {
         my_layers.clear();
         my_layers.reserve(other.my_layers.size());

         for (const auto& layer : other.my_layers)
            my_layers.emplace_back(layer->clone());
      }

      bool layered_t::operator==(const layered_t& other) const
      {
         if (my_layers.size() != other.my_layers.size())
            return false;

         for (size_t i = 0; i < my_layers.size(); ++i)
            if (*my_layers[i] != *other.my_layers[i])
               return false;

         return true;
      }

      void layered_t::draw(drawing_t& drw)
      {
         const auto end = my_layers.rend();
         for (auto i = my_layers.rbegin(); i != end; ++i)
         {
            drw.push_transform();
            (*i)->draw(drw);
            drw.pop_transform();
         }
      }

      const transform_t& layered_t::get_transform() const
      {
         for (const auto& layer : my_layers)
            if (layer->is_moving)
               return layer->get_transform();

         if (my_layers.size() > 0)
            return my_layers[0]->get_transform();

         static const transform_t none = transform_t::identity();
         return none;
      }

      layered_t& layered_t::set_transform(const transform_t& t)
      {
         for (auto& layer : my_layers)
            if (layer->is_moving)
               layer->set_transform(t);

         return *this;
      }

      layered_t& layered_t::compose(const transform_t& t)
      {
         for (auto& layer : my_layers)
            if (layer->is_moving)
               layer->compose(t);

         return *this;
      }

      void draw_layered(drawing_t& drw, const std::shared_ptr<layered_t>& layered)
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
