#include <dak/geometry/point.h>
#include <dak/geometry/constants.h>
#include <dak/geometry/transform.h>

namespace dak::geometry
{
   const point_t point_t::invalid;

   double point_t::mag() const
   {
      return std::sqrt(mag_2());
   }

   double point_t::distance(const point_t& other) const
   {
      return std::sqrt(distance_2(other));
   }

   point_t point_t::normalize() const
   {
      double m = mag();
      if (m != 0.0)
         return scale(1.0 / m);
      else
         return *this;
   }

   point_t point_t::convex_sum(const point_t& other, double t) const
   {
      double mt = 1.0 - t;
      return point_t(mt * x + t * other.x, mt * y + t * other.y);
   }

   // Return the absolute angle of the edge from this to other, in the
   // range -PI to PI.
   double point_t::angle(const point_t& other) const
   {
      return std::atan2(other.y - y, other.x - x);
   }

   // Angle wrt the origin.
   double point_t::angle() const
   {
      return std::atan2(y, x);
   }

   // Get the section of arc swept out between the edges this ==> from
   // and this ==> to.
   double point_t::sweep(const point_t& from, const point_t& to) const
   {
      double res = angle(to) - angle(from);

      while (res < 0.0)
         res += 2.0 * PI;

      return res;
   }

   double point_t::distance_to_line(const point_t& p, const point_t& q) const
   {
      return std::sqrt(distance_2_to_line(p, q));
   }

   double point_t::distance_2_to_line(point_t p, const point_t& q) const
   {
      const point_t qmp = q - p;
      const double t = (*this - p).dot(qmp) / qmp.dot(qmp);
      if (t >= 0.0 && t <= 1.0)
      {
         double ox = p.x + t * (q.x - p.x);
         double oy = p.y + t * (q.y - p.y);
         return (x - ox)*(x - ox) + (y - oy)*(y - oy);
      }
      else if (t < 0.0)
      {
         return distance_2(p);
      }
      else
      {
         return distance_2(q);
      }
   }

   double point_t::parameterization_on_line(const point_t& p, const point_t& q) const
   {
      point_t qmp = q - p;
      return (*this - p).dot(qmp) / qmp.dot(qmp);
   }

   point_t point_t::apply(const transform_t& t) const
   {
      return point_t(
         t.scale_x * x + t.rot_1 * y   + t.trans_x,
         t.rot_2 * x   + t.scale_y * y + t.trans_y);
   }
}

// vim: sw=3 : sts=3 : et : sta : 

