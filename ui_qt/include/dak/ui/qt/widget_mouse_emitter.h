#pragma once

#ifndef DAK_UI_QT_WIDGET_EMITTER_H
#define DAK_UI_QT_WIDGET_EMITTER_H

#include <dak/ui/mouse.h>

#include <QtWidgets/qwidget.h>

namespace dak::ui::qt
{
   using dak::geometry::point_t;
   using dak::ui::modifiers_t;
   using dak::ui::mouse::buttons_t;

   ////////////////////////////////////////////////////////////////////////////
   //
   // Generator of mouse events for a QWidget.

   class widget_emitter_t : public mouse::emitter_t, public QObject
   {
   public:
      // Widget that will give the events
      QWidget& widget;

      // Create the emitter on the given widget.
      // An event filter will be placed on the widget.
      widget_emitter_t(QWidget& w);

      // Destructor.
      // The event filter will be removed from the widget.
      ~widget_emitter_t();

   protected:
      bool eventFilter(QObject* obj, QEvent* ev) override;
   };
}

#endif

// vim: sw=3 : sts=3 : et : sta : 
