#include "dak/object/stream.h"
#include "dak/utility/types.h"
#include "dak/object/dict.h"
#include "dak/object/array.h"
#include "dak/object/object.h"

namespace dak::object
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Stream operations.

   stream_helper_t operator <<(std::wostream& nsh, const namer_t& n)
   {
      return stream_helper_t(nsh, n);
   }

   const stream_helper_t& print(const stream_helper_t& nsh, const element_t& e)
   {
      switch(e.type())
      {
         case datatype_t::unknown:  return nsh << L"unknown";
         case datatype_t::boolean:  return nsh << (bool) e;
         case datatype_t::integer:  return nsh << (int64_t) e;
         case datatype_t::ref:      return nsh << (const ref_t<const object_t> &) e;
         case datatype_t::name:     return nsh << (const name_t &) e;
         case datatype_t::real:     return nsh << (double) e;
         case datatype_t::array:    return nsh << (const array_t &) e;
         case datatype_t::dict:     return nsh << (const dict_t &) e;
         case datatype_t::text:     return nsh << (str_ptr_t) e;
         default:                   return nsh;
      }
   }

   const stream_helper_t& print(const stream_helper_t& nsh, const array_t& a)
   {
      nsh << L"[\n";
      for (const element_t& e : a)
         nsh << e << L" ,\n";
      nsh << L"]";
      return nsh;
   }

   const stream_helper_t& print(const stream_helper_t& nsh, const dict_t& d)
   {
      nsh << L"{\n";
      for (const auto& [n, e] : d)
         nsh << n << L" : " <<  e << L" ,\n";
      nsh << L"}";
      return nsh;
   }

   const stream_helper_t& print(const stream_helper_t& nsh, const object_t& o)
   {
      nsh << L"{\n";
      for (const auto& [n, e] : o)
         nsh << n << L" : " << e << L" ,\n";
      nsh << L"}";
      return nsh;
   }

   int64_t stream_helper_t::get_object_id(const ref_t<const object_t>& object) const
   {
      if (!object)
         return 0;

      const auto pos = my_object_ids.find(object);
      if (pos != my_object_ids.end())
         return -pos->second;

      // Note: 0 is reserved for null object ref.
      const int64_t id = static_cast<int64_t>(my_object_ids.size()) + 1;
      my_object_ids[object] = id;
      return id;
   }

   void stream_helper_t::clear()
   {
      my_object_ids.clear();
   }

   const stream_helper_t& print(const stream_helper_t& nsh, const ref_t<const object_t>& o)
   {
      const auto id = nsh.get_object_id(o);
      nsh << L"ref " << id;
      if (id > 0)
         nsh << " " << *o;
      return nsh;
   }
}

