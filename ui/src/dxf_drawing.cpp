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

            const code_t section =           {   0, L"SECTION"       };
            const code_t end_section =       {   0, L"ENDSEC"        };
            const code_t header =            {   2, L"HEADER"        };
            const code_t tables =            {   2, L"TABLES"        };
            const code_t table =             {   0, L"TABLE"         };
            const code_t end_table =         {   0, L"ENDTAB"        };
            const code_t layer =             {   0, L"LAYER"         };
            const code_t line_type =         {   0, L"LTYPE"         };
            const code_t alignment =         {  72, L"65"            };
            const code_t style =             {   2, L"STYLE"         };
            const code_t entities =          {   2, L"ENTITIES"      };
            const code_t line =              {   0, L"LINE"          };
            const code_t eof =               {   0, L"EOF"           };
            const code_t acad_version =      {   9, L"$ACADVER"      };
            const code_t ac_1006 =           {   1, L"AC1006"        };
            const code_t ins_base =          {   9, L"$INSBASE"      };
            const code_t extension_min =     {   9, L"$EXTMIN"       };
            const code_t extension_max =     {   9, L"$EXTMAX"       };
            const code_t polyline =          {   0, L"LWPOLYLINE"    };
            const code_t ac_entity =         { 100, L"AcDbEntity"    };
            const code_t ac_polyline =       { 100, L"AcDbPolyline"  };

            //////////////////////////////////////////////////////////////////////////
            //
            // DXF varying codes.

            code_t comment(const text_t& comment)
            {
               return code_t{ 999, comment };
            }

            code_t entry_name(const text_t& name)
            {
               return code_t{ 2, name };
            }

            code_t entry_description(const text_t& desc)
            {
               return code_t{ 3, desc };
            }

            code_t handle(const size_t id)
            {
               return code_t{ 5, text_t(L"H") + std::to_wstring(id) };
            }

            code_t line_type_count(int32_t count)
            {
               return code_t{ 73, std::to_wstring(count) };
            }

            code_t line_type_pattern_length(double length)
            {
               return code_t{ 40, std::to_wstring(length) };
            }

            code_t use_line_type(const text_t& name)
            {
               return code_t{ 6, name };
            }

            code_t use_layer(int32_t which_layer)
            {
               return code_t{ 8, std::to_wstring(which_layer)};
            }

            code_t use_color(int32_t which_color)
            {
               return code_t{ 62, std::to_wstring(which_color) };
            }

            code_t line_weight(int32_t which_color)
            {
               return code_t{ 370, std::to_wstring(which_color) };
            }

            code_t constant_width(double width)
            {
               return code_t{ 43, std::to_wstring(width) };
            }

            code_t vertices_count(int32_t count)
            {
               return code_t{ 90, std::to_wstring(count) };
            }

            code_t vertices_count(size_t count)
            {
               return code_t{ 90, std::to_wstring(int32_t(count)) };
            }

            code_t flags(int32_t value)
            {
               return code_t{ 70, std::to_wstring(int32_t(value)) };
            }

            code_t polyline_closed(bool is_closed)
            {
               return code_t{ 70, std::to_wstring(is_closed ? 1 : 0) };
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
         if (finished)
            return;
         finished = true;

         dxf::codes::maker_t maker;

         const text_t solid_line_type_name = L"CONTINUOUS";
         const text_t solid_line_type_desc = L"Solid line";

         out << dxf::codes::comment(L"Generated by Alhambra");
         out << dxf::codes::section << dxf::codes::header;
            out << dxf::codes::acad_version << dxf::codes::ac_1006;
            out << dxf::codes::ins_base << maker.make_double_code(0.0) << maker.make_double_code(0.0) << maker.make_double_code(0.0) << maker.reset();
            out << dxf::codes::extension_min << maker.make_double_code(std::floor(bbox.x - 1))
                                             << maker.make_double_code(std::floor(bbox.y - 1))
                                             << maker.reset();
            out << dxf::codes::extension_max << maker.make_double_code(std::ceil(bbox.x + bbox.width  + 1))
                                             << maker.make_double_code(std::ceil(bbox.y + bbox.height + 1))
                                             << maker.reset();
         out << dxf::codes::end_section;

         out << dxf::codes::section << dxf::codes::tables;
            out << dxf::codes::table << dxf::codes::entry_name(L"LTYPE");
               out << dxf::codes::line_type << dxf::codes::flags(0);
               out << dxf::codes::line_type << dxf::codes::entry_name(solid_line_type_name) << dxf::codes::flags(0)
                   << dxf::codes::entry_description(solid_line_type_desc) << dxf::codes::alignment
                   << dxf::codes::line_type_count(0) << dxf::codes::line_type_pattern_length(0.0);
               out << dxf::codes::end_table;

            out << dxf::codes::table << dxf::codes::entry_name(L"LAYER");
               out << dxf::codes::layer << dxf::codes::entry_name(L"0") << dxf::codes::flags(0)
                                        << dxf::codes::use_color(0) << dxf::codes::use_line_type(solid_line_type_name);
               out << dxf::codes::layer << dxf::codes::entry_name(L"1") << dxf::codes::flags(0)
                                        << dxf::codes::use_color(7) << dxf::codes::use_line_type(solid_line_type_name);
               out << dxf::codes::layer << dxf::codes::entry_name(L"2") << dxf::codes::flags(0)
                                        << dxf::codes::use_color(7) << dxf::codes::use_line_type(solid_line_type_name);
            out << dxf::codes::end_table;

            out << dxf::codes::table << dxf::codes::entry_name(L"STYLE");
               out << dxf::codes::flags(0);
            out << dxf::codes::end_table;
         out << dxf::codes::end_section;

         out << dxf::codes::section << dxf::codes::entry_name(L"BLOCKS");
         out << dxf::codes::end_section;

         out << dxf::codes::section << dxf::codes::entry_name(L"ENTITIES");
            out << buffer.str();
         out << dxf::codes::end_section;

         out << dxf::codes::eof;
      }

      void dxf_drawing_t::start_polyline(size_t vertices_count, bool is_closed)
      {
         buffer << dxf::codes::polyline << dxf::codes::handle(++next_handle_id)
                << dxf::codes::ac_entity << dxf::codes::use_layer(0)
                << dxf::codes::use_line_type(L"BYLAYER") << dxf::codes::use_color(256) << dxf::codes::line_weight(-1)
                << dxf::codes::ac_polyline << dxf::codes::vertices_count(vertices_count)
                << dxf::codes::polyline_closed(is_closed) << dxf::codes::constant_width(0);
      }

      drawing_t& dxf_drawing_t::draw_line(const point_t& from, const point_t& dest)
      {
         return draw_polygon(polygon_t({ from , dest }));
      }

      drawing_t& dxf_drawing_t::draw_corner(const point_t& from, const point_t& midd, const point_t& dest)
      {
         return draw_polygon(polygon_t({ from , midd, dest }));
      }

      drawing_t& dxf_drawing_t::fill_polygon(const polygon_t& p)
      {
         return draw_polygon(p);
      }

      drawing_t& dxf_drawing_t::draw_polygon(const polygon_t& p)
      {
         if (p.is_invalid())
            return *this;

         const auto& pts = p.points;

         internal_update_stroke();
         internal_update_color();
         internal_update_transform();
         internal_update_bbox(pts);

         dxf::codes::maker_t maker;

#ifdef DAK_DXF_USE_POLYLINE

         if (pts.size() < 2)
            return *this;

         start_polyline(pts.size(), true);
         for (const point_t pt : pts) {
            buffer << maker.make_double_code(pt.x) << maker.make_double_code(pt.y) << maker.reset(0);
         }

#else
         if (pts.size() < 3)
            return *this;


         const point_t& corner = pts[0];
         for (size_t i = 2; i < pts.size(); ++i) {
            const point_t& p1 = corner;
            const point_t& p2 = pts[i - 1];
            const point_t& p3 = pts[i];
            const point_t& p4 = corner;
            buffer << dxf::raw(0) << dxf::raw(text_t(L"3DFACE"))
               << dxf::codes::use_layer(0) << dxf::codes::use_color(256);
            buffer << maker.make_double_code(p1.x) << maker.make_double_code(p1.y) << maker.make_double_code(0) << maker.reset(1);
            buffer << maker.make_double_code(p2.x) << maker.make_double_code(p2.y) << maker.make_double_code(0) << maker.reset(2);
            buffer << maker.make_double_code(p3.x) << maker.make_double_code(p3.y) << maker.make_double_code(0) << maker.reset(3);
            buffer << maker.make_double_code(p4.x) << maker.make_double_code(p4.y) << maker.make_double_code(0) << maker.reset(0);
         }

#endif

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
