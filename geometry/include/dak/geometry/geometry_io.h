#pragma once

#ifndef DAK_GEOMETRY_IO_H
#define DAK_GEOMETRY_IO_H

#include <iostream>

namespace dak::geometry
{
   class point_t;
   class edge_t;
   class polygon_t;
   class rectangle_t;
   class transform_t;

   std::wostream& operator <<(std::wostream&, const point_t&);
   std::wostream& operator <<(std::wostream&, const edge_t&);
   std::wostream& operator <<(std::wostream&, const polygon_t&);
   std::wostream& operator <<(std::wostream&, const rectangle_t&);
   std::wostream& operator <<(std::wostream&, const transform_t&);

   std::wistream& operator >>(std::wistream&, point_t&);
   std::wistream& operator >>(std::wistream&, edge_t&);
   std::wistream& operator >>(std::wistream&, polygon_t&);
   std::wistream& operator >>(std::wistream&, rectangle_t&);
   std::wistream& operator >>(std::wistream&, transform_t&);
}

#endif

// vim: sw=3 : sts=3 : et : sta : 

