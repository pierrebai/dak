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

   std::wostream& operator<<(std::wostream& ostr, const element_t& e)
   {
      switch(e.type())
      {
         case datatype_t::unknown:  return ostr << L"unknown";
         case datatype_t::boolean:  return ostr << (bool) e;
         case datatype_t::integer:  return ostr << (int64_t) e;
         case datatype_t::ref:      return ostr << *(const valid_ref_t<object_t> &) e;
         case datatype_t::name:     return ostr << (const name_t &) e;
         case datatype_t::real:     return ostr << (double) e;
         case datatype_t::array:    return ostr << (const array_t &) e;
         case datatype_t::dict:     return ostr << (const dict_t &) e;
         case datatype_t::text:     return ostr << (str_ptr_t) e;
         default:                   return ostr;
      }
   }

   std::wostream& operator<<(std::wostream& ostr, const name_t& n)
   {
      ostr << n.to_text();
      return ostr;
   }

   std::wostream& operator<<(std::wostream& ostr, const array_t& a)
   {
      ostr << L"[\n";
      for (const element_t& e : a)
         ostr << e << L" ,\n";
      ostr << L"]";
      return ostr;
   }

   std::wostream& operator<<(std::wostream& ostr, const dict_t& d)
   {
      ostr << L"{\n";
      for (const auto& [n, e] : d)
         ostr << n << L" : " <<  e << L" ,\n";
      ostr << L"}";
      return ostr;
   }

   std::wostream& operator<<(std::wostream& ostr, const object_t& o)
   {
      ostr << L"{\n";
      for (const auto& [n, e] : o)
         ostr << n << L" : " << e << L" ,\n";
      ostr << L"}";
      return ostr;
   }
}

