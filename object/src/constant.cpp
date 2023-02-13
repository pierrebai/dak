#include <dak/object/constant.h>

namespace dak::object
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Data access.

   bool constant_t::contains(const name_t& n) const
   {
      return 0 != my_values.count(n);
   }

   index_t constant_t::size() const
   {
      return my_values.size();
   }

   const value_t & constant_t::operator [](const name_t& n) const
   {
      const_iterator pos = my_values.find(n);
      if(my_values.end() == pos)
         return value_t::empty;
      else
         return pos->second;
   }

   constant_t::const_iterator constant_t::begin() const
   {
      return my_values.begin();
   }

   constant_t::const_iterator constant_t::end() const
   {
      return my_values.end();
   }

   void constant_t::clear()
   {
      my_values.clear();
   }

}
