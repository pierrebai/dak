#pragma once

#ifndef DAK_ANY_OP_GET_TYPE_INFO_OP_H
#define DAK_ANY_OP_GET_TYPE_INFO_OP_H

#include <dak/any_op/op.h>

namespace dak::any_op
{
   //////////////////////////////////////////////////////////////////////////
   //
   // The get_type_info operation returns the std::type_info
   // of a named type.
   //
   // Returns the type_info of void when a type name is unknown.
   //
   // Unlike most operations, it does not derive from op_t, but is a simple
   // free function and a registry of type names to type info.
   //
   // The registry of type info must be filled in parralel to imnplementing
   // the get_type_name_op_t operation and the construct_op_t operation so
   // that the ref streaming operation work. (See the implementation of
   // ref_ostream_t and ref_istream_t.)

   const std::type_info& get_type_info(const text_t& a_type_name);

   void add_type_info(const text_t& a_type_name, const std::type_info&);
   void remove_type_info(const text_t& a_type_name);
}

#endif /* DAK_ANY_OP_GET_TYPE_INFO_OP_H */
