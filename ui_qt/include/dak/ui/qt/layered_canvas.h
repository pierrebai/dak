#pragma once

#ifndef DAK_UI_QT_MOSAIC_CANVAS_H
#define DAK_UI_QT_MOSAIC_CANVAS_H

#include <dak/ui/qt/drawing_canvas.h>

#include <dak/ui/layered.h>

namespace dak::ui::qt
{
   ////////////////////////////////////////////////////////////////////////////
   //
   // A widget canvas working with a layers container.

   class layered_canvas_t : public drawing_canvas_t
   {
   public:
      // This is the layered container to draw on the canvas.
      ui::layered_t* layered = nullptr;

      // Create a canvas with the given parent widget.
      layered_canvas_t(QWidget* parent);

   protected:
      // This will draw the layered container, if any, then the transformer drawings, if any.
      void draw(drawing_t& drw) override;
   };
}

#endif

// vim: sw=3 : sts=3 : et : sta : 
