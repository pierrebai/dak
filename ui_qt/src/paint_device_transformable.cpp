#include <dak/ui/qt/paint_device_transformable.h>

namespace dak::ui::qt
{
   const transform_t& paint_device_transformable_t::get_transform() const
   {
      return paint_device_drawing_t::get_transform();
   }

   paint_device_transformable_t& paint_device_transformable_t::set_transform(const transform_t& t)
   {
      paint_device_drawing_t::set_transform(t);
      return *this;
   }

   paint_device_transformable_t& paint_device_transformable_t::compose(const transform_t& t)
   {
      paint_device_drawing_t::compose(t);
      return *this;
   }
}

// vim: sw=3 : sts=3 : et : sta : 
