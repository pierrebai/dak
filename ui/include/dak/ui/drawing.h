#pragma once

#ifndef DAK_UI_DRAWING_H
#define DAK_UI_DRAWING_H

#include <dak/geometry/rectangle.h>
#include <dak/geometry/point.h>
#include <dak/geometry/polygon.h>
#include <dak/geometry/transform.h>

#include <dak/ui/color.h>
#include <dak/ui/stroke.h>

namespace dak::ui
{
   using geometry::point_t;
   using geometry::polygon_t;
   using geometry::transform_t;
   using geometry::rectangle_t;

   ////////////////////////////////////////////////////////////////////////////
   //
   // API needed to draw.

   class drawing_t
   {
   public:
      virtual ~drawing_t() = 0 { }

      // Stroke manipulations.
      virtual stroke_t get_stroke() const = 0;
      virtual drawing_t& set_stroke(const stroke_t& s) = 0;

      // Color manipulations.
      virtual color_t get_color() const = 0;
      virtual drawing_t& set_color(const color_t& c) = 0;

      // Drawing.
      virtual drawing_t& draw_line(const point_t& from, const point_t& to) = 0;
      virtual drawing_t& draw_corner(const point_t& from, const point_t& corner, const point_t& to) = 0;
      virtual drawing_t& fill_polygon(const polygon_t& p) = 0;
      virtual drawing_t& draw_polygon(const polygon_t& p) = 0;
      virtual drawing_t& fill_oval(const point_t& c, double rx, double ry) = 0;
      virtual drawing_t& draw_oval(const point_t& c, double rx, double ry) = 0;
      virtual drawing_t& fill_arc(const point_t& c, double rx, double ry, double angle1, double angle2) = 0;
      virtual drawing_t& fill_rect(const rectangle_t& r) = 0;
      virtual drawing_t& draw_rect(const rectangle_t& r) = 0;

      void draw_arrow(const point_t& from, const point_t& to, double length, double half_width);
      void fill_arrow(const point_t& from, const point_t& to, double length, double half_width);

      // Note: the bounds are *without* the transform.
      //       They are the true bounds of the drawing surface.
      virtual rectangle_t get_bounds() const = 0;

      // Transform applied to all the points in the drawing commands.
      virtual const transform_t& get_transform() const = 0;
      virtual drawing_t& set_transform(const transform_t&) = 0;
      virtual drawing_t& compose(const transform_t&) = 0;
      virtual drawing_t& push_transform() = 0;
      virtual drawing_t& pop_transform() = 0;
   };
}

#endif

// vim: sw=3 : sts=3 : et : sta : 
