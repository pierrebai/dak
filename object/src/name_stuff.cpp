#include "dak/object/name_stuff.h"

namespace dak::object
{
   name_stuff_t::name_stuff_t(const edit_ref_t<namespace_t>& a_namespace, const text_t& a_label)
      : my_label(a_label)
      , my_namespace(a_namespace)
   {
      a_namespace->my_names.insert(std::pair(my_label, valid_ref_t<name_stuff_t>(this)));
   }

   // Constructor for a derived name of the given name, in the same namespace.
   name_stuff_t::name_stuff_t(const valid_ref_t<name_stuff_t>& a_basename)
      : my_namespace(a_basename->my_namespace)
      , my_label(a_basename->my_label)
      , my_basename(a_basename)
   {
   }

   // Constructor for a derived name of the given name, in the given namespace.
   name_stuff_t::name_stuff_t(const edit_ref_t<namespace_t>& a_namespace, const valid_ref_t<name_stuff_t>& a_basename)
      : my_namespace(a_namespace)
      , my_label(a_basename->my_label)
      , my_basename(a_basename)
   {
      a_namespace->my_names.insert(std::pair(my_label, valid_ref_t<name_stuff_t>(this)));
   }

   edit_ref_t<name_stuff_t> name_stuff_t::make(const edit_ref_t<namespace_t>& a_namespace, const text_t& a_label)
   {
      return edit_ref_t<name_stuff_t>(new name_stuff_t(a_namespace, a_label));
   }

   // Make a new derived name of the given name, in the same namespace.
   edit_ref_t<name_stuff_t> name_stuff_t::make(const valid_ref_t<name_stuff_t>& a_basename)
   {
      return edit_ref_t<name_stuff_t>(new name_stuff_t(a_basename));
   }

   // Make a new derived name of the given name, in the given namespace.
   edit_ref_t<name_stuff_t> name_stuff_t::make(const edit_ref_t<namespace_t>& a_namespace, const valid_ref_t<name_stuff_t>& a_basename)
   {
      return edit_ref_t<name_stuff_t>(new name_stuff_t(a_namespace, a_basename));
   }

   auto name_stuff_t::operator <=>(const name_stuff_t& other) const
   {
      return my_label <=> other.my_label;
   }

   uint64_t name_stuff_t::hash() const
   {
      const name_stuff_t* n = this;
      while (n->my_basename.is_valid())
         n = valid_ref_t<name_stuff_t>(n->my_basename);

      return reinterpret_cast<uint64_t>(n);
   }

}