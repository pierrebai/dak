#pragma once

#ifndef DAK_UI_QT_PAINT_DEVICE_DRAWING_H
#define DAK_UI_QT_PAINT_DEVICE_DRAWING_H

#include <dak/ui/qt/painter_drawing.h>

class QPaintDevice;

namespace dak::ui::qt
{
   using geometry::point_t;
   using geometry::polygon_t;
   using geometry::rectangle_t;

   ////////////////////////////////////////////////////////////////////////////
   //
   // Draw on a QPaintDevice.

   class paint_device_drawing_t : public painter_drawing_t
   {
   public:
      // Create a drawing on the given QT paint device.
      paint_device_drawing_t(QPaintDevice& pd) : paint_device(pd) { }

      // ui::drawing interface, complete the implementation.
      paint_device_drawing_t& draw_line(const point_t& from, const point_t& to) override;
      paint_device_drawing_t& draw_corner(const point_t& from, const point_t& corner, const point_t& to) override;
      paint_device_drawing_t& fill_polygon(const polygon_t& p) override;
      paint_device_drawing_t& draw_polygon(const polygon_t& p) override;
      paint_device_drawing_t& fill_oval(const point_t& c, double rx, double ry) override;
      paint_device_drawing_t& draw_oval(const point_t& c, double rx, double ry) override;
      paint_device_drawing_t& fill_arc(const point_t& c, double rx, double ry, double angle1, double angle2) override;
      paint_device_drawing_t& fill_rect(const rectangle_t& r) override;
      paint_device_drawing_t& draw_rect(const rectangle_t& r) override;

      rectangle_t get_bounds() const override;

   private:
      QPaintDevice& paint_device;
   };
}

#endif

// vim: sw=3 : sts=3 : et : sta : 
