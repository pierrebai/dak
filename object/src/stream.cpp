#include "dak/object/ref_stream.h"
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
      ref_stream_t(ostr) << e;
      return ostr;
   }

   std::wostream& operator<<(std::wostream& ostr, const name_t& n)
   {
      ostr << n.to_text();
      return ostr;
   }

   std::wostream& operator<<(std::wostream& ostr, const array_t& a)
   {
      ref_stream_t(ostr) << a;
      return ostr;
   }

   std::wostream& operator<<(std::wostream& ostr, const dict_t& d)
   {
      ref_stream_t(ostr) << d;
      return ostr;
   }

   std::wostream& operator<<(std::wostream& ostr, const object_t& o)
   {
      ref_stream_t(ostr) << o;
      return ostr;
   }
}

