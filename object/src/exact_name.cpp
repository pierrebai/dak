#include <dak/object/exact_name.h>

namespace dak::object
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Name comparison and hash.

   std::strong_ordering exact_name_t::operator <=>(const exact_name_t& other) const
   {
      // Compare name stuff pointers, so that only the same names compare equal.
      return my_stuff <=> other.my_stuff;
   }

   bool exact_name_t::operator ==(const exact_name_t& other) const
   {
      // Compare name stuff pointers, so that only the same names compare equal.
      return my_stuff == other.my_stuff;
   }

   uint64_t exact_name_t::hash() const
   {
      return my_stuff.hash();
   }
}
