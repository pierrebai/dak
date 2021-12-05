#include "dak/object/name_stuff.h"

namespace dak::object
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Name internal base stuff.
   //
   // Keep things to compare two basenames.

   name_stuff_base_t::name_stuff_base_t(weak_ref_t<namespace_t> a_namespace, const text_t& a_label)
      : my_label(a_label)
      , my_namespace(a_namespace)
   {
   }


   //////////////////////////////////////////////////////////////////////////
   //
   // Name stuff constructors.

   name_stuff_t::name_stuff_t(const edit_ref_t<namespace_t>& a_namespace, const text_t& a_label)
      : name_stuff_base_t(a_namespace, a_label)
   {
      a_namespace->my_names.insert_or_assign(my_label, valid_ref_t<name_stuff_t>(this));
   }

   // Constructor for a derived name of the given name, in the given namespace.
   name_stuff_t::name_stuff_t(const edit_ref_t<namespace_t>& a_namespace, const valid_ref_t<name_stuff_t>& a_basename)
      : name_stuff_base_t(a_namespace, a_basename->my_label)
      , my_basename(a_basename)
   {
      a_namespace->my_names.insert_or_assign(my_label, valid_ref_t<name_stuff_t>(this));
   }

   edit_ref_t<name_stuff_t> name_stuff_t::make(const edit_ref_t<namespace_t>& a_namespace, const text_t& a_label)
   {
      return edit_ref_t<name_stuff_t>(new name_stuff_t(a_namespace, a_label));
   }

   // Make a new derived name of the given name, in the given namespace.
   edit_ref_t<name_stuff_t> name_stuff_t::make(const edit_ref_t<namespace_t>& a_namespace, const valid_ref_t<name_stuff_t>& a_basename)
   {
      return edit_ref_t<name_stuff_t>(new name_stuff_t(a_namespace, a_basename));
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Swap with another name stuff.

   void name_stuff_t::clear()
   {
      my_label.clear();
      my_namespace = ref_t<namespace_t>();
      my_basename = ref_t<name_stuff_t>();
      my_metadata.clear();

   }

   void name_stuff_t::swap(name_stuff_t& other)
   {
      my_label.swap(other.my_label);
      my_namespace.swap(other.my_namespace);
      my_basename.swap(other.my_basename);
      my_metadata.swap(other.my_metadata);
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Comparison and hash.

   const name_stuff_base_t& name_stuff_t::get_basename() const
   {
      const name_stuff_t* n = this;
      while (n->my_basename.is_valid())
         n = valid_ref_t<name_stuff_t>(n->my_basename);
      return *n;
   }

   std::strong_ordering name_stuff_t::operator <=>(const name_stuff_t& other) const
   {
      const name_stuff_base_t* this_n = &get_basename();
      const name_stuff_base_t* other_n = &other.get_basename();

      return this_n <=> other_n;
   }

   bool name_stuff_t::operator ==(const name_stuff_t& other) const
   {
      const name_stuff_base_t* this_n = &get_basename();
      const name_stuff_base_t* other_n = &other.get_basename();

      return this_n == other_n;
   }

   uint64_t name_stuff_t::hash() const
   {
      return reinterpret_cast<uint64_t>(&get_basename());
   }

}
