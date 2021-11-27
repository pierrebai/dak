#include "dak/object/namespace.h"
#include "dak/object/name_stuff.h"

#include <mutex>

namespace dak::object
{
   namespace
   {
      str_ptr_t intern(const text_t& a_label)
      {
         static std::unordered_set<text_t> known_names;
         static std::mutex mutex;

         std::lock_guard lock(mutex);
         const auto iter = known_names.find(a_label);
         if (iter != known_names.end())
            return iter->c_str();

         auto iter_and_result = known_names.insert(a_label);
         return iter_and_result.first->c_str();
      }
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Makers and constructors.

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

   edit_ref_t<namespace_t> namespace_t::make(valid_ref_t<namespace_t>& other)
   {
      return edit_ref_t<namespace_t>(new namespace_t(other));
   }

   // Make a child ref-counted instance.
   edit_ref_t<namespace_t> namespace_t::make(str_ptr_t a_label, const parent_t& a_parent)
   {
      return a_label ? make(text_t(a_label), a_parent) : make();
   }

   edit_ref_t<namespace_t> namespace_t::make(const text_t& a_label, const parent_t& a_parent)
   {
      auto new_ns = edit_ref_t<namespace_t>(new namespace_t);
      if (a_label.size() > 0)
         a_parent->my_children.insert(std::pair(a_label, valid_ref_t<namespace_t>(new_ns)));
      return new_ns;
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Children namespace.

   ref_t<namespace_t> namespace_t::find_namespace(str_ptr_t a_label) const
   {
      if (!a_label)
         return ref_t<namespace_t>();
      return find_namespace(text_t(a_label));
   }

   ref_t<namespace_t> namespace_t::find_namespace(const text_t& a_label) const
   {
      const auto iter = my_children.find(a_label);
      if (iter == my_children.end())
         return ref_t<namespace_t>();

      return iter->second;
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Names.

   // Finds a name in this namespace. May return an invalid name.
   name_t namespace_t::find_name(str_ptr_t a_label) const
   {
      if (!a_label)
         return name_t();
      return find_name(text_t(a_label));
   }

   name_t namespace_t::find_name(const text_t& a_label) const
   {
      const auto iter = my_names.find(a_label);
      if (iter == my_names.end())
         return name_t();

      return iter->second;
   }
}
