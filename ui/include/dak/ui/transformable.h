#pragma once

#ifndef DAK_UI_TRANSFORMABLE_H
#define DAK_UI_TRANSFORMABLE_H

#include <dak/geometry/point.h>
#include <dak/geometry/transform.h>

namespace dak::ui
{
   using geometry::point_t;
   using geometry::transform_t;

   ////////////////////////////////////////////////////////////////////////////
   //
   // Interface needed to enable transform something.
   //
   // Used by the transformer class.

   class transformable_t
   {
   public:
      virtual ~transformable_t() = 0 { }

      // Changing the transform.
      virtual const transform_t& get_transform() const = 0;
      virtual transformable_t& set_transform(const transform_t&) = 0;
      virtual transformable_t& compose(const transform_t&) = 0;
   };
}

#endif

// vim: sw=3 : sts=3 : et : sta : 
