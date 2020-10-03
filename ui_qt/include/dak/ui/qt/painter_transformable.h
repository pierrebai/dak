#pragma once

#ifndef DAK_UI_QT_PAINTER_TRANSFORMABLE_H
#define DAK_UI_QT_PAINTER_TRANSFORMABLE_H

#include <dak/ui/qt/painter_drawing.h>

#include <dak/ui/transformable.h>

namespace dak::ui::qt
{
   using geometry::point_t;
   using geometry::transform_t;

   ////////////////////////////////////////////////////////////////////////////
   //
   // Enable editing the transform of a QPainter.

   class painter_transformable : public painter_drawing_t, public transformable_t
   {
   public:
      // Empty transformable.
      painter_transformable() : painter_drawing_t() { }

      // Transformable for the given QPainter.
      painter_transformable(QPainter& p) : painter_drawing_t(p) { }

      // ui::transformable implementation.
      const transform_t& get_transform() const override;
      painter_transformable& set_transform(const transform_t& t) override;
      painter_transformable& compose(const transform_t& t) override;
   };
}

#endif

// vim: sw=3 : sts=3 : et : sta : 
