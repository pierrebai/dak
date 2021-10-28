#include <dak/ui/qt/layered_canvas.h>

#include <QtGui/qpainter.h>

namespace dak::ui::qt
{
   ////////////////////////////////////////////////////////////////////////////
   //
   // A widget drawing_canvas working with a layered.

   layered_canvas_t::layered_canvas_t(QWidget* parent)
   : drawing_canvas_t(parent)
   {
      transformer.manipulated = this;
   }

   void layered_canvas_t::draw(drawing_t& drw)
   {
      drw.push_transform();
      drw.compose(my_trf);

      draw_layered(drw, layered);
      drawing_canvas_t::draw(drw);

      drw.pop_transform();
   }

   const transform_t& layered_canvas_t::get_transform() const
   {
      if (!layered || layered->are_all_moving() || layered->are_not_moving())
         return my_trf;
      else
         return layered->get_transform();
   }

   layered_canvas_t& layered_canvas_t::set_transform(const transform_t& t)
   {
      if (!layered || layered->are_all_moving() || layered->are_not_moving())
         my_trf = t;
      else
         layered->set_transform(t);
      return *this;
   }

   layered_canvas_t& layered_canvas_t::compose(const transform_t& t)
   {
      if (!layered || layered->are_all_moving() || layered->are_not_moving())
         my_trf = my_trf.compose(t);
      else
         layered->compose(t);
      return *this;
   }
}

// vim: sw=3 : sts=3 : et : sta : 
