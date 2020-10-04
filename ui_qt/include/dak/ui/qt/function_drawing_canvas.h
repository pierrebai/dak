#pragma once

#ifndef DAK_UI_QT_FUNCTION_DRAWING_CANVAS_H
#define DAK_UI_QT_FUNCTION_DRAWING_CANVAS_H

#include <dak/ui/qt/drawing_canvas.h>

#include <dak/ui/qt/painter_transformable.h>

#include <functional>

namespace dak::ui::qt
{

   ////////////////////////////////////////////////////////////////////////////
   //
   // A widget canvas working with a transformable painter drawing.

   class function_drawing_canvas_t : public drawing_canvas_t
   {
   public:
      using draw_func_t = std::function<void(drawing_t& drw)>;

      // Create a canvas with the given parent widget and draw function.
      function_drawing_canvas_t(QWidget* parent, draw_func_t a_func)
         : drawing_canvas_t(parent), my_func(a_func) {}

   protected:
      // Paint using the prepared drawing by calling the function.
      void draw(drawing_t& drw) override
      {
         if (!my_func)
            return;

         my_func(drw);
      }

      draw_func_t my_func;
   };
}

#endif

// vim: sw=3 : sts=3 : et : sta : 
