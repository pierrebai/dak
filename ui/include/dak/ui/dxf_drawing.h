#pragma once

#ifndef DAK_UI_DXF_DRAWING_H
#define DAK_UI_DXF_DRAWING_H

#include <dak/ui/drawing_base.h>

#include <ostream>
#include <sstream>

namespace dak::ui
{
   ////////////////////////////////////////////////////////////////////////////
   //
   // Drawing into an AutoCAD format (DXF).

   class dxf_drawing_t : public drawing_base_t
   {
   public:
      enum drawing_with_t
      {
         with_polygons, with_faces
      };

      dxf_drawing_t(std::wostream& out, drawing_with_t drawing_with);

      // Finish writing the file if not already done.
      ~dxf_drawing_t() override;

      // Finish writing the file.
      void finish();

      // drawing interface implementation.
      drawing_t& draw_line(const point_t& from, const point_t& to) override;
      drawing_t& draw_corner(const point_t& from, const point_t& mid, const point_t& to) override;
      drawing_t& fill_polygon(const polygon_t& p) override;
      drawing_t& draw_polygon(const polygon_t& p) override;
      drawing_t& fill_oval(const point_t& c, double rx, double ry) override;
      drawing_t& draw_oval(const point_t& c, double rx, double ry) override;
      drawing_t& fill_arc(const point_t& c, double rx, double ry, double angle1, double angle2) override;
      drawing_t& fill_rect(const rectangle_t& r) override;
      drawing_t& draw_rect(const rectangle_t& r) override;

      // Note: the bounds are *without* the transform.
      //       They are the true bounds of the drawing surface.
      rectangle_t get_bounds() const override;

   private:
      void internal_update_color();
      void internal_update_stroke();
      void internal_update_transform();

      void internal_update_bbox(const std::vector<point_t>& pts);
      void internal_update_bbox(const point_t& p);

      std::wostream& out;

      drawing_with_t drawing_with;

      color_t applied_co = color_t::black();
      stroke_t applied_strk = stroke_t(1);
      transform_t applied_trf = transform_t::identity();
      rectangle_t bbox;

      std::vector<polygon_t> polygons;
   };
}

#endif

// vim: sw=3 : sts=3 : et : sta : 
