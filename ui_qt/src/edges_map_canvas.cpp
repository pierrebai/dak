#include <dak/ui/qt/edges_map_canvas.h>

#include <QtGui/qpainter.h>

namespace dak::ui::qt
{
   ////////////////////////////////////////////////////////////////////////////
   //
   // A widget drawing_canvas_t working with a map.

   edges_map_canvas_t::edges_map_canvas_t(QWidget* parent)
   : drawing_canvas_t(parent)
   {
   }

   void edges_map_canvas_t::draw(drawing_t& drw)
   {
      draw_map(drw);
      drawing_canvas_t::draw(drw);
   }

   void edges_map_canvas_t::draw_map(dak::ui::drawing_t& drw) const
   {
      geometry::rectangle_t bounds = drw.get_bounds().apply(drw.get_transform().invert());
      drw.set_color(color_t::white());
      drw.fill_rect(bounds);

      drw.set_color(color_t::black());
      drw.set_stroke(stroke_t(1.2));
      for (const auto& edge : map.all())
         if (edge.is_canonical())
            drw.draw_line(edge.p1, edge.p2);
      drw.set_stroke(stroke_t(1));
   }
}

// vim: sw=3 : sts=3 : et : sta : 
