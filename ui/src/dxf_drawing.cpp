#include <dak/ui/dxf_drawing.h>

#include <dak/utility/types.h>

namespace dak
{
   namespace ui
   {
      USING_DAK_UTILITY_TYPES;

      namespace dxf
      {
         //////////////////////////////////////////////////////////////////////////
         //
         // IN DXF, every entry in the file starts with a pair of numeric code and text.

         struct code_t
         {
            int32_t code;
            text_t  text;
         };

         std::wostream& operator<<(std::wostream& out, const code_t& code)
         {
            return out << code.code << L"\n" << code.text << L"\n";
         }

         //////////////////////////////////////////////////////////////////////////
         //
         // To simplify writing values, which must always be ended with a newline,
         // we wrap them in a raw type that will add the new-line automatically.

         template <class T>
         struct raw_t
         {
            raw_t(const T& v) : value(v) {}

            T value;
         };

         template <class T>
         raw_t<T> raw(const T& value)
         {
            return raw_t<T>(value);
         }

         template <class T>
         std::wostream& operator<<(std::wostream& out, const raw_t<T>& raw)
         {
            return out << raw.value<< L"\n";
         }

         //////////////////////////////////////////////////////////////////////////
         //
         // Provide well-known DXF codes and code generators.

         namespace codes
         {
            //////////////////////////////////////////////////////////////////////////
            //
            // The maker creates integer and floating-point DXF entries,
            // with automatically increasing codes.
            // 
            // Use the reset function to reset the increasing codes.

            struct maker_t
            {
               code_t make_int_code(int32_t value)
               {
                  int_code += 10;
                  return code_t(int_code, std::to_wstring(value));
               }

               code_t make_double_code(double value)
               {
                  double_code += 10;
                  return code_t(double_code, std::to_wstring(value));
               }

               const wchar_t* reset(const int32_t start_value = 0)
               {
                  int_code = start_value;
                  double_code = start_value;
                  return L"";
               }

            private:
               int32_t int_code = 0;
               int32_t double_code = 0;
            };

            //////////////////////////////////////////////////////////////////////////
            //
            // Well-known pre-defined DXF codes.

            const code_t section =           {   0, L"SECTION"     };
            const code_t end_section =       {   0, L"ENDSEC"      };
            const code_t header =            {   2, L"HEADER"      };
            const code_t tables =            {   2, L"TABLES"      };
            const code_t table =             {   0, L"TABLE"       };
            const code_t end_table =         {   0, L"ENDTAB"      };
            const code_t layer =             {   0, L"LAYER"       };
            const code_t line_type =         {   0, L"LTYPE"       };
            const code_t continuous_line =   {   2, L"CONTINUOUS"  };
            const code_t continuous_layer =  {   6, L"CONTINUOUS"  };
            const code_t style =             {   2, L"STYLE"       };
            const code_t blocks =            {   2, L"BLOCKS"      };
            const code_t entities =          {   2, L"ENTITIES"    };
            const code_t line =              {   0, L"LINE"        };
            const code_t eof =               {   0, L"EOF"         };
            const code_t acad_version =      {   9, L"$ACADVER"    };
            const code_t ac_1006 =           {   1, L"AC1006"      };
            const code_t ins_base =          {   9, L"$INSBASE"    };
            const code_t extension_min =     {   9, L"$EXTMIN"     };
            const code_t extension_max =     {   9, L"$EXTMAX"     };

            //////////////////////////////////////////////////////////////////////////
            //
            // DXF special codes.

            const code_t comment(const text_t& comment)
            {
               return code_t{ 999, comment };
            }

            const code_t use_layer(int32_t which_layer)
            {
               return code_t{ 8, std::to_wstring(which_layer)};
            }

            const code_t use_color(int32_t which_color)
            {
               return code_t{ 62, std::to_wstring(which_color) };
            }
         }
      }

      //////////////////////////////////////////////////////////////////////////
      //
      // DXF drawing interface implementation.

      dxf_drawing_t::dxf_drawing_t(std::wostream& out)
         : out(out)
      {
      }

      dxf_drawing_t::~dxf_drawing_t()
      {
         try
         {
            finish();
         }
         catch (const std::exception&)
         {
            // Ignore exceptions in destructor.
         }
      }

