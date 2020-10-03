#include <dak/ui/edges_map_layer.h>

#include <dak/ui/drawing.h>

namespace dak
{
   namespace ui
   {
      std::shared_ptr<layer_t> edges_map_layer_t::clone() const
      {
         return std::make_shared<edges_map_layer_t>(*this);
      }

      void edges_map_layer_t::make_similar(const layer_t& other)
      {
         layer_t::make_similar(other);

         if (const edges_map_layer_t* other_map_layer = dynamic_cast<const edges_map_layer_t*>(&other))
         {
            map = other_map_layer->map;
         }
      }

      void edges_map_layer_t::internal_draw(drawing_t& drw)
      {
         drw.set_color(color_t::black());
         drw.set_stroke(stroke_t(1.));
         for (const auto& edge : map.all())
            if (edge.is_canonical())
               drw.draw_line(edge.p1, edge.p2);
      }
   }
}

// vim: sw=3 : sts=3 : et : sta : 
