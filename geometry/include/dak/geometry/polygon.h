#pragma once

#ifndef DAK_GEOMETRY_POLYGON_H
#define DAK_GEOMETRY_POLYGON_H

#include <dak/geometry/rectangle.h>

#include <vector>

namespace dak::geometry
{
   class point_t;
   class transform_t;

   ////////////////////////////////////////////////////////////////////////////
   //
   // A plain old polygon, in this case a dynamically-sized array of point
   // instances.

   class polygon_t
   {
   public:
      std::vector<point_t> points;

      // Empty polygon.
      polygon_t() { }

      // Polygon containing the given points.
      polygon_t(const std::vector<point_t>& pts) : points(pts) { }

      // Polygon containing a subset of the given points.
      polygon_t(const std::vector<point_t>& pts, int start, int end);

      // Make a regular polygon of n sides.
      static polygon_t make_regular(int n);

      // Make a polygon from a rectangle.
      static polygon_t from_rect(const rectangle_t& r) { return polygon_t(r.points()); }

      // Comparison.
      bool operator ==(const polygon_t& other) const
      {
         return points == other.points;
      }

      bool operator !=(const polygon_t& other) const
      {
         return !(points == other.points);
      }

      // Compare the points of the polygon.
      // The points are not re-ordered, so they may compare different even though they contain the same points.
      bool operator <(const polygon_t& other) const
      {
         return points < other.points;
      }

      // Apply a transform to the polygon.
      polygon_t apply(const transform_t& T) const;

      point_t center() const;

      // Perimeter of the polygon.
      double perimeter(bool closed = true) const;

      // Area of the polygon.
      double area() const;

      // The bounding rectangle containing the polygon.
      rectangle_t bounds() const;

      // Verify if a point is inside the polygon.
      bool is_inside(const point_t& apt) const;

      // Verify if the polygon is regular.
      bool is_regular() const;

      // Verify if the polygon intersect another polygon.
      bool intersects(const polygon_t& other) const;

      // Verify if the polygon is invalid. (Less than 3 sides.)
      bool is_invalid() const
      {
         return points.size() < 3;
      }
   };
}

#endif

// vim: sw=3 : sts=3 : et : sta : 
