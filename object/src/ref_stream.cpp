#include "dak/object/ref_stream.h"
#include "dak/object/stream.h"

namespace dak::object
{
   int64_t ref_stream_t::get_object_id(const ref_t<object_t>& object) const
   {
      if (object.is_null())
         return 0;

      const auto pos = my_object_ids.find(object);
      if (pos != my_object_ids.end())
         return -pos->second;

      // Note: 0 is reserved for null object ref.
      const int64_t id = static_cast<int64_t>(my_object_ids.size()) + 1;
      my_object_ids[object] = id;
      return id;
   }

   void ref_stream_t::clear()
   {
      my_object_ids.clear();
   }

   const ref_stream_t& ref_stream_t::print(const ref_t<object_t>& o) const
   {
      const auto id = get_object_id(o);
      *this << L"ref " << id;
      if (id > 0)
         *this << " " << *valid_ref_t(o);
      return *this;
   }

   const ref_stream_t& ref_stream_t::print(const array_t& a) const
   {
      *this << L"[\n";
      for (const element_t& e : a)
         *this << e << L" ,\n";
      *this << L"]";
      return *this;
   }

   const ref_stream_t& ref_stream_t::print(const dict_t& d) const
   {
      *this << L"{\n";
      for (const auto& [n, e] : d)
         *this << n << L" : " << e << L" ,\n";
      *this << L"}";
      return *this;
   }

   const ref_stream_t& ref_stream_t::print(const object_t& o) const
   {
      *this << L"{\n";
      for (const auto& [n, e] : o)
         *this << n << L" : " << e << L" ,\n";
      *this << L"}";
      return *this;
   }

   const ref_stream_t& ref_stream_t::print(const element_t& e) const
   {
      switch (e.type())
      {
         case datatype_t::unknown:  return *this << L"unknown";
         case datatype_t::boolean:  return *this << (bool)e;
         case datatype_t::integer:  return *this << (int64_t)e;
         case datatype_t::ref:      return *this << (const ref_t<object_t> &) e;
         case datatype_t::name:     return *this << (const name_t&)e;
         case datatype_t::real:     return *this << (double)e;
         case datatype_t::array:    return *this << (const array_t&)e;
         case datatype_t::dict:     return *this << (const dict_t&)e;
         case datatype_t::text:     return *this << (str_ptr_t)e;
         default:                   return *this;
      }
}
}