      void dxf_drawing_t::finish()
      {
         dxf::codes::maker_t maker;

         out << dxf::codes::comment(L"Generated by Alhambra");
         out << dxf::codes::section << dxf::codes::header;
            out << dxf::codes::acad_version;
            out << dxf::codes::ins_base << maker.make_double_code(0.0) << maker.make_double_code(0.0) << maker.make_double_code(0.0) << maker.reset();
            out << dxf::codes::extension_min << maker.make_double_code(std::floor(bbox.x - 1))
                                             << maker.make_double_code(std::floor(bbox.y - 1))
                                             << maker.reset();
            out << dxf::codes::extension_max << maker.make_double_code(std::ceil(bbox.x + bbox.width  + 1))
                                             << maker.make_double_code(std::ceil(bbox.y + bbox.height + 1))
                                             << maker.reset();
         out << dxf::codes::end_section;

         out << dxf::codes::section << dxf::codes::tables;
            out << dxf::codes::table;
               out << dxf::codes::line_type << dxf::raw(70) << dxf::raw(1);
               out << dxf::codes::line_type << dxf::codes::continuous_line << dxf::raw(70) << dxf::raw(64)
                   << dxf::raw(3) << dxf::raw(text_t(L"Solid line")) << dxf::raw(72) << dxf::raw(65) << dxf::raw(73)
                   << dxf::raw(0) << dxf::raw(40) << dxf::raw(0.0);
            out << dxf::codes::end_table;

            out << dxf::codes::table;
               out << dxf::codes::layer << dxf::raw(70) << dxf::raw(6);
               out << dxf::codes::layer << dxf::raw(2) << dxf::raw(1) << dxf::raw(70) << dxf::raw(64)
                                        << dxf::raw(62) << dxf::raw(7) << dxf::codes::continuous_layer;
               out << dxf::codes::layer << dxf::raw(2) << dxf::raw(2) << dxf::raw(70) << dxf::raw(64)
                                        << dxf::raw(62) << dxf::raw(7) << dxf::codes::continuous_layer;
            out << dxf::codes::end_table;

            out << dxf::codes::table;
               out << dxf::codes::style << dxf::raw(70) << dxf::raw(0);
            out << dxf::codes::end_table;
         out << dxf::codes::end_section;

         out << dxf::codes::section << dxf::codes::tables;
            out << dxf::codes::blocks;
         out << dxf::codes::end_section;

         out << dxf::codes::section << dxf::codes::entities;
            out << buffer.str();
         out << dxf::codes::end_section;

         out << dxf::codes::eof;
      }

      drawing_t& dxf_drawing_t::draw_line(const point_t& from, const point_t& dest)
      {
         if (from.is_invalid() || dest.is_invalid())
            return *this;

         internal_update_stroke();
         internal_update_color();
         internal_update_transform();
         internal_update_bbox(from);
         internal_update_bbox(dest);

         dxf::codes::maker_t maker;

         buffer << dxf::codes::line << dxf::codes::use_layer(1) << dxf::codes::use_color(0)
                << maker.make_double_code(from.x) << maker.make_double_code(from.y) << maker.make_double_code(0) << maker.reset(1)
                << maker.make_double_code(dest.x) << maker.make_double_code(dest.y) << maker.make_double_code(0) << maker.reset(0);

         return *this;
      }

      drawing_t& dxf_drawing_t::draw_corner(const point_t& from, const point_t& midd, const point_t& dest)
      {
         if (from.is_invalid() || midd.is_invalid() || dest.is_invalid())
            return *this;

         internal_update_stroke();
         internal_update_color();
         internal_update_transform();
         internal_update_bbox(from);
         internal_update_bbox(midd);
         internal_update_bbox(dest);

         dxf::codes::maker_t maker;

         buffer << dxf::codes::line << dxf::codes::use_layer(1) << dxf::codes::use_color(0)
                << maker.make_double_code(from.x) << maker.make_double_code(from.y) << maker.make_double_code(0) << maker.reset(1)
                << maker.make_double_code(midd.x) << maker.make_double_code(midd.y) << maker.make_double_code(0) << maker.reset(0);

         buffer << dxf::codes::line << dxf::codes::use_layer(1) << dxf::codes::use_color(0)
                << maker.make_double_code(midd.x) << maker.make_double_code(midd.y) << maker.make_double_code(0) << maker.reset(1)
                << maker.make_double_code(dest.x) << maker.make_double_code(dest.y) << maker.make_double_code(0) << maker.reset(0);

         return *this;
      }

