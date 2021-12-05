#pragma once

#ifndef DAK_OBJECT_NAMESPACE_H
#define DAK_OBJECT_NAMESPACE_H

#include <dak/object/name_stuff.h>
#include <dak/object/edit_ref.h>
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
      //    parent_t: optional parent namespace of this namespace.
      //    names_t: the names kept directly in this namespace.

      using child_t = valid_ref_t<namespace_t>;
      using children_t = std::unordered_map<text_t, child_t>;
      using parent_t = weak_ref_t<namespace_t>;
      using names_t = std::unordered_map<text_t, valid_ref_t<name_stuff_t>>;

      DAK_OBJECT_REF_COUNTED(namespace_t);

      // Make a child ref-counted instance. If the label is empty, it is not added to the parent.
      static edit_ref_t<namespace_t> make(const edit_ref_t<namespace_t>& a_parent, str_ptr_t a_label);
      static edit_ref_t<namespace_t> make(const edit_ref_t<namespace_t>& a_parent, const text_t& a_label);

      // Destructor.
      ~namespace_t() = default;

      // Remove all names and child namespaces from this namespace.
      void clear() override;

      // Swap with another namespace.
      void swap(namespace_t& other);
      
      // Retrieves the namespace label.
      const text_t& to_text() const { return my_label; }

      // Retrieves the optional parent namespace.
      const parent_t& get_parent() const {return my_parent; }

      // Retrieve the children namespaces.
      const children_t& get_namespaces() const { return my_children; }

      // Add the given namespace as a child of this namespace.
      void add_namespace(const valid_ref_t<namespace_t>&);

      // Retrieves a child namespace in this namespace. May return an invalid reference.
      ref_t<namespace_t> get_namespace(str_ptr_t a_label) const;
      ref_t<namespace_t> get_namespace(const text_t& a_label) const;

      // Retrieves all names of this namespace.
      const names_t& get_names() const { return my_names; }

      // Retrieves a name in this namespace. May return an invalid name.
      name_t get_name(str_ptr_t a_label) const;
      name_t get_name(const text_t& a_label) const;

      // Searches a name in this namespace and its parents. May return an invalid name.
      name_t search_name(str_ptr_t a_label) const;
      name_t search_name(const text_t& a_label) const;

      // Comparison.
      auto operator <=>(const namespace_t&) const = default;

      // Modification in a transaction.
      edit_ref_t<namespace_t> modify(transaction_t&) const;

   protected:
      text_t      my_label;
      parent_t    my_parent;
      children_t  my_children;
      names_t     my_names;

      friend struct name_stuff_t;
   };

}

#endif /* DAK_OBJECT_NAMESPACE */
