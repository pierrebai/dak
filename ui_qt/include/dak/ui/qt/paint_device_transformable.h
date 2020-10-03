#pragma once

#ifndef DAK_UI_QT_PAINT_DEVICE_TRANSFORMABLE_H
#define DAK_UI_QT_PAINT_DEVICE_TRANSFORMABLE_H

#include <dak/ui/qt/paint_device_drawing.h>

#include <dak/ui/transformable.h>

namespace dak::ui::qt
{
   using geometry::point_t;
   using geometry::transform_t;

   ////////////////////////////////////////////////////////////////////////////
   //
   // Enable editing the transform of a QPaintDevice.

   class paint_device_transformable_t : public paint_device_drawing_t, public ui::transformable_t
   {
   public:
      // Create a transformable QT paint device.
      paint_device_transformable_t(QPaintDevice& pd) : paint_device_drawing_t(pd) { }

      // ui::transformable implementation.
      const transform_t& get_transform() const override;
      paint_device_transformable_t& set_transform(const transform_t& t) override;
      paint_device_transformable_t& compose(const transform_t& t) override;
   };
}

#endif

// vim: sw=3 : sts=3 : et : sta : 
