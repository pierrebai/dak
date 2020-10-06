#pragma once

#ifndef DAK_UI_QT_PAINTER_DRAWING_H
#define DAK_UI_QT_PAINTER_DRAWING_H

#include <dak/ui/qt/qt_drawing_base.h>

class QPainter;

namespace dak::ui::qt
{
   using geometry::point_t;
   using geometry::polygon_t;
   using geometry::rectangle_t;

   ////////////////////////////////////////////////////////////////////////////
   //
   // Draw on a QPainter.

   class painter_drawing_t : public qt_drawing_base_t
   {
   public:
      // Current QPainter. Nothing drawn if null.
      QPainter* painter;

      // Empty drawing.
      painter_drawing_t() : painter(nullptr) { }

      // Drawing on the given QPainter.
      painter_drawing_t(QPainter& p) : painter(&p) { }

      // ui::drawing_t interface, complete the implementation.
      painter_drawing_t& draw_line(const point_t& from, const point_t& to) override;
      painter_drawing_t& draw_corner(const point_t& from, const point_t& corner, const point_t& to) override;
      painter_drawing_t& fill_polygon(const polygon_t& p) override;
      painter_drawing_t& draw_polygon(const polygon_t& p) override;
      painter_drawing_t& fill_oval(const point_t& c, double rx, double ry) override;
      painter_drawing_t& draw_oval(const point_t& c, double rx, double ry) override;
      painter_drawing_t& fill_arc(const point_t& c, double rx, double ry, double angle1, double angle2) override;
      painter_drawing_t& fill_rect(const rectangle_t& r) override;
      painter_drawing_t& draw_rect(const rectangle_t& r) override;

      rectangle_t get_bounds() const override;
   };
}

#endif

// vim: sw=3 : sts=3 : et : sta : 
