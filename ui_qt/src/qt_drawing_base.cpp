#include <dak/ui/qt/qt_drawing_base.h>
#include <dak/ui/qt/convert.h>
#include <dak/ui/layered.h>

#include <dak/geometry/utility.h>

namespace dak::ui::qt
{
   using geometry::transform_t;

   QPen qt_drawing_base_t::get_pen() const
   {
      const auto& co = get_color();
      const auto& strk = get_stroke();
      return QPen(convert(co), strk.width, Qt::SolidLine, convert(strk.cap), convert(strk.join));
   }

   QBrush qt_drawing_base_t::get_brush() const
   {
      const auto& co = get_color();
      return QBrush(convert(co));
   }

   static void clear_background(drawing_t& drw)
   {
      drw.set_color(color_t::white());
      drw.fill_polygon(polygon_t::from_rect(drw.get_bounds()).apply(drw.get_transform().invert()));
   }

   void draw_layered(drawing_t& drw, ui::layered_t* layered)
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

// vim: sw=3 : sts=3 : et : sta : 
