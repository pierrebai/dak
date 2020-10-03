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
   // A QWidget that brings together a transformer and widget mouse emitter
   // with some transformable object to be provided by a sub-class.

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

      // This gets called by the paint event to do the painting.
      // Sub-class should override this and call this implementation last.
      virtual void paint(QPainter& painter);

      // This will allow receiving mouse event from the canvas.
      dak::ui::qt::widget_emitter_t emi;
   };
}

#endif

// vim: sw=3 : sts=3 : et : sta : 
