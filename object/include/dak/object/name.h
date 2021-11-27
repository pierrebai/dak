#pragma once

#ifndef DAK_OBJECT_NAME_H
#define DAK_OBJECT_NAME_H

#include <dak/utility/types.h>
#include <dak/object/ref.h>

namespace dak::object
{
   USING_DAK_UTILITY_TYPES;

   struct name_stuff_t;
   struct namespace_t;

   //////////////////////////////////////////////////////////////////////////
   //
   // Name. Efficient when used as key.

   struct name_t
   {
      // Default constructor for an invalid name.
      name_t() = default;

      // Constructor for a name with the given label in the given namespace.
      name_t(const edit_ref_t<namespace_t>& a_namespace, str_ptr_t a_label);
      name_t(const edit_ref_t<namespace_t>& a_namespace, const text_t& a_label);

      // Constructor for a derived name of the given name, in the given namespace.
      name_t(const edit_ref_t<namespace_t>& a_namespace, const name_t& a_basename);

      // Constructor from name internal stuff.
      name_t(const ref_t<name_stuff_t>& stuff);

      // Destructor.
      ~name_t() = default;

      // Return the text of the name.
      str_ptr_t to_text() const;

      // Validity.
      bool is_valid() const { return my_stuff.is_valid(); }

      // Comparison.
      auto operator <=>(const name_t&) const = default;

      uint64_t hash() const { return my_stuff.hash(); }

   protected:
      ref_t<name_stuff_t> my_stuff;

      friend struct element_t;
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
