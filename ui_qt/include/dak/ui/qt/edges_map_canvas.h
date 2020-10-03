#pragma once

#ifndef DAK_UI_QT_MAP_CANVAS_H
#define DAK_UI_QT_MAP_CANVAS_H

#include <dak/ui/qt/drawing_canvas.h>

#include <dak/geometry/edges_map.h>

namespace dak::ui::qt
{
   ////////////////////////////////////////////////////////////////////////////
   //
   // A widget drawing_canvas working with a map.

   class edges_map_canvas_t : public drawing_canvas_t
   {
   public:
      // This is the layered container to draw on the drawing_canvas.
      geometry::edges_map_t map;

      // Create a drawing_canvas with the given parent widget.
      edges_map_canvas_t(QWidget* parent);

      // Draw the map in the given drawing.
      void draw_map(dak::ui::drawing_t& drw) const;

   protected:
      // This will draw the map, if any, then the transformer drawings, if any.
      void paint(QPainter& painter) override;

      void draw(drawing_t& drw) override;
   };
}

#endif

// vim: sw=3 : sts=3 : et : sta : 
