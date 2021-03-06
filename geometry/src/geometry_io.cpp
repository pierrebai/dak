#include <dak/geometry/geometry_io.h>

#include <dak/geometry/point.h>
#include <dak/geometry/face.h>
#include <dak/geometry/edge.h>
#include <dak/geometry/polygon.h>
#include <dak/geometry/rectangle.h>
#include <dak/geometry/transform.h>

namespace dak::geometry
{
   std::wostream& operator <<(std::wostream& ostr, const point_t& point)
   {
      ostr << point.x << L" " << point.y;
      return ostr;
   }

   std::wostream& operator <<(std::wostream& ostr, const edge_t& edge)
   {
      ostr << edge.p1 << L" " << edge.p2;
      return ostr;
   }

   std::wostream& operator <<(std::wostream& ostr, const polygon_t& polygon)
   {
      ostr << polygon.points.size();
      for (const auto& pt : polygon.points)
         ostr << L" " << pt;
      return ostr;
   }

   std::wostream& operator <<(std::wostream& ostr, const rectangle_t& rect)
   {
      ostr << rect.x << L" " << rect.y << L" " << rect.width << L" " << rect.height;
      return ostr;
   }

   std::wostream& operator <<(std::wostream& ostr, const transform_t& trf)
   {
      ostr << trf.scale_x << L" " << trf.rot_1 << L" " << trf.trans_x << L" " << trf.rot_2 << L" " << trf.scale_y << L" " << trf.trans_y;
      return ostr;
   }

   std::wistream& operator >>(std::wistream& istr, point_t& point)
   {
      istr >> point.x >> point.y;
      return istr;
   }

   std::wistream& operator >>(std::wistream& istr, edge_t& edge)
   {
      istr >> edge.p1 >> edge.p2;
      return istr;
   }

   std::wistream& operator >>(std::wistream& istr, polygon_t& polygon)
   {
      size_t count = 0;
      istr >> count;
      for (size_t i = 0; i < count; ++i)
      {
         point_t pt;
         istr >> pt;
         polygon.points.emplace_back(pt);
      }
      return istr;
   }

   std::wistream& operator >>(std::wistream& istr, rectangle_t& rect)
   {
      istr >> rect.x >> rect.y >> rect.width >> rect.height;
      return istr;
   }

   std::wistream& operator >>(std::wistream& istr, transform_t& trf)
   {
      istr >> trf.scale_x >> trf.rot_1 >> trf.trans_x >> trf.rot_2 >> trf.scale_y >> trf.trans_y;
      return istr;
   }
}

// vim: sw=3 : sts=3 : et : sta : 

