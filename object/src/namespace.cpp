#include "dak/object/namespace.h"
#include "dak/object/name.h"
#include "dak/object/name_stuff.h"

#include <mutex>

namespace dak::object
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Makers.

   // Make a root ref-counted instance.
   edit_ref_t<namespace_t> namespace_t::make()
   {
      return edit_ref_t<namespace_t>(new namespace_t);
   }

   // Make a copy ref-counted instance.
   edit_ref_t<namespace_t> namespace_t::make(const namespace_t& other)
   {
      return edit_ref_t<namespace_t>(new namespace_t(other));
   }

   edit_ref_t<namespace_t> namespace_t::make(const valid_ref_t<namespace_t>& other)
   {
      return edit_ref_t<namespace_t>(new namespace_t(other));
   }

   // Make a child ref-counted instance.
   edit_ref_t<namespace_t> namespace_t::make(str_ptr_t a_label, const edit_ref_t<namespace_t>& a_parent)
   {
      return a_label ? make(text_t(a_label), a_parent) : make();
   }

   edit_ref_t<namespace_t> namespace_t::make(const text_t& a_label, const edit_ref_t<namespace_t>& a_parent)
   {
      auto new_ns = edit_ref_t<namespace_t>(new namespace_t);
      new_ns->my_label = a_label;
      new_ns->my_parent = a_parent;
      if (a_label.size() > 0)
         a_parent->add_namespace(new_ns);
      return new_ns;
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Clear and swap.

   void namespace_t::clear()
   {
      my_children.clear();
      my_names.clear();
      my_parent = ref_t<namespace_t>();
   }

   void namespace_t::swap(namespace_t& other)
   {
      my_label.swap(other.my_label);
      my_parent.swap(other.my_parent);
      my_children.swap(other.my_children);
      my_names.swap(other.my_names);
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Children namespace.

   void namespace_t::add_namespace(const valid_ref_t<namespace_t>& ns)
   {
      my_children.insert(std::pair(ns->to_text(), ns));
   }

   ref_t<namespace_t> namespace_t::get_namespace(str_ptr_t a_label) const
   {
      if (!a_label)
         return ref_t<namespace_t>();
      return get_namespace(text_t(a_label));
   }

   ref_t<namespace_t> namespace_t::get_namespace(const text_t& a_label) const
   {
      const auto iter = my_children.find(a_label);
      if (iter == my_children.end())
         return ref_t<namespace_t>();

      return iter->second;
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Names.

   // Retrieves a name in this namespace. May return an invalid name.
   name_t namespace_t::get_name(str_ptr_t a_label) const
   {
      if (!a_label)
         return name_t();
      return get_name(text_t(a_label));
   }

   name_t namespace_t::get_name(const text_t& a_label) const
   {
      const auto iter = my_names.find(a_label);
      if (iter == my_names.end())
         return name_t();

      return iter->second;
   }

   // Searches a name in this namespace and its parents. May return an invalid name.
   name_t namespace_t::search_name(str_ptr_t a_label) const
   {
      if (!a_label)
         return name_t();

      return search_name(text_t(a_label));
   }

   name_t namespace_t::search_name(const text_t& a_label) const
   {
      const namespace_t* current_ns = this;
      while (current_ns)
      {
         const name_t name = current_ns->get_name(a_label);
         if (name.is_valid())
            return name;

         auto parent = current_ns->get_parent();
         if (!parent.is_valid())
            break;

         current_ns = valid_ref_t(ref_t(parent));
      }

      return name_t();
   }
}
