#include <dak/geometry/rectangle.h>
#include <dak/geometry/transform.h>

#include <algorithm>

namespace dak::geometry
{
   rectangle_t rectangle_t::apply(const transform_t& trf) const
   {
      rectangle_t applied(top_left().apply(trf), bottom_right().apply(trf));
      applied = applied.combine(top_right().apply(trf));
      applied = applied.combine(bottom_left().apply(trf));
      return applied;
   }

   rectangle_t rectangle_t::combine(const rectangle_t& other) const
   {
      const double min_x = std::min(x, other.x);
      const double min_y = std::min(y, other.y);
      const double max_x = std::max(x + width, other.x + other.width);
      const double max_y = std::max(y + height, other.y + other.height);

      return rectangle_t(min_x, min_y, max_x - min_x, max_y - min_y);
   }

   rectangle_t rectangle_t::combine(const point_t& pt) const
   {
      const double min_x = std::min(x, pt.x);
      const double min_y = std::min(y, pt.y);
      const double max_x = std::max(x + width, pt.x);
      const double max_y = std::max(y + height, pt.y);

      return rectangle_t(min_x, min_y, max_x - min_x, max_y - min_y);
   }

   rectangle_t rectangle_t::intersect(const rectangle_t& other) const
   {
      const double min_x = std::max(x, other.x);
      const double min_y = std::max(y, other.y);
      const double max_x = std::min(x + width, other.x + other.width);
      const double max_y = std::min(y + height, other.y + other.height);

      if (max_x < min_x || max_y < min_y) {
         return rectangle_t();
      }
      else {
         return rectangle_t(min_x, min_y, max_x - min_x, max_y - min_y);
      }
   }

   rectangle_t rectangle_t::central_scale(double s) const
   {
      double cx = x + width * 0.5;
      double cy = y + height * 0.5;

      double nw = width * s;
      double nh = height * s;

      return rectangle_t(cx - nw * 0.5, cy - nh * 0.5, nw, nh);
   }

   transform_t rectangle_t::center_inside(const rectangle_t& other)
   {
      double xscale = other.width / width;
      double yscale = other.height / height;

      double scale = std::min(xscale, yscale);

      transform_t Ts = transform_t::scale(scale, scale);

      const point_t my_center = point_t(x + (width / 2.0), y + (height / 2.0));
      const point_t your_center = point_t(other.x + (other.width / 2.0), other.y + (other.height / 2.0));

      return transform_t::translate(your_center).compose(Ts).compose(
         transform_t::translate(my_center.scale(-1.0)));
   }
}

// vim: sw=3 : sts=3 : et : sta : 
