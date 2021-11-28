#include "dak/object/name.h"
#include "dak/object/name_stuff.h"

namespace dak::object
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Constructors.

   name_t::name_t(const edit_ref_t<namespace_t>& a_namespace, str_ptr_t a_label)
      : my_stuff(name_stuff_t::make(a_namespace, a_label))
   {
   }

   name_t::name_t(const edit_ref_t<namespace_t>& a_namespace, const text_t& a_label)
      : my_stuff(name_stuff_t::make(a_namespace, a_label))
   {
   }

   name_t::name_t(const edit_ref_t<namespace_t>& a_namespace, const name_t& a_basename)
      : my_stuff(a_basename.my_stuff.is_valid()
         ? name_stuff_t::make(a_namespace, valid_ref_t< name_stuff_t>(a_basename.my_stuff))
         : ref_t<name_stuff_t>())
   {
   }

   name_t::name_t(const ref_t<name_stuff_t>& stuff)
      : my_stuff(stuff)
   {
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Name data access.

   str_ptr_t name_t::to_text() const
   {
      return my_stuff.is_valid()
         ? valid_ref_t<name_stuff_t>(my_stuff)->my_label.c_str()
         : L"";
   }

   namespace
   {
      const valid_ref_t<namespace_t>& get_invalid_namespace()
      {
         static valid_ref_t<namespace_t> invalid_ns = namespace_t::make();
         return invalid_ns;
      }
   }

   // Retrieve the name namespace.
   const valid_ref_t<namespace_t>& name_t::get_namespace() const
   {
      return my_stuff.is_valid()
         ? valid_ref_t<name_stuff_t>(my_stuff)->my_namespace
         : get_invalid_namespace();
   }
}
