#include <dak/ui/qt/paint_device_drawing.h>
#include <dak/ui/qt/convert.h>

#include <QtGui/qpainter.h>
#include <QtGui/qpainterpath.h>

namespace dak::ui::qt
{
   paint_device_drawing_t& paint_device_drawing_t::draw_line(const point_t& from, const point_t& to)
   {
      QPainter tmp_painter(&paint_device);
      painter = &tmp_painter;
      painter_drawing_t::draw_line(from, to);
      painter = 0;
      return *this;
   }

   paint_device_drawing_t& paint_device_drawing_t::draw_corner(const point_t& from, const point_t& corner, const point_t& to)
   {
      QPainter tmp_painter(&paint_device);
      painter = &tmp_painter;
      painter_drawing_t::draw_corner(from, corner, to);
      painter = 0;
      return *this;
   }

   paint_device_drawing_t& paint_device_drawing_t::fill_polygon(const polygon_t& p)
   {
      QPainter tmp_painter(&paint_device);
      painter = &tmp_painter;
      painter_drawing_t::fill_polygon(p);
      painter = 0;
      return *this;
   }

   paint_device_drawing_t& paint_device_drawing_t::draw_polygon(const polygon_t& p)
   {
      QPainter tmp_painter(&paint_device);
      painter = &tmp_painter;
      painter_drawing_t::draw_polygon(p);
      painter = 0;
      return *this;
   }

   paint_device_drawing_t& paint_device_drawing_t::fill_oval(const point_t& c, double rx, double ry)
   {
      QPainter tmp_painter(&paint_device);
      painter = &tmp_painter;
      painter_drawing_t::fill_oval(c, rx, ry);
      painter = 0;
      return *this;
   }

   paint_device_drawing_t& paint_device_drawing_t::draw_oval(const point_t& c, double rx, double ry)
   {
      QPainter tmp_painter(&paint_device);
      painter = &tmp_painter;
      painter_drawing_t::draw_oval(c, rx, ry);
      painter = 0;
      return *this;
   }

   paint_device_drawing_t& paint_device_drawing_t::fill_arc(const point_t& c, double rx, double ry, double angle1, double angle2)
   {
      QPainter tmp_painter(&paint_device);
      painter = &tmp_painter;
      painter_drawing_t::fill_arc(c, rx, ry, angle1, angle2);
      painter = 0;
      return *this;
   }

   paint_device_drawing_t& paint_device_drawing_t::fill_rect(const rectangle_t& r)
   {
      QPainter tmp_painter(&paint_device);
      painter = &tmp_painter;
      painter_drawing_t::fill_rect(r);
      painter = 0;
      return *this;
   }

   paint_device_drawing_t& paint_device_drawing_t::draw_rect(const rectangle_t& r)
   {
      QPainter tmp_painter(&paint_device);
      painter = &tmp_painter;
      painter_drawing_t::draw_rect(r);
      painter = 0;
      return *this;
   }

   rectangle_t paint_device_drawing_t::get_bounds() const
   {
      return rectangle_t(0, 0, paint_device.width(), paint_device.height());
   }
}

// vim: sw=3 : sts=3 : et : sta : 
