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

   namer_stream_helper_t operator <<(std::wostream& o, const namer_t& n)
   {
      return namer_stream_helper_t(o, n);
   }

   namer_stream_helper_t print(namer_stream_helper_t o, const element_t& e)
   {
      switch(e.type())
      {
         case datatype_t::unknown:  return o << L"unknown";
         case datatype_t::boolean:  return o << (bool) e;
         case datatype_t::integer:  return o << (int64_t) e;
         case datatype_t::ref:      return o << L"ref"; // TODO
         case datatype_t::name:     return o << (const name_t &) e;
         case datatype_t::real:     return o << (double) e;
         case datatype_t::array:    return o << (const array_t &) e;
         case datatype_t::dict:     return o << (const dict_t &) e;
         case datatype_t::text:     return o << (str_ptr_t) e;
         default:                 return o;
      }
   }

   namer_stream_helper_t print(namer_stream_helper_t o, const array_t& a)
   {
      o << L"[ ";
      for (const element_t& e : a)
         o << e << L" , ";
      o << L"]";
      return o;
   }

   namer_stream_helper_t print(namer_stream_helper_t o, const dict_t& d)
   {
      o << L"{ ";
      for (const auto& [n, e] : d)
         o << n << L" : " <<  e << L" , ";
      o << L"}";
      return o;
   }

   namer_stream_helper_t print(namer_stream_helper_t o, const modifiable_object_t& d)
   {
      o << L"{ ";
      for (const auto& [n, e] : d)
         o << n << L" : " << e << L" , ";
      o << L"}";
      return o;
   }

   namer_stream_helper_t print(namer_stream_helper_t o, const object_t& d)
   {
      o << L"{ ";
      for (const auto& [n, e] : d)
         o << n << L" : " << e << L" , ";
      o << L"}";
      return o;
   }
}

