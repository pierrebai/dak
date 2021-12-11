#pragma once

#ifndef DAK_OBJECT_NAME_H
#define DAK_OBJECT_NAME_H

#include <dak/object/name_stuff.h>
#include <dak/utility/types.h>
#include <dak/object/edit_ref.h>

namespace dak::object
{
   USING_DAK_UTILITY_TYPES;

   struct name_stuff_t;
   struct namespace_t;
   struct transaction_t;

   //////////////////////////////////////////////////////////////////////////
   //
   // Name. Efficient when used as key.

   struct name_t
   {
      // Metadata on the name to allow customizing behaviour based on their presence.
      using metadata_t = name_stuff_t::metadata_t;

      // Default constructor for an invalid name.
      name_t();

      // Constructor for a name with the given label in the given namespace.
      name_t(const edit_ref_t<namespace_t>& a_namespace, str_ptr_t a_label);
      name_t(const edit_ref_t<namespace_t>& a_namespace, const text_t& a_label);

      // Constructor for a derived name of the given name, in the given namespace.
      name_t(const edit_ref_t<namespace_t>& a_namespace, const name_t& a_basename);

      // Constructor from name internal stuff.
      name_t(const ref_t<name_stuff_t>& stuff);
      name_t(const valid_ref_t<name_stuff_t>& stuff);
      name_t(const edit_ref_t<name_stuff_t>& stuff);

      // Destructor.
      ~name_t() = default;

      // Return the label of the name.
      const text_t& to_text() const;

      // Retrieves the name namespace, if any.
      const weak_ref_t<namespace_t>& get_namespace() const;

      // Adds metadata to the name.
      void add_metadata(const name_t& a_metadata, transaction_t& tr);

      // Removes metadata to the name.
      void remove_metadata(const name_t& a_metadata, transaction_t& tr);

      // Removes metadata to the name.
      bool has_metadata(const name_t& a_metadata) const;

      // Retrieves all metadata.
      const metadata_t& get_metadata() const;

      // Validity.
      bool is_valid() const { return my_stuff != get_invalid_name_stuff(); }

      // Comparison and hash.
      std::strong_ordering operator <=>(const name_t&) const;
      bool operator ==(const name_t&) const;
      uint64_t hash() const;

   protected:
      static const valid_ref_t<name_stuff_t> get_invalid_name_stuff();

      valid_ref_t<name_stuff_t> my_stuff;

      friend struct value_t;
   };

   //////////////////////////////////////////////////////////////////////////
   //
   // Hashes the name.

   struct name_hasher_t
   {
      inline uint64_t operator ()(const name_t& a_name) const
      {
         return a_name.hash();
      }
   };
}

namespace std
{
   template <>
   struct hash<dak::object::name_t>
   {
      size_t operator()(const dak::object::name_t& n) const
      {
         return static_cast<size_t>(n.hash());
      }
   };
}

#endif /* DAK_OBJECT_NAME */
