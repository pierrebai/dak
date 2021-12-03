#include "dak/object/ref_counted.h"

#include <limits>

namespace dak::object
{
   ref_counted_t::ref_counted_t(const ref_counted_t &)
   : my_ref_count(0)
   {
   }

   ref_counted_t& ref_counted_t::operator =(const ref_counted_t &)
   {
      return *this;
   }

   void ref_counted_t::add_ref() const
   {
      ++my_ref_count;
   }

   void ref_counted_t::sub_ref() const
   {
      if ( --my_ref_count == 0 )
      {
         my_ref_count = std::numeric_limits<int64_t>::min() / 2;
         delete this;
      }
   }
}

