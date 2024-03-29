#pragma once

#ifndef DAK_GEOMETRY_POINT_H
#define DAK_GEOMETRY_POINT_H

#include <dak/utility/number.h>

#include <cmath>
#include <cstdint>

namespace dak::geometry
{
   class transform_t;

   ////////////////////////////////////////////////////////////////////////////
   //
   // point in a geometrical map.

   class point_t
   {
   public:

      // Three common points.
      static constexpr point_t origin() { return point_t(0.0, 0.0); }
      static constexpr point_t unit_x() { return point_t(1.0, 0.0); }
      static constexpr point_t unit_y() { return point_t(0.0, 1.0); }

      // Invalid value used to fill invalid points.
      static constexpr double nan() { return 1e+300 * 1e+300 * 0.; }

      // Static invalid point. Used in some return values.
      static const point_t invalid;

      // Point coordinates, invalid by default.
      double x = nan();
      double y = nan();

      // Invalid point.
      constexpr point_t() {}

      // Point with coordinates.
      constexpr point_t(double x, double y) : x(x), y(y) { }

      // Swap two points.
      constexpr void swap(point_t& other)
      {
         { const double t = x; x = other.x; other.x = t; }
         { const double t = y; y = other.y; other.y = t; }
      }

      // Comparisons. Two invalid are equal.
      bool operator ==(const point_t& other) const
      {
         if (is_invalid())
            return other.is_invalid();

         return utility::near(x, other.x) && utility::near(y, other.y);
      }

      bool operator !=(const point_t& other) const
      {
         return !(*this == other);
      }

      // Less-than compares x coordinates first, then y, using the default tolerance.
      bool operator <(const point_t& other) const
      {
         if (utility::near_less(x, other.x))
            return true;

         if (utility::near_greater(x, other.x))
            return false;

         if (utility::near_less(y, other.y))
            return true;

         return false;
      }

      bool operator >(const point_t& other) const
      {
         return *this != other && !(*this < other);
      }

      // Verify if a point is invalid.
      bool is_invalid() const
      {
         return std::isnan(x);
      }

      // Return the square of the distance to the origin.
      constexpr double mag_2() const
      {
         return x * x + y * y;
      }

      // Return the distance to the origin.
      double mag() const;

      // Return the square of the distance between two points.
      constexpr double distance_2(point_t other) const
      {
         double dx = x - other.x;
         double dy = y - other.y;
         return dx * dx + dy * dy;
      }

      // Return the distance between two points.
      double distance(const point_t& other) const;

      // Make the point be on the unit circle. (Magnitude one.)
      point_t normalize() const;

      // Add two points.
      constexpr point_t operator +(const point_t& other) const
      {
         return point_t(x + other.x, y + other.y);
      }

      // Subtract two points.
      constexpr point_t operator -(const point_t& other) const
      {
         return point_t(x - other.x, y - other.y);
      }

      // Dot product betwen two points.
      constexpr double dot(const point_t& other) const
      {
         return x * other.x + y * other.y;
      }

      // Sin dot product betwen two points.
      constexpr double sin_dot(const point_t& other) const
      {
         return y * other.x - x * other.y;
      }

      // Scale a point uniformly.
      constexpr point_t scale(double r) const
      {
         return point_t(x * r, y * r);
      }

      // Scale a point differently in x and y.
      constexpr point_t scale(double xr, double yr) const
      {
         return point_t(x * xr, y * yr);
      }

      // Return a vector counter-clockwise perpendicular to this.
      constexpr point_t perp() const
      {
         return point_t(-y, x);
      }

      // Verify if this point is perpendicular to another. (Treated as vectors.)
      bool is_perp(const point_t& other) const
      {
         return utility::near_zero(dot(other));
      }

      // Add two points with reciprocal scaling (reciprocal to 1.)
      point_t convex_sum(const point_t& other, double t) const;

      // Return the absolute angle of the edge from this to other, in the
      // range -PI to PI.
      double angle(const point_t& other) const;

      // Angle with the unit-x at the origin.
      double angle() const;

      // Cross product betwen two points.
      constexpr double cross(const point_t& other) const
      {
         return (x * other.y) - (y * other.x);
      }

      // Get the section of arc swept out between the edges this ==> from
      // and this ==> to.
      double sweep(const point_t& from, const point_t& to) const;

      // Distance between this point and the line made by the two given points.
      double distance_to_line(const point_t& p, const point_t& q) const;

      // Square of the distance between this point and the line made by the two given points.
      double distance_2_to_line(point_t p, const point_t& q) const;

      // Return the proportion between zero and one of the point on the given line.
      // The result can be out of the range if not on the line.
      double parameterization_on_line(const point_t& p, const point_t& q) const;

      // Apply a transform to the point.
      point_t apply(const transform_t& t) const;
   };
}

#endif

// vim: sw=3 : sts=3 : et : sta : 
