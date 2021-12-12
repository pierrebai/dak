#include "dak/object/ref_ostream.h"

namespace dak::object
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Output stream wrapper data.

   namespace
   {
      bool is_valid(const ref_t<object_t>& object) { return object.is_valid(); }
      bool is_valid(const exact_name_t& name) { return name.is_valid(); }
      bool is_valid(const datatype_t* a_type) { return a_type && *a_type != typeid(void); }

      template <class T>
      int64_t get_thing_id(std::unordered_map<T, int64_t>& ids, const T& thing)
      {
         if (!is_valid(thing))
            return 0;

         const auto pos = ids.find(thing);
         if (pos != ids.end())
            return -pos->second;

         // Note: 0 is reserved for invalid things.
         const int64_t id = static_cast<int64_t>(ids.size()) + 1;
         ids[thing] = id;
         return id;
      }
   }

   int64_t ref_ostream_t::get_object_id(const ref_t<object_t>& object) const
   {
      return get_thing_id<ref_t<object_t>>(my_object_ids, object);
   }

   int64_t ref_ostream_t::get_name_id(const exact_name_t& name) const
   {
      return get_thing_id<exact_name_t>(my_name_ids, name);
   }

   int64_t ref_ostream_t::get_type_id(const datatype_t& a_type) const
   {
      return get_thing_id<const datatype_t*>(my_type_ids, &a_type);
   }

   void ref_ostream_t::clear()
   {
      my_object_ids.clear();
      my_name_ids.clear();
      my_type_ids.clear();
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Output a end-line and indent the next line to the current indentation.

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

