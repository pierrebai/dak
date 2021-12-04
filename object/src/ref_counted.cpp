#include "dak/object/ref_counted.h"

#include <limits>

namespace dak::object
{
   ref_counted_t::ref_counted_t(const ref_counted_t&)
      : my_ref_count(0)
   {
   }

   ref_counted_t& ref_counted_t::operator =(const ref_counted_t&)
   {
      return *this;
   }

   void ref_counted_t::add_ref() const
   {
      ++my_ref_count;
   }

   void ref_counted_t::sub_ref() const
   {
      if (--my_ref_count == 0)
      {
         // Prevent deletion by making the strong reference count very negative
         // while we're clearing. The reason is that referenced objects could
         // have weak references to us. Also, do subtraction and addition
         // to the ref-count as clearing could somehow add new strong references
         // to this, however unlikely that may seem, and we cannot just reset it
         // to zero. 
         my_ref_count -= std::numeric_limits<int32_t>::min() / 2;
         const_cast<ref_counted_t*>(this)->clear();
         my_ref_count += std::numeric_limits<int32_t>::min() / 2;
         check_ref();
      }
   }

   void ref_counted_t::add_weak() const
   {
      ++my_weak_count;
   }

   void ref_counted_t::sub_weak() const
   {
      if (--my_weak_count == 0)
      {
         check_ref();
      }
   }
   void ref_counted_t::check_ref() const
   {
      if (my_ref_count == 0 && my_weak_count == 0)
      {
         // Prevent double-deletion by making the all reference counts
         // very negative while we're destroying this.
         my_ref_count = std::numeric_limits<int32_t>::min() / 2;
         my_weak_count = std::numeric_limits<int32_t>::min() / 2;
         delete this;
      }
   }
}

