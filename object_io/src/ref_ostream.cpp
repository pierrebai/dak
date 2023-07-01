#include <dak/object_io/ref_ostream.h>

namespace dak::object
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Output a end-line and indent the next line to the current indentation.


   // Abort the input, called on errors, in particular by abort_on_unknown().
   void ref_ostream_t::abort() const
   {
      auto& ostr = get_stream();
      ostr.setstate(std::ios::failbit);
   }

   const ref_ostream_t& ref_ostream_t::end_line() const
   {
      static const wchar_t whitespaces[] = L"                            ";
      static const int32_t white_count = int32_t(sizeof(whitespaces) / sizeof(whitespaces[0]) - 1);

      auto& ostr = get_stream();

      ostr << L'\n';

      for (int32_t indent = my_indentation; indent > 0; )
      {
         const int32_t amount = (indent >= white_count) ? white_count : indent;
         const int32_t offset = white_count - amount;
         indent -= amount;
         ostr << (whitespaces + offset);
      }

      return *this;
   }

   ref_ostream_indent_t::ref_ostream_indent_t(const ref_ostream_t& ostr,
      const text_t& open, const text_t& close, int32_t indent_by)
      : my_ostr(ostr), my_close(close), my_indent_by(indent_by)
   {
      ostr.get_stream() << open;
      ostr.my_indentation += indent_by;
   }
   ref_ostream_indent_t::~ref_ostream_indent_t()
   {
      my_ostr.my_indentation -= my_indent_by;
      my_ostr.end_line();
      my_ostr.get_stream() << my_close;
   }
}

