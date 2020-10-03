#pragma once

#ifndef DAK_UI_QT_CONVERT_H
#define DAK_UI_QT_CONVERT_H

#include <dak/geometry/point.h>
#include <dak/geometry/polygon.h>
#include <dak/geometry/rectangle.h>

#include <dak/ui/drawing.h>

#include <QtGui/qcolor.h>
#include <QtGui/qpolygon.h>

namespace dak::geometry
{
   class point_t;
   class polygon_t;
}

namespace dak::ui::qt
{
   using geometry::point_t;
   using geometry::polygon_t;
   using geometry::rectangle_t;

   ////////////////////////////////////////////////////////////////////////////
   //
   // Convert various type to their QT equivalent.

   QColor convert(const color_t& c);
   QPointF convert(const point_t& p);
   QPolygonF convert(const polygon_t& p);
   Qt::PenCapStyle convert(stroke_t::cap_style_t c);
   Qt::PenJoinStyle convert(stroke_t::join_style_t j);
   QRectF convert(const rectangle_t & r);

   color_t convert(const QColor & c);
   point_t convert(const QPointF& p);
   polygon_t convert(const QPolygonF& p);
   rectangle_t convert(const QRect& r);
   rectangle_t convert(const QSize& s);
}

#endif

// vim: sw=3 : sts=3 : et : sta : 
