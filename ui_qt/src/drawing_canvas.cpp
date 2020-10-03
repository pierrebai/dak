#include <dak/ui/qt/drawing_canvas.h>

namespace dak::ui::qt
{
   ////////////////////////////////////////////////////////////////////////////
   //
   // A widget canvas working with a transformable drawing.

   drawing_canvas_t::drawing_canvas_t(QWidget* parent)
   : drawing_canvas_t(parent, painter_trf_drawing)
   {
   }

   drawing_canvas_t::drawing_canvas_t(QWidget* parent, ui::transformable_t& trfable)
   : canvas_t(parent, trfable)
   {
      transformer.manipulated = &trfable;
   }

   void drawing_canvas_t::paint(QPainter& painter)
   {
      painter_trf_drawing.painter = &painter;
      draw(painter_trf_drawing);
      painter_trf_drawing.painter = nullptr;

      canvas_t::paint(painter);
   }

   void drawing_canvas_t::draw(drawing_t&)
   {
      // Nothing.
   }
}

// vim: sw=3 : sts=3 : et : sta : 
