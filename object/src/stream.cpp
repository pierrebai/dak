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

   namer_stream_helper_t operator <<(std::wostream& nsh, const namer_t& n)
   {
      return namer_stream_helper_t(nsh, n);
   }

   const namer_stream_helper_t& print(const namer_stream_helper_t& nsh, const element_t& e)
   {
      switch(e.type())
      {
         case datatype_t::unknown:  return nsh << L"unknown";
         case datatype_t::boolean:  return nsh << (bool) e;
         case datatype_t::integer:  return nsh << (int64_t) e;
         case datatype_t::ref:      return nsh << L"ref"; // TODO
         case datatype_t::name:     return nsh << (const name_t &) e;
         case datatype_t::real:     return nsh << (double) e;
         case datatype_t::array:    return nsh << (const array_t &) e;
         case datatype_t::dict:     return nsh << (const dict_t &) e;
         case datatype_t::text:     return nsh << (str_ptr_t) e;
         default:                 return nsh;
      }
   }

   const namer_stream_helper_t& print(const namer_stream_helper_t& nsh, const array_t& a)
   {
      nsh << L"[ ";
      for (const element_t& e : a)
         nsh << e << L" , ";
      nsh << L"]";
      return nsh;
   }

   const namer_stream_helper_t& print(const namer_stream_helper_t& nsh, const dict_t& d)
   {
      nsh << L"{ ";
      for (const auto& [n, e] : d)
         nsh << n << L" : " <<  e << L" , ";
      nsh << L"}";
      return nsh;
   }

   const namer_stream_helper_t& print(const namer_stream_helper_t& nsh, const object_t& o)
   {
      nsh << L"{ ";
      for (const auto& [n, e] : o)
         nsh << n << L" : " << e << L" , ";
      nsh << L"}";
      return nsh;
   }
}

