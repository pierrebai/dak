#pragma once

#ifndef DAK_OBJECT_NAMESPACE_H
#define DAK_OBJECT_NAMESPACE_H

#include <dak/object/name.h>
#include <dak/object/ref.h>
#include <dak/object/ref_counted.h>

#include <unordered_map>

namespace dak::object
{
   USING_DAK_UTILITY_TYPES;

   struct name_stuff_t;

   //////////////////////////////////////////////////////////////////////////
   //
   // Namespace. Hierarchical container of names.

   struct namespace_t : private ref_counted_t
   {
      // Various types used by the namespace:
      //
      //    child_t: a child namespace of this namespace.
      //    children_t: all children of this namespace.
      //    parent_t: parent namespace of this namespace.
      //    names_t: the names kept directly in this namespace.

      using child_t = valid_ref_t<namespace_t>;
      using children_t = std::unordered_map<text_t, child_t>;
      using parent_t = edit_ref_t<namespace_t>;
      using names_t = std::unordered_map<text_t, valid_ref_t<name_stuff_t>>;

      // Make a root ref-counted instance.
      static edit_ref_t<namespace_t> make();

      // Make a copy ref-counted instance.
      static edit_ref_t<namespace_t> make(const namespace_t&);
      static edit_ref_t<namespace_t> make(valid_ref_t<namespace_t>&);

      // Make a child ref-counted instance. If the label is empty, it is not added to the parent.
      static edit_ref_t<namespace_t> make(str_ptr_t a_label, const parent_t& a_parent);
      static edit_ref_t<namespace_t> make(const text_t& a_label, const parent_t& a_parent);

      // Root namespace constructor.
      namespace_t() = default;

      // Copy constructor.
      namespace_t(const namespace_t& other) = default;
      namespace_t(valid_ref_t<namespace_t>& other) : namespace_t(*other) {}

      // Destructor.
      ~namespace_t() = default;
      
      // Retrieve the children namespaces.
      const children_t& get_namespaces() const { return my_children; }

      // Finds a child namespace in this namespace. May return an invalid reference.
      ref_t<namespace_t> find_namespace(str_ptr_t a_label) const;
      ref_t<namespace_t> find_namespace(const text_t& a_label) const;

      // Retrieves all names of this namespace.
      const names_t& get_names() const { return my_names; }

      // Finds a name in this namespace. May return an invalid name.
      name_t find_name(str_ptr_t a_label) const;
      name_t find_name(const text_t& a_label) const;

      // Comparison.
      auto operator <=>(const namespace_t&) const = default;

   protected:
      children_t my_children;
      names_t my_names;

      friend struct ref_t<namespace_t>;
      friend struct valid_ref_t<namespace_t>;
      friend struct edit_ref_t<namespace_t>;
      friend struct name_stuff_t;
   };

}

#endif /* DAK_OBJECT_NAMESPACE */
