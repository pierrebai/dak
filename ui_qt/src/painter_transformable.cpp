#include <dak/ui/qt/painter_transformable.h>

namespace dak::ui::qt
{
   const transform_t& painter_transformable::get_transform() const
   {
      return painter_drawing_t::get_transform();
   }

   painter_transformable& painter_transformable::set_transform(const transform_t& t)
   {
      painter_drawing_t::set_transform(t);
      return *this;
   }

   painter_transformable& painter_transformable::compose(const transform_t& t)
   {
      painter_drawing_t::compose(t);
      return *this;
   }
}

// vim: sw=3 : sts=3 : et : sta : 
