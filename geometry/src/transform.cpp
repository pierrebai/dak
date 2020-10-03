#include <dak/geometry/transform.h>

namespace dak::geometry
{
   const transform_t transform_t::invalid;

   transform_t transform_t::rotate(double t)
   {
      return transform_t(
         std::cos(t), -std::sin(t), 0,
         std::sin(t), std::cos(t), 0);
   }

   transform_t transform_t::rotate(const point_t& pt, double t)
   {
      return translate(pt).compose(
         rotate(t).compose(
            translate(-pt.x, -pt.y)));
   }

   double transform_t::dist_from_zero(double v) const
   {
      return point_t(v, 0.0).apply(*this).distance(point_t::origin().apply(*this));
   }

   double transform_t::dist_from_inverted_zero(double v) const
   {
      return invert().dist_from_zero(v);
   }
}

// vim: sw=3 : sts=3 : et : sta : 
