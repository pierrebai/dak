#pragma once

#ifndef DAK_GEOMETRY_RECT_H
#define DAK_GEOMETRY_RECT_H

#include <dak/geometry/point.h>
#include <dak/geometry/transform.h>

#include <vector>
#include <cmath>

namespace dak::geometry
{
   class transform_t;

   ////////////////////////////////////////////////////////////////////////////
   //
   // A Rectangle, always axis-aligned.

   class rectangle_t
   {
   public:
      double x;
      double y;

      double width;
      double height;

      // Invalid rectangle.
      constexpr rectangle_t()
      : x(NAN), y(NAN), width(NAN), height(NAN)
      {
      }

      // Rectangle starting at the given coordinate with the given size.
      constexpr rectangle_t(double x, double y, double width, double height)
      : x(x), y(y), width(width), height(height)
      {
      }

      // Rectangle starting at the given point with the given size.
      constexpr rectangle_t(const point_t& pt, double width, double height)
         : x(pt.x), y(pt.y), width(width), height(height)
      {
      }

      // Rectangle starting at the given top-left point down to the given bottom-right point.
      constexpr rectangle_t(const point_t& tl, const point_t& br)
         : x(tl.x), y(tl.y), width(br.x - tl.x), height(br.y - tl.y)
      {
      }

      // The corners of the rectangle.
      point_t top_left() const { return point_t(x, y); }
      point_t top_right() const { return point_t(x+width, y); }
      point_t bottom_left() const { return point_t(x, y+height); }
      point_t bottom_right() const { return point_t(x+width, y+height); }

      // All points of the rectangle.
      std::vector<point_t> points() const { return std::vector<point_t>({ top_left(), top_right(), bottom_right(), bottom_left() }); }

      // Verify if invalid.
      bool is_invalid() const
      {
         const double n = NAN;
         return reinterpret_cast<const uint64_t&>(n) == reinterpret_cast<const uint64_t&>(x);
      }

      // Comparison. Two invalid are equal.
      bool operator ==(const rectangle_t& other) const;

      bool operator !=(const rectangle_t& other) const
      {
         return !(*this == other);
      }

      // Apply a transform to the rect.
      // The rect will stay orthogonal though. Its two corners will have moved.
      rectangle_t apply(const transform_t& t) const;

      // Combine two rectangles.
      rectangle_t combine(const rectangle_t& other) const;

      // Combine a rectangle with a point.
      // Make sure the rectangle is big enough to contain the point.
      rectangle_t combine(const point_t& pt) const;

      // Intersect two rectangles.
      rectangle_t intersect(const rectangle_t& other) const;

      // Scale a rectangle from its center.
      rectangle_t central_scale(double s) const;

      // Create a transform that will place this rectangle inside the other.
      transform_t center_inside(const rectangle_t& other);

      // Return the rectangle center.
      point_t center() const { return point_t(x, y) + point_t(width,height).scale(0.5); }
   };
}

#endif

// vim: sw=3 : sts=3 : et : sta : 