      drawing_t& dxf_drawing_t::fill_polygon(const polygon_t& p)
      {
         if (p.is_invalid())
            return *this;

         const auto& pts = p.points;

         if (pts.size() < 2)
            return *this;

         internal_update_stroke();
         internal_update_color();
         internal_update_transform();
         internal_update_bbox(pts);

         dxf::codes::maker_t maker;

         point_t prev_pt = pts.back();
         for (const point_t curr_pt : pts) {
            buffer << dxf::codes::line << dxf::codes::use_layer(1) << dxf::codes::use_color(0)
               << maker.make_double_code(prev_pt.x) << maker.make_double_code(prev_pt.y) << maker.make_double_code(0) << maker.reset(1)
               << maker.make_double_code(curr_pt.x) << maker.make_double_code(curr_pt.y) << maker.make_double_code(0) << maker.reset(0);
            prev_pt = curr_pt;
         }

         return *this;
      }

      drawing_t& dxf_drawing_t::draw_polygon(const polygon_t& p)
      {
         if (p.is_invalid())
            return *this;

         const auto& pts = p.points;

         if (pts.size() < 2)
            return *this;

         internal_update_stroke();
         internal_update_color();
         internal_update_transform();
         internal_update_bbox(pts);

         dxf::codes::maker_t maker;

         point_t prev_pt = pts.back();
         for (const point_t curr_pt : pts) {
            buffer << dxf::codes::line << dxf::codes::use_layer(1) << dxf::codes::use_color(0)
                   << maker.make_double_code(prev_pt.x) << maker.make_double_code(prev_pt.y) << maker.make_double_code(0) << maker.reset(1)
                   << maker.make_double_code(curr_pt.x) << maker.make_double_code(curr_pt.y) << maker.make_double_code(0) << maker.reset(0);
            prev_pt = curr_pt;
         }

         return *this;
      }

      drawing_t& dxf_drawing_t::fill_oval(const point_t& c, double rx, double ry)
      {
         internal_update_stroke();
         internal_update_color();
         internal_update_transform();
         internal_update_bbox(c);
         internal_update_bbox(c + point_t(rx, ry));
         internal_update_bbox(c - point_t(rx, ry));

         // TODO: dxf_drawing_t::fill_oval

         return *this;
      }

      drawing_t& dxf_drawing_t::draw_oval(const point_t& c, double rx, double ry)
      {
         internal_update_stroke();
         internal_update_color();
         internal_update_transform();

         // TODO: dxf_drawing_t::draw_oval

         return *this;
      }

      drawing_t& dxf_drawing_t::fill_arc(const point_t& c, double rx, double ry, double angle1, double angle2)
      {
         internal_update_stroke();
         internal_update_color();
         internal_update_transform();

         // TODO: dxf_drawing_t::fill_arc

         return *this;
      }

      drawing_t& dxf_drawing_t::fill_rect(const rectangle_t& r)
      {
         fill_polygon(polygon_t::from_rect(r));

         return *this;
      }

      drawing_t& dxf_drawing_t::draw_rect(const rectangle_t& r)
      {
         draw_polygon(polygon_t::from_rect(r));

         return *this;
      }

      // Note: the bounds are *without* the transform.
      //       They are the true bounds of the drawing surface.
      rectangle_t dxf_drawing_t::get_bounds() const
      {
         return bbox;
      }

      void dxf_drawing_t::internal_update_bbox(const std::vector<point_t>& pts)
      {
         for (const auto& p : pts)
            internal_update_bbox(p);
      }

      void dxf_drawing_t::internal_update_bbox(const point_t& p)
      {
         bbox = bbox.combine(point_t(p.x, p.y));
      }

      void dxf_drawing_t::internal_update_color()
      {
         if (get_color() == applied_co)
            return;

         applied_co = get_color();

         // TODO: internal_update_color()
      }

      void dxf_drawing_t::internal_update_stroke()
      {
         if (get_stroke() == applied_strk)
            return;

         applied_strk = get_stroke();
         
         // TODO: internal_update_stroke()
      }

      void dxf_drawing_t::internal_update_transform()
      {
         if (get_transform() == applied_trf)
            return;

         applied_trf = get_transform();

         // TODO: internal_update_stroke()
      }
   }
}

// vim: sw=3 : sts=3 : et : sta : 
