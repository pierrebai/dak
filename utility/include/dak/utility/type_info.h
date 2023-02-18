#pragma once

#ifndef DAK_UTILITY_TYPE_INFO_H
#define DAK_UTILITY_TYPE_INFO_H

#include <dak/utility/types.h>


namespace dak::utility
{
   //////////////////////////////////////////////////////////////////////////
   //
   // The get_type_info function finds the type_info_t of a type by its
   // textual name.
   //
   // Returns the type_info_t of void when a type name is unknown.
   //
   // The registry of type info must be filled in parralel to imnplementing
   // the get_type_name_op_t operation and the construct_op_t operation so
   // that the ref streaming operation work. (See the implementation of
   // ref_ostream_t and ref_istream_t.)
   //
   // In the future, we may record more information about a type, like
   // its supertypes or other useful information.

   template <class T>
   const type_info_t& type_info_of() { return typeid(T); }

   const type_info_t& get_type_info(const text_t& a_type_name);

   text_t get_type_name(const type_info_t& a_type_info);
   inline text_t get_type_name(const any_t& a_value) { return get_type_name(a_value.type()); }
   template <class T>
   text_t get_type_name() { return get_type_name(typeid(T)); }

   void add_type_info(const text_t& a_type_name, const type_info_t&);
   void remove_type_info(const text_t& a_type_name);
}

#endif /* DAK_UTILITY_TYPE_INFO_H */
