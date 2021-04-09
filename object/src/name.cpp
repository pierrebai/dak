#include "dak/object/name.h"

namespace dak::object
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Constructors.

   ref_t<name_t::rc_sub_names_t> name_t::rc_sub_names_t::make()
   {
      return new rc_sub_names_t;
   }

   ref_t<name_t::rc_sub_names_t> name_t::rc_sub_names_t::make(const rc_sub_names_t& s)
   {
      return new rc_sub_names_t(s);
   }

   // Name root constructor.
   name_t::name_t()
      : my_sub_names(new rc_sub_names_t)
   {
   }

   // Rooted constructors.
   name_t::name_t(name_t& root, const text_t& a_label)
      : my_sub_names((*root.my_sub_names)[a_label].my_sub_names)
   {
   }

   name_t::name_t(name_t& root, str_ptr_t a_label)
      : my_sub_names((*root.my_sub_names)[a_label].my_sub_names)
   {
   }

   // Internal constructor.
   name_t::name_t(rc_sub_names_t* d)
      : my_sub_names(d ? d : new rc_sub_names_t)
   {
   }

   // Destructor.
   name_t::~name_t()
   {
   }

   // Access rooted name.
   name_t name_t::operator/(const text_t& a_label)
   {
      return (*my_sub_names)[a_label];
   }

   name_t name_t::operator/(str_ptr_t a_label)
   {
      return (*my_sub_names)[a_label];
   }

   name_t::iterator name_t::begin()
   {
      return my_sub_names->begin();
   }

   name_t::iterator name_t::end()
   {
      return my_sub_names->end();
   }

   name_t::const_iterator name_t::begin() const
   {
      return my_sub_names->begin();
   }

   name_t::const_iterator name_t::end() const
   {
      return my_sub_names->end();
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Data methods.

   bool name_t::is_valid() const
   {
      return my_sub_names.is_valid();
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Comparison methods.

   bool name_t::operator ==(const name_t& other) const
   {
      return my_sub_names.my_object == other.my_sub_names.my_object;
   }

   bool name_t::operator !=(const name_t& other) const
   {
      return my_sub_names.my_object != other.my_sub_names.my_object;
   }

   bool name_t::operator <(const name_t& other) const
   {
      return my_sub_names.my_object < other.my_sub_names.my_object;
   }

   bool name_t::operator <=(const name_t& other) const
   {
      return my_sub_names.my_object <= other.my_sub_names.my_object;
   }

   bool name_t::operator >(const name_t& other) const
   {
      return my_sub_names.my_object > other.my_sub_names.my_object;
   }

   bool name_t::operator >=(const name_t& other) const
   {
      return my_sub_names.my_object >= other.my_sub_names.my_object;
   }

   uint64_t name_t::hash() const
   {
      return static_cast<uint64_t>(reinterpret_cast<intptr_t>(my_sub_names.my_object));
   }
}
