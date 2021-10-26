#include <dak/geometry/polygon.h>
#include <dak/geometry/point.h>
#include <dak/geometry/transform.h>
#include <dak/geometry/utility.h>
#include <dak/geometry/constants.h>
#include <dak/geometry/face.h>
#include <dak/geometry/intersect.h>

#include <algorithm>
#include <numeric>

namespace dak::geometry
{
   polygon_t::polygon_t(const std::vector<point_t>& pts, int start, int end)
      : points(pts)
   {
      if (end > 0)
         points.erase(pts.begin() + end, pts.end());
      if (start > 0)
         points.erase(pts.begin(), pts.begin() + start);
   }

   polygon_t polygon_t::make_regular(int n)
   {
      polygon_t p;
      p.points.reserve(n);

      for (int i = 0; i < n; ++i)
      {
         const double angle = (PI / n) * (2 * i + 1);
         const double sc = 1.0 / std::cos(PI / n);
         p.points.emplace_back(sc * std::cos(angle), sc * std::sin(angle));
      }

      return p;
   }

   polygon_t polygon_t::apply(const transform_t& T) const
   {
      polygon_t copy(*this);
      for (auto& pt : copy.points)
         pt = pt.apply(T);
      return copy;
   }

   point_t polygon_t::center() const
   {
      return dak::geometry::center(points);
   }

   double polygon_t::perimeter(bool closed) const
   {
      if (points.size() < 2)
         return 0.0;

      double len = 0.0;
      for (size_t idx = 0; idx < points.size() - 1; ++idx) {
         len += points[idx].distance(points[idx + 1]);
      }

      if (closed) {
         len += points[0].distance(points.back());
      }

      return len;
   }

   double polygon_t::raw_double_area() const
   {
      double total = 0.0;

      const size_t size = points.size();
      for (size_t idx = 0; idx < size; ++idx) {
         total += (points[idx].x * points[(idx + 1) % size].y) -
            (points[idx].y * points[(idx + 1) % size].x);
      }

      return total;
   }

   double polygon_t::area() const
   {
      return std::abs(raw_double_area()) * 0.5;
   }

   rectangle_t polygon_t::bounds() const
   {
      if (points.size() <= 0)
         return rectangle_t();

      point_t min_pt = points.front();
      point_t max_pt = points.front();
      for (const auto& pt : points)
      {
         if (pt.x < min_pt.x)
            min_pt.x = pt.x;
         if (pt.x > max_pt.x)
            max_pt.x = pt.x;
         if (pt.y < min_pt.y)
            min_pt.y = pt.y;
         if (pt.y > max_pt.y)
            max_pt.y = pt.y;
      }
      return rectangle_t(min_pt, max_pt);
   }

   bool polygon_t::is_inside(const point_t& apt) const
   {
      size_t size = points.size();
      bool outside = false;

      double x = apt.x;
      double y = apt.y;

      point_t a = points[0];
      double ax = a.x;
      double ay = a.y;

      double xmin = 0.0;
      double ymin = 0.0;
      double xmax = 0.0;
      double ymax = 0.0;

      for (size_t idx = 0; idx < size; ++idx)
      {
         const point_t b = points[(idx + 1) % size];

         const double bx = b.x;
         const double by = b.y;

         if (ax < bx)
         {
            xmin = ax;
            ymin = ay;
            xmax = bx;
            ymax = by;
         }
         else
         {
            xmin = bx;
            ymin = by;
            xmax = ax;
            ymax = ay;
         }

         // Does it straddle?
         if ((xmin <= x) && (x < xmax))
         {
            // Is the intersection point north?
            if ((x - xmin) * (ymax - ymin) > (y - ymin) * (xmax - xmin))
            {
               outside = !outside;
            }
         }

         a = b;
         ax = bx;
         ay = by;
      }

      return outside;
   }

   bool polygon_t::is_clockwise() const
   {
      return (raw_double_area() > 0.);
   }

   polygon_t& polygon_t::make_clockwise()
   {
      if (!is_clockwise())
         std::reverse(points.begin(), points.end());
      return *this;
   }

   bool polygon_t::is_regular() const
   {
      // With two or less points, they're ganranteed to be regular.
      // Besides, the rest of the algorithm needs at least two points.
      if (points.size() <= 2)
         return true;

      // A regular polygon has points evenly spaced and
      // at a constant distance around from its center.
      //
      // Evenly spaced points have roughly equal sweep
      // angles from the center.

      const point_t poly_center = center();

      const double dist2 = poly_center.distance_2(points[0]);
      const bool equidistant = std::equal(points.begin(), std::prev(points.end()), std::next(points.begin()), [poly_center, dist2](const point_t& a, const point_t& b) {
         return utility::near(poly_center.distance_2(b), dist2);
      });
      if (!equidistant)
         return false;

      const double angle = poly_center.sweep(points.back(), points.front());
      const bool equiangled = std::equal(points.begin(), std::prev(points.end()), std::next(points.begin()), [poly_center, angle](const point_t& a, const point_t& b) {
         return utility::near(poly_center.sweep(a, b), angle);
      });
      if (!equiangled)
         return false;

      return true;
   }

   bool polygon_t::intersects(const polygon_t& other) const
   {
      if (is_invalid() || other.is_invalid())
         return false;

      point_t prev = points.back();
      for (const point_t& pt : points)
      {
         if (other.is_inside(pt))
            return true;

         point_t other_prev = other.points.back();
         for (const point_t& other_pt : other.points)
         {
            if (is_inside(other_pt))
               return true;

            if (!geometry::intersect::intersect(prev, pt, other_prev, other_pt).is_invalid())
               return true;

            other_prev = other_pt;
         }
         prev = pt;
      }
      return false;
   }
}

// vim: sw=3 : sts=3 : et : sta : 

