#include <dak/geometry/utility.h>
#include <dak/geometry/transform.h>

#include <algorithm>

namespace dak::geometry
{
   bool near_zero(const point_t& a, double tolerance)
   {
      return a.mag_2() <= tolerance;
   }

   bool near_zero(const point_t& a)
   {
      return near_zero(a, TOLERANCE_2);
   }

   bool near(const point_t& a, const point_t& b, double tolerance)
   {
      return a.distance_2(b) <= tolerance;
   }

   bool near(const point_t& a, const point_t& b)
   {
      return near(a, b, TOLERANCE_2);
   }

   point_t center(const point_t* begin, const point_t* end)
   {
      point_t cent = point_t(0.0, 0.0);
      const auto count = end - begin;
      while (begin != end)
         cent = cent + *begin++;
      return cent.scale(1.0 / (double) count);
   }

   point_t center(const std::vector<point_t>& pts)
   {
      if (pts.size() <= 0)
         return point_t();
      return center(&*pts.begin(), (&*pts.begin()) + pts.size());
   }

   std::vector<point_t> translate(const std::vector<point_t>& pts, const point_t& move)
   {
      std::vector<point_t> new_pts;
      new_pts.reserve(pts.size());
      for (const auto& pt : pts)
         new_pts.emplace_back(pt + move);
      return new_pts;
   }

   std::vector<point_t> apply(const transform_t& t, const std::vector<point_t>& pts)
   {
      std::vector<point_t> new_pts;
      new_pts.reserve(pts.size());
      for (const auto& pt : pts)
         new_pts.emplace_back(pt.apply(t));
      return new_pts;
   }

   point_t get_arc(double frac)
   {
      const double ang = frac * 2 * PI;
      return point_t(std::cos(ang), std::sin(ang));
   }
}

// vim: sw=3 : sts=3 : et : sta : 

