#include <dak/ui/qt/layered_canvas.h>

#include <QtGui/qpainter.h>

namespace dak::ui::qt
{
   ////////////////////////////////////////////////////////////////////////////
   //
   // A widget drawing_canvas working with a layered.

   layered_canvas_t::layered_canvas_t(QWidget* parent)
   : drawing_canvas_t(parent)
   , layered(nullptr)
   {
   }

   void layered_canvas_t::draw(drawing_t& drw)
   {
      draw_layered(drw, layered);
      drawing_canvas_t::draw(drw);
   }
}

// vim: sw=3 : sts=3 : et : sta : 
