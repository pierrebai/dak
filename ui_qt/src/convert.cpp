#include <dak/ui/qt/convert.h>

#include <dak/ui/drawing.h>

namespace dak::ui::qt
{
   color_t convert(const QColor & qc)
   {
      return dak::ui::color_t(qc.red(), qc.green(), qc.blue(), qc.alpha());
   }

   QColor convert(const color_t& c)
   {
      return QColor(c.r, c.g, c.b, c.a);
   }

   point_t convert(const QPointF& qp)
   {
      return point_t(qp.x(), qp.y());
   }

   QPointF convert(const point_t& p)
   {
      return QPointF(p.x, p.y);
   }

   polygon_t convert(const QPolygonF& p)
   {
      polygon_t poly;
      for (const auto& pt : p)
         poly.points.emplace_back(convert(pt));
      return poly;
   }

   QPolygonF convert(const polygon_t& p)
   {
      QPolygonF poly;
      for (const point_t& pt : p.points)
         poly.append(convert(pt));
      return poly;
   }

   rectangle_t convert(const QRect& r)
   {
      return rectangle_t(convert(r.topLeft()), convert(r.bottomRight()));
   }

   QRectF convert(const rectangle_t & r)
   {
      return QRectF(convert(r.top_left()), convert(r.bottom_right()));
   }

   rectangle_t convert(const QSize& s)
   {
      return rectangle_t(point_t(0., 0.), point_t(s.width(), s.height()));
   }

   Qt::PenCapStyle convert(stroke_t::cap_style_t c)
   {
      switch (c)
      {
         case stroke_t::cap_style_t::flat:
            return Qt::PenCapStyle::FlatCap;
         case stroke_t::cap_style_t::square:
            return Qt::PenCapStyle::SquareCap;
         default:
         case stroke_t::cap_style_t::round:
            return Qt::PenCapStyle::RoundCap;
      }
   }

   Qt::PenJoinStyle convert(stroke_t::join_style_t j)
   {
      switch (j)
      {
         case stroke_t::join_style_t::miter:
            return Qt::PenJoinStyle::MiterJoin;
         case stroke_t::join_style_t::bevel:
            return Qt::PenJoinStyle::BevelJoin;
         default:
         case stroke_t::join_style_t::round:
            return Qt::PenJoinStyle::RoundJoin;
      }
   }
}

// vim: sw=3 : sts=3 : et : sta : 
