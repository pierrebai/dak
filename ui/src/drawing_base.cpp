#include <dak/ui/drawing_base.h>

namespace dak
{
   namespace ui
   {
      stroke_t drawing_base_t::get_stroke() const
      {
         return strk;
      }

      drawing_base_t& drawing_base_t::set_stroke(const stroke_t& s)
      {
         strk = s;
         return *this;
      }

      color_t drawing_base_t::get_color() const
      {
         return co;
      }

      drawing_base_t& drawing_base_t::set_color(const color_t& c)
      {
         co = c;
         return *this;
      }

      const transform_t& drawing_base_t::get_transform() const
      {
         return trf;
      }

      drawing_base_t& drawing_base_t::set_transform(const transform_t& t)
      {
         trf = t;
         return *this;
      }

      drawing_base_t& drawing_base_t::compose(const transform_t& t)
      {
         trf = trf.compose(t);
         return *this;
      }

      drawing_base_t& drawing_base_t::push_transform()
      {
         saved_trfs.emplace_back(trf);
         return *this;
      }

      drawing_base_t& drawing_base_t::pop_transform()
      {
         if (saved_trfs.size() <= 0)
            return *this;

         trf = saved_trfs.back();
         saved_trfs.pop_back();
         return *this;
      }

      static polygon_t make_arrow(const point_t& from, const point_t& to, double length, double half_width)
      {
         const point_t dir = (to - from).normalize().scale(length);
         const point_t perp = dir.perp().normalize().scale(half_width);
         return polygon_t({ to, to - dir + perp, to - dir - perp, to });
      }

      void drawing_t::draw_arrow(const point_t& from, const point_t& to, double length, double half_width)
      {
         draw_polygon(make_arrow(from, to, length, half_width));
      }

      void drawing_t::fill_arrow(const point_t& from, const point_t& to, double length, double half_width)
      {
         fill_polygon(make_arrow(from, to, length, half_width));
      }
   }
}

// vim: sw=3 : sts=3 : et : sta : 
