#pragma once

#ifndef DAK_GEOMETRY_INTERSECT_H
#define DAK_GEOMETRY_INTERSECT_H

#include <dak/geometry/point.h>

namespace dak::geometry::intersect
{
   ////////////////////////////////////////////////////////////////////////////
   //
   // Some routines for testing line segment intersections.

   // Return a point (s,t), where s is the fraction from p1 to
   // q1 where an intersection occurs.  t is defined similarly for p2 and q2.
   // If there's no intersection, return an invalid point.
   point_t get_intersection_params(const point_t& p1, const point_t& q1, const point_t& p2, const point_t& q2);

   // Coerce the point to be invalid if not on both unit segments.
   const point_t& stay_on_units(const point_t& ip);

   // Coerce the point to be invalid if too far off both unit segments.
   static constexpr double near_limit = 0.2;
   const point_t& stay_near_units(const point_t& ip);

   // Get the position of the intersection by interpolating.
   // Returns invalid if parallel or if it ends up outside of the segments.
   point_t intersect(const point_t& p1, const point_t& q1, const point_t& p2, const point_t& q2);

   // Get the position of the intersection by interpolating.
   // Returns invalid if parallel or if the point is too far off.
   point_t intersect_near(const point_t& p1, const point_t& q1, const point_t& p2, const point_t& q2);

   // Get the position of the intersection by interpolating, even outside the segments.
   // Returns invalid if parallel.
   point_t intersect_anywhere(const point_t& p1, const point_t& q1, const point_t& p2, const point_t& q2);

   // Don't return the intersection if it is at the enpoints of both segments.
   point_t intersect_within(const point_t& p1, const point_t& q1, const point_t& p2, const point_t& q2);
}

#endif

// vim: sw=3 : sts=3 : et : sta : 
