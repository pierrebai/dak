#include <dak/object/name_stuff.h>

#include <stdexcept>

namespace dak::object
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Name internal base stuff.
   //
   // Keep things to compare two synonyms.

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
      if (!a_namespace->my_names.insert(std::make_pair(my_label, valid_ref_t<name_stuff_t>(this))).second)
         throw std::runtime_error("cannot create sanem name twice");
   }

   // Constructor for a derived name of the given name, in the given namespace.
   name_stuff_t::name_stuff_t(const edit_ref_t<namespace_t>& a_namespace, const valid_ref_t<name_stuff_t>& a_synonym)
      : name_stuff_base_t(a_namespace, a_synonym->my_label)
      , my_synonym(a_synonym)
   {
      if (!a_namespace->my_names.insert(std::make_pair(my_label, valid_ref_t<name_stuff_t>(this))).second)
         throw std::runtime_error("cannot create sanem name twice");
   }

   edit_ref_t<name_stuff_t> name_stuff_t::make(const edit_ref_t<namespace_t>& a_namespace, const text_t& a_label)
   {
      return edit_ref_t<name_stuff_t>(new name_stuff_t(a_namespace, a_label));
   }

   // Make a new derived name of the given name, in the given namespace.
   edit_ref_t<name_stuff_t> name_stuff_t::make_synonym(const edit_ref_t<namespace_t>& a_namespace, const valid_ref_t<name_stuff_t>& a_synonym)
   {
      return edit_ref_t<name_stuff_t>(new name_stuff_t(a_namespace, a_synonym));
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Swap with another name stuff.

   void name_stuff_t::clear()
   {
      my_label.clear();
      my_namespace = ref_t<namespace_t>();
      my_synonym = ref_t<name_stuff_t>();
      my_metadata.clear();

   }

   void name_stuff_t::swap(name_stuff_t& other)
   {
      my_label.swap(other.my_label);
      my_namespace.swap(other.my_namespace);
      my_synonym.swap(other.my_synonym);
      my_metadata.swap(other.my_metadata);
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Synonym.

   const name_stuff_base_t& name_stuff_t::get_synonym() const
   {
      const name_stuff_t* n = this;
      while (n->my_synonym.is_valid())
         n = valid_ref_t<name_stuff_t>(n->my_synonym);
      return *n;
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Comparison and hash.

   std::strong_ordering name_stuff_t::operator <=>(const name_stuff_t& other) const
   {
      const name_stuff_base_t* this_n = &get_synonym();
      const name_stuff_base_t* other_n = &other.get_synonym();

      return this_n <=> other_n;
   }

   bool name_stuff_t::operator ==(const name_stuff_t& other) const
   {
      const name_stuff_base_t* this_n = &get_synonym();
      const name_stuff_base_t* other_n = &other.get_synonym();

      return this_n == other_n;
   }

   uint64_t name_stuff_t::hash() const
   {
      return reinterpret_cast<uint64_t>(&get_synonym());
   }

}
