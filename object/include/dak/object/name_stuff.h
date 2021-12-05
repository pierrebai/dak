#pragma once

#ifndef DAK_OBJECT_NAME_PRIVATE_H
#define DAK_OBJECT_NAME_PRIVATE_H

#include <dak/object/namespace.h>
#include <dak/object/edit_ref.h>

#include <unordered_set>

namespace dak::object
{
   USING_DAK_UTILITY_TYPES;

   struct element_t;
   struct name_t;
   struct namespace_t;

   //////////////////////////////////////////////////////////////////////////
   //
   // Name internal stuff. Internal information about a single name.

   struct name_stuff_t : private ref_counted_t
   {
      // Metadata on the name to allow customizing behaviour based on their presence.
      using metadata_t = std::unordered_set<valid_ref_t<name_stuff_t>>;

      // Optional basename of the name: same name, but different metadata.
      using basename_t = ref_t<name_stuff_t>;

      // Make a new name with the given label in the given namespace.
      static edit_ref_t<name_stuff_t> make(const edit_ref_t<namespace_t>& a_namespace, const text_t& a_label);

      // Make a new derived name of the given name, in the same namespace.
      static edit_ref_t<name_stuff_t> make(const valid_ref_t<name_stuff_t>& a_basename);

      // Make a new derived name of the given name, in the given namespace.
      static edit_ref_t<name_stuff_t> make(const edit_ref_t<namespace_t>& a_namespace, const valid_ref_t<name_stuff_t>& a_basename);

      // Constructor for a name with the given label in the given namespace.
      name_stuff_t(const edit_ref_t<namespace_t>& a_namespace, const text_t& a_label);

      // Constructor for a derived name of the given name, in the same namespace.
      name_stuff_t(const valid_ref_t<name_stuff_t>& a_basename);

      // Constructor for a derived name of the given name, in the given namespace.
      name_stuff_t(const edit_ref_t<namespace_t>& a_namespace, const valid_ref_t<name_stuff_t>& a_basename);

      // Copy constructor.
      name_stuff_t(const name_stuff_t& other) = default;

      // Swap with another name stuff.
      void swap(name_stuff_t& other);

      // Reset the name stuff.
      void clear() override;

      // Comparison and hash.
      auto operator <=>(const name_stuff_t& other) const;
      uint64_t hash() const;

   private:
      text_t my_label;
      weak_ref_t<namespace_t> my_namespace;
      basename_t my_basename;
      metadata_t my_metadata;

      friend struct ref_t<name_stuff_t>;
      friend struct valid_ref_t<name_stuff_t>;
      friend struct edit_ref_t<name_stuff_t>;
      friend struct weak_ref_t<name_stuff_t>;
      friend struct ref_base_t;
      friend struct name_t;
      friend struct element_t;
      friend struct transaction_t;
   };
}

#endif /* DAK_OBJECT_NAME */
