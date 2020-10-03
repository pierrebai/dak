#include <dak/ui/qt/painter_drawing.h>
#include <dak/ui/qt/convert.h>

#include <dak/geometry/constants.h>

#include <QtGui/qpainter.h>
#include <QtGui/qpainterpath.h>

namespace dak::ui::qt
{
   using geometry::PI;

   painter_drawing_t& painter_drawing_t::draw_line(const point_t& from, const point_t& to)
   {
      if (!painter)
         return *this;

      const point_t tf = from.apply(get_transform());
      const point_t tt = to.apply(get_transform());

      painter->setPen(get_pen());
      painter->drawLine(tf.x, tf.y, tt.x, tt.y);
      return *this;
   }

   painter_drawing_t& painter_drawing_t::draw_corner(const point_t& from, const point_t& mid, const point_t& to)
   {
      if (!painter)
         return *this;

      const point_t tf = from.apply(get_transform());
      const point_t tm = mid.apply(get_transform());
      const point_t tt = to.apply(get_transform());

      QPointF qps[] = { convert(tf), convert(tm), convert(tt) };

      painter->setPen(get_pen());
      painter->drawPolyline(qps, 3);
      return *this;
   }

   painter_drawing_t& painter_drawing_t::fill_polygon(const polygon_t& p)
   {
      if (!painter)
         return *this;

      QPainterPath path;
      path.addPolygon(convert(p.apply(get_transform())));
      path.closeSubpath();
      painter->fillPath(path, get_brush());
      return *this;
   }

   painter_drawing_t& painter_drawing_t::draw_polygon(const polygon_t& p)
   {
      if (!painter)
         return *this;

      QPainterPath path;
      path.addPolygon(convert(p.apply(get_transform())));
      path.closeSubpath();
      painter->setPen(get_pen());
      painter->drawPath(path);
      return *this;
   }

   static void adjust_radii(const dak::geometry::transform_t& trf, const point_t& center, double& rx, double& ry)
   {
      // If asked for a circle (both radius equal), then keep as circle.
      if (rx == ry)
      {
         rx = ry = trf.dist_from_zero(rx);
      }
      else
      {
         const point_t radius = point_t(rx, ry).apply(trf) - point_t::origin().apply(trf);
         rx = radius.x;
         ry = radius.y;
      }
   }

   painter_drawing_t& painter_drawing_t::fill_oval(const point_t& c, double rx, double ry)
   {
      if (!painter)
         return *this;

      const point_t center = c.apply(get_transform());
      adjust_radii(get_transform(), center, rx, ry);

      QPainterPath path;
      path.addEllipse(convert(center), rx, ry);
      painter->fillPath(path, get_brush());
      return *this;
   }

   painter_drawing_t& painter_drawing_t::draw_oval(const point_t& c, double rx, double ry)
   {
      if (!painter)
         return *this;

      const point_t center = c.apply(get_transform());
      adjust_radii(get_transform(), center, rx, ry);

      painter->setPen(get_pen());
      painter->drawEllipse(convert(center), rx, ry);
      return *this;
   }

   painter_drawing_t& painter_drawing_t::fill_arc(const point_t& c, double rx, double ry, double angle1, double angle2)
   {
      if (!painter)
         return *this;

      const point_t center = c.apply(get_transform());
      const point_t top_left = (c - point_t(rx, ry)).apply(get_transform());
      const point_t bottom_right = (c + point_t(rx, ry)).apply(get_transform());
      const point_t w_h = bottom_right - top_left;
      const point_t mid_right = (c + point_t(rx, 0)).apply(get_transform());

      const double delta_angle = angle2 - angle1;

      QPainterPath path;
      path.moveTo(center.x, center.y);
      path.lineTo(mid_right.x, mid_right.y);
      path.arcTo(top_left.x, top_left.y, w_h.x, w_h.y, angle1 * 180 / PI, -delta_angle * 180 / PI);
      painter->fillPath(path, get_brush());
      return *this;
   }

   painter_drawing_t& painter_drawing_t::fill_rect(const rectangle_t& r)
   {
      return fill_polygon(polygon_t::from_rect(r));
   }

   painter_drawing_t& painter_drawing_t::draw_rect(const rectangle_t& r)
   {
      return draw_polygon(polygon_t::from_rect(r));
   }

   rectangle_t painter_drawing_t::get_bounds() const
   {
      if (!painter)
         return rectangle_t(0, 0, 1, 1);

      const auto viewport = painter->viewport();
      return rectangle_t(viewport.x(), viewport.y(), viewport.width(), viewport.height());
   }
}

// vim: sw=3 : sts=3 : et : sta : 
