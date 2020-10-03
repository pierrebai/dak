#pragma once

#ifndef DAK_UI_QT_DRAWING_H
#define DAK_UI_QT_DRAWING_H

#include <dak/ui/drawing_base.h>

#include <QtGui/qpen.h>
#include <QtGui/qbrush.h>

namespace dak::ui::qt
{
   ////////////////////////////////////////////////////////////////////////////
   //
   // Drawing that can translate color, stroke, etc to QT format.

   class qt_drawing_base_t : public ui::drawing_base_t
   {
   protected:
      QPen get_pen() const;
      QBrush get_brush() const;
   };
}

#endif

// vim: sw=3 : sts=3 : et : sta : 
