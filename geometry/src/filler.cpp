#include <dak/geometry/utility.h>
#include <dak/geometry/rectangle.h>
#include <dak/geometry/polygon.h>

#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>

namespace dak::geometry
{
   size_t count_fill_replications(const rectangle_t& region, const point_t& T1, const point_t& T2)
   {
      const transform_t basis_change = transform_t::to_basis(T1, T2);
      const polygon_t region_in_t1_t2(polygon_t::from_rect(region).apply(basis_change));

      point_t minimums(1.0e100, 1.0e100);
      point_t maximums(-1.0e100, -1.0e100);
      for (const auto& pt : region_in_t1_t2.points)
      {
         minimums.x = std::min(minimums.x, pt.x);
         minimums.y = std::min(minimums.y, pt.y);
         maximums.x = std::max(maximums.x, pt.x);
         maximums.y = std::max(maximums.y, pt.y);
      }

      // Note: since the tiling base are irregularly shaped,
      //       we need to acount for it by adding another outer band.
      const int from_x = int(std::floor(minimums.x)) - 1;
      const int to_x = int(std::ceil(maximums.x)) + 1;
      const int from_y = int(std::floor(minimums.y)) - 1;
      const int to_y = int(std::ceil(maximums.y)) + 1;

      return (1 + to_x - from_x) * (1 + to_y - from_y);
   }

   void fill(const rectangle_t& region, const point_t& T1, const point_t& T2, std::function<void(int, int)> fill_callback)
   {
      const transform_t basis_change = transform_t::to_basis(T1, T2);
      const polygon_t region_in_t1_t2(polygon_t::from_rect(region).apply(basis_change));

      point_t minimums(1.0e100, 1.0e100);
      point_t maximums(-1.0e100, -1.0e100);
      for (const auto& pt : region_in_t1_t2.points)
      {
         minimums.x = std::min(minimums.x, pt.x);
         minimums.y = std::min(minimums.y, pt.y);
         maximums.x = std::max(maximums.x, pt.x);
         maximums.y = std::max(maximums.y, pt.y);
      }

      // Note: since the tiling base are irregularly shaped,
      //       we need to acount for it by adding another outer band.
      const int from_x = int(std::floor(minimums.x)) - 1;
      const int to_x   = int(std::ceil(maximums.x))  + 1;
      const int from_y = int(std::floor(minimums.y)) - 1;
      const int to_y   = int(std::ceil(maximums.y))  + 1;

      for (int x = from_x; x <= to_x; ++x)
      {
         for (int y = from_y; y <= to_y; ++y)
         {
            // Note: we increase the size of the tile to account
            //       for the irregular shape of the tiling base tiles.
            const polygon_t tile(
            {
               point_t(x - 0.5, y - 0.5), point_t(x + 1.5, y - 0.5),
               point_t(x + 1.5, y + 1.5), point_t(x - 0.5, y + 1.5)
            });

            if (region_in_t1_t2.intersects(tile))
               fill_callback(x, y);
         }
      }
   }
}

// vim: sw=3 : sts=3 : et : sta : 

