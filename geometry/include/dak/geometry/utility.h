#pragma once

#ifndef DAK_GEOMETRY_UTILITY_H
#define DAK_GEOMETRY_UTILITY_H

#include <dak/utility/number.h>

#include <dak/geometry/constants.h>
#include <dak/geometry/point.h>

#include <vector>
#include <functional>

namespace dak::geometry
{
   class transform_t;
   class rectangle_t;

   ////////////////////////////////////////////////////////////////////////////
   //
   // Point functions.

   // Verify if the point is near the origin for the given tolerance.
   bool near_zero(const point_t& a, double tolerance);

   // Verify if the point is near the origin for the default tolerance.
   bool near_zero(const point_t& a);

   // Verify if the two points are near for the given tolerance.
   bool near(const point_t& a, const point_t& b, double tolerance);

   // Verify if the two points are near for the default tolerance.
   bool near(const point_t& a, const point_t& b);

   // Verify if three points are co-linear.
   inline bool is_colinear(const point_t& p, const point_t& q, const point_t& a)
   {
      double px = p.x;
      double py = p.y;

      double qx = q.x;
      double qy = q.y;

      double x = a.x;
      double y = a.y;

      double left = (qx - px) * (y - py);
      double right = (qy - py) * (x - px);

      return utility::near(left, right);
   }

   ////////////////////////////////////////////////////////////////////////////
   //
   // Point calculation functions.

   // Calculate the center of all the given points.
   point_t center(const point_t* begin, const point_t* end);

   // Calculate the center of all the given points.
   point_t center(const std::vector<point_t>& pts);

   // Translate all the given points by the given amount.
   std::vector<point_t> translate(const std::vector<point_t>& pts, const point_t& move);

   // Apply the transform to all the points.
   std::vector<point_t> apply(const transform_t& t, const std::vector<point_t>& pts);

   // Get the point frac of the way around the unit circle.
   point_t get_arc(double frac);

   ////////////////////////////////////////////////////////////////////////////
   //
   // Fill a rectangular region with regularly spaced copies of a motif.
   // fill a rectangle regions with the integer linear combinations of two
   // translation vectors.
   //
   // To make the algorithm general, the output is provided through a 
   // callback that gets a sequence of calls, one for each translate.
   //
   // Calls the function repatedly with integer linear combinations to be applied to T1 and T2.
   size_t count_fill_replications(const rectangle_t& region, const point_t& T1, const point_t& T2);
   void fill(const rectangle_t& region, const point_t& T1, const point_t& T2, std::function<void(int, int)> c);
}

#endif

// vim: sw=3 : sts=3 : et : sta : 

