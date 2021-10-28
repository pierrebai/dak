#include <dak/ui/qt/qt_drawing_base.h>
#include <dak/ui/qt/convert.h>

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
}

// vim: sw=3 : sts=3 : et : sta : 
