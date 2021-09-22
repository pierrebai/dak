#pragma once

#ifndef DAK_UI_QT_DRAWING_CANVAS_H
#define DAK_UI_QT_DRAWING_CANVAS_H

#include <dak/ui/qt/canvas.h>

#include <dak/ui/qt/painter_transformable.h>

namespace dak::ui::qt
{

   ////////////////////////////////////////////////////////////////////////////
   //
   // A canvas widget (that is using mouse input to play with a transformable)
   // that knows of to convert Qt paint event into a draw() call that receives
   // a drawing (that is an abtract drawing interface).
   //
   // It uses a painter drawing to bridges between the drawing interface and
   // QPainter and also be the transformable. That is the drawing/painting is
   // the thing being moved around.

   class drawing_canvas_t : public canvas_t
   {
   public:
      // Create a canvas with the given parent widget.
      drawing_canvas_t(QWidget* parent);
      drawing_canvas_t(QWidget* parent, ui::transformable_t& trfable);

   protected:
      // This will call draw, then the transformer drawings, if any.
      void paint(QPainter& painter) override;

      // Paint using the prepared drawing.
      // Sub-class should override this to draw in the canvas.
      virtual void draw(drawing_t& drw) = 0;

      // This will allow painting using a drawing.
      dak::ui::qt::painter_transformable painter_trf_drawing;
   };
}

#endif

// vim: sw=3 : sts=3 : et : sta : 
