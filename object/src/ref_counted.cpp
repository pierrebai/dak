#include "dak/object/ref_counted.h"

#include <limits>

namespace dak::object
{
   ref_counted_t::ref_counted_t(const ref_counted_t &)
   : my_refcount(0)
   {
   }

   ref_counted_t& ref_counted_t::operator =(const ref_counted_t &)
   {
      return *this;
   }

   void ref_counted_t::addref() const
   {
      ++my_refcount;
   }

   void ref_counted_t::unref() const
   {
      if ( --my_refcount == 0 )
      {
         my_refcount = std::numeric_limits<int64_t>::min() / 2;
         delete this;
      }
   }
}

