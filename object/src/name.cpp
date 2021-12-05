#include "dak/object/name.h"
#include "dak/object/transaction.h"
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
      if (!is_valid())
         return other.is_valid() ? std::strong_ordering::less : std::strong_ordering::equal;

      if (!other.is_valid())
         return std::strong_ordering::greater;

      return *valid_ref_t<name_stuff_t>(my_stuff) <=> *valid_ref_t<name_stuff_t>(other.my_stuff);
   }

   bool name_t::operator ==(const name_t& other) const
   {
      if (!is_valid())
         return !other.is_valid();

      if (!other.is_valid())
         return false;

      return *valid_ref_t<name_stuff_t>(my_stuff) == *valid_ref_t<name_stuff_t>(other.my_stuff);
   }

   uint64_t name_t::hash() const
   {
      if (my_stuff.is_null())
         return 0;

      return valid_ref_t<name_stuff_t>(my_stuff)->hash();
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Name text conversion.

   str_ptr_t name_t::to_text() const
   {
      return my_stuff.is_valid()
         ? valid_ref_t<name_stuff_t>(my_stuff)->my_label.c_str()
         : L"";
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Name namespace.

   // Retrieve the name namespace.
   const weak_ref_t<namespace_t>& name_t::get_namespace() const
   {
      if (!my_stuff.is_valid())
      {
         static const weak_ref_t<namespace_t> empty;
         return empty;
      }

      return valid_ref_t<name_stuff_t>(my_stuff)->my_namespace;
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

      valid_ref_t<name_stuff_t> valid_mt(a_metadata.my_stuff);
      edit_ref_t<name_stuff_t> edit_my_stuff(my_stuff, tr);
      edit_my_stuff->my_metadata.insert(valid_mt);
   }

   // Removes metadata to the name.
   void name_t::remove_metadata(const name_t& a_metadata, transaction_t& tr)
   {
      if (!is_valid())
         return;

      if (!a_metadata.is_valid())
         return;

      valid_ref_t<name_stuff_t> valid_mt(a_metadata.my_stuff);
      edit_ref_t<name_stuff_t> edit_my_stuff(my_stuff, tr);
      edit_my_stuff->my_metadata.erase(valid_mt);
   }

   // Removes metadata to the name.
   bool name_t::has_metadata(const name_t& a_metadata) const
   {
      if (!is_valid())
         return false;

      if (!a_metadata.is_valid())
         return false;

      valid_ref_t<name_stuff_t> valid_mt(a_metadata.my_stuff);
      return valid_ref_t<name_stuff_t>(my_stuff)->my_metadata.contains(valid_mt);
   }

   namespace
   {
      const name_t::metadata_t& get_invalid_metadata()
      {
         static name_t::metadata_t invalid_metadata;
         return invalid_metadata;
      }
   }

   // Retrieves all metadata.
   const name_t::metadata_t& name_t::get_metadata() const
   {
      if (my_stuff.is_valid())
         return valid_ref_t<name_stuff_t>(my_stuff)->my_metadata;
      else
         return get_invalid_metadata();
   }
}
