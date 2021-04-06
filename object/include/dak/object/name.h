#pragma once

#ifndef DAK_OBJECT_NAME_H
#define DAK_OBJECT_NAME_H

#include <dak/utility/types.h>
#include <dak/object/ref_counted.h>
#include <dak/object/ref.h>

#include <map>

namespace dak::object
{
   USING_DAK_UTILITY_TYPES;

   //////////////////////////////////////////////////////////////////////////
   //
   // Name. Efficient when used as key.
   //
   // Names form a tree. In other words, a namespace.
   //
   // Anonymous names are roots, other are rooted (attached) to some root.
   //
   // Each root is different for comparison purpose, and so are identical names
   // with different roots. (i.e. root1/"foo" != root2/"foo".)

   struct name_t
   {
      typedef std::map<text_t, name_t> sub_names_t;
      typedef sub_names_t::iterator iterator;
      typedef sub_names_t::const_iterator const_iterator;

      // Name root constructor.
      name_t();

      // Rooted constructors.
      name_t(name_t& root, const text_t& a_label);
      name_t(name_t& root, str_ptr_t a_label);

      // Destructor.
      ~name_t();

      // Access rooted name.
      name_t operator/(const text_t& a_label);
      name_t operator/(str_ptr_t a_label);

      iterator begin();
      iterator end();
      const_iterator begin() const;
      const_iterator end() const;

      // Validity.
      bool is_valid() const;

      // Comparison methods.
      bool operator ==(const name_t&) const;
      bool operator !=(const name_t&) const;
      bool operator  <(const name_t&) const;
      bool operator <=(const name_t&) const;
      bool operator  >(const name_t&) const;
      bool operator >=(const name_t&) const;

      uint64_t hash() const;

   protected:
      struct rc_sub_names_t : ref_counted_t, sub_names_t
      {
         static ref_t<rc_sub_names_t> make();
         static ref_t<rc_sub_names_t> make(const rc_sub_names_t&);
      };

      // Internal constructor.
      name_t(rc_sub_names_t* d);

      ref_t<rc_sub_names_t> my_sub_names;

      friend struct element_t;
      friend struct dict_t;
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

#endif /* DAK_OBJECT_NAME */
