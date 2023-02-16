#include <dak/object/name.h>
#include <dak/object/transaction.h>
#include <dak/object/name_stuff.h>

namespace dak::object
{
   const valid_ref_t<name_stuff_t> name_t::get_invalid_name_stuff()
   {
      static edit_ref_t<namespace_t> invalid_ns = namespace_t::make();
      static valid_ref_t<name_stuff_t> invalid = name_stuff_t::make(invalid_ns, L"");
      return invalid;
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Constructors.

   name_t::name_t()
      : my_stuff(get_invalid_name_stuff())
   {
   }

   name_t::name_t(const edit_ref_t<namespace_t>& a_namespace, str_ptr_t a_label)
      : my_stuff(name_stuff_t::make(a_namespace, a_label))
   {
   }

   name_t::name_t(const edit_ref_t<namespace_t>& a_namespace, const text_t& a_label)
      : my_stuff(name_stuff_t::make(a_namespace, a_label))
   {
   }

   name_t::name_t(const edit_ref_t<namespace_t>& a_namespace, const name_t& a_synonym)
      : my_stuff(a_synonym.is_valid()
         ? valid_ref_t<name_stuff_t>(name_stuff_t::make_synonym(a_namespace, a_synonym.my_stuff))
         : a_synonym.my_stuff)
   {
   }

   name_t::name_t(const ref_t<name_stuff_t>& stuff)
      : my_stuff(stuff)
   {
   }

   name_t::name_t(const valid_ref_t<name_stuff_t>& stuff)
      : my_stuff(stuff)
   {
   }

   name_t::name_t(const edit_ref_t<name_stuff_t>& stuff)
      : my_stuff(stuff)
   {
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Name comparison and hash.

   std::strong_ordering name_t::operator <=>(const name_t& other) const
   {
      // Compare dereferenced name stuff so that its comparison op is used.
      return *my_stuff <=> *other.my_stuff;
   }

   bool name_t::operator ==(const name_t& other) const
   {
      // Compare dereferenced name stuff so that its comparison op is used.
      return *my_stuff == *other.my_stuff;
   }

   uint64_t name_t::hash() const
   {
      return my_stuff->hash();
   }


   //////////////////////////////////////////////////////////////////////////
   //
   // Name text conversion.

   const text_t& name_t::to_text() const
   {
      return my_stuff->my_label;
   }

   str_ptr_t name_t::to_str_ptr() const
   {
      return to_text().c_str();
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Name namespace.

   // Retrieve the name namespace.
   const weak_ref_t<namespace_t>& name_t::get_namespace() const
   {
      return my_stuff->my_namespace;
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Name metadata.

   // Adds metadata to the name.
   void name_t::add_metadata(const name_t& a_metadata, transaction_t& tr)
   {
      if (!is_valid())
         return;

      if (!a_metadata.is_valid())
         return;

      edit_ref_t<name_stuff_t> edit_my_stuff(my_stuff, tr);
      edit_my_stuff->my_metadata.insert(a_metadata.my_stuff);
   }

   // Removes metadata to the name.
   void name_t::remove_metadata(const name_t& a_metadata, transaction_t& tr)
   {
      if (!is_valid())
         return;

      if (!a_metadata.is_valid())
         return;

      edit_ref_t<name_stuff_t> edit_my_stuff(my_stuff, tr);
      edit_my_stuff->my_metadata.erase(a_metadata.my_stuff);
   }

   // Removes metadata to the name.
   bool name_t::has_metadata(const name_t& a_metadata) const
   {
      if (!is_valid())
         return false;

      if (!a_metadata.is_valid())
         return false;

      return my_stuff->my_metadata.contains(a_metadata.my_stuff);
   }

   // Retrieves all metadata.
   const name_t::metadata_t& name_t::get_metadata() const
   {
      return my_stuff->my_metadata;
   }
}
