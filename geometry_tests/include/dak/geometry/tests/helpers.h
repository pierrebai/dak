#include <dak/geometry/polygon.h>
#include <dak/geometry/point.h>
#include <dak/geometry/edge.h>
#include <dak/geometry/face.h>
#include <dak/geometry/rectangle.h>
#include <dak/geometry/transform.h>

#include "CppUnitTest.h"

namespace Microsoft::VisualStudio::CppUnitTestFramework
{
   template<> inline std::wstring ToString<dak::geometry::point_t>(const dak::geometry::point_t& p)
   {
      std::wstringstream _s;
      _s << p.x << L"/" << p.y;
      return _s.str();
   }

   template<> inline std::wstring ToString<dak::geometry::transform_t>(const dak::geometry::transform_t& t)
   {
      std::wstringstream _s;
      _s << "x" << t.scale_x << L"/" << t.scale_y << L" @ " << t.rot_1 << L"/" << t.rot_2 << L" move " << t.trans_x << L"/" << t.trans_y;
      return _s.str();
   }

   template<> inline std::wstring ToString<dak::geometry::edge_t>(const dak::geometry::edge_t& e)
   {
      std::wstringstream _s;
      _s << e.p1.x << L"/" << e.p1.y << L" - " << e.p2.x << L"/" << e.p2.y;
      return _s.str();
   }

   template<> inline std::wstring ToString<dak::geometry::rectangle_t>(const dak::geometry::rectangle_t& r)
   {
      std::wstringstream _s;
      _s << r.x << L"/" << r.y << L" - " << r.width << L"x" << r.height;
      return _s.str();
   }

   template<> inline std::wstring ToString<dak::geometry::polygon_t>(const dak::geometry::polygon_t& poly)
   {
      std::wstringstream _s;
      for (const auto& p : poly.points)
      {
         _s << p.x << L"/" << p.y << L" - ";
      }
      return _s.str();
   }

}
