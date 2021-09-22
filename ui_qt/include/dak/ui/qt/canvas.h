#pragma once

#ifndef DAK_UI_QT_TRANSFORMABLE_CANVAS_H
#define DAK_UI_QT_TRANSFORMABLE_CANVAS_H

#include <dak/ui/qt/widget_mouse_emitter.h>

#include <dak/ui/transformer.h>

#include <QtWidgets/qwidget>

namespace dak::ui::qt
{
   ////////////////////////////////////////////////////////////////////////////
   //
   // A QWidget that uses a widget mouse emitter as a source of mouse inputs
   // and feeds them to a transformer so that it can move a transformable.
   // 
   // The transformable object is provided by a sub-class and is kept in the
   // transformer.

   class canvas_t : public QWidget
   {
   public:
      // This will allow changing the transform of the drawing.
      dak::ui::transformer_t transformer;

      // Create a canvas with the given parent widget and transformable object.
      canvas_t(QWidget* parent);
      canvas_t(QWidget* parent, ui::transformable_t& trfable);

   protected:
      // This will draw the transformer drawings, if any.
      void paintEvent(QPaintEvent * pe) override;

      // Time-out to erase transformer drawings.
      void timerEvent(QTimerEvent* te) override;

      // Setup to trigger a repaint for the transformer.
      void paint_transformer();

      // This gets called by the paint event to do the painting.
      // Sub-class should override this and call this implementation last.
      virtual void paint(QPainter& painter);

      // This will allow receiving mouse event from the canvas.
      dak::ui::qt::widget_emitter_t emi;

      // Timer used to redraw after transformer drew somthing,
      // to erase it after a time-out.
      int redraw_timer = 0;
   };
}

#endif

// vim: sw=3 : sts=3 : et : sta : 
