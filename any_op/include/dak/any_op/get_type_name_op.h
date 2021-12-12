#pragma once

#ifndef DAK_ANY_OP_GET_TYPE_NAME_OP_H
#define DAK_ANY_OP_GET_TYPE_NAME_OP_H

#include <dak/any_op/op.h>
#include <dak/any_op/as_op.h>

namespace dak::any_op
{
   //////////////////////////////////////////////////////////////////////////
   //
   // The get_type_name operation returns the (hopefully) unique name
   // of a type.

   struct get_type_name_op_t : op_t<get_type_name_op_t>
   {
      // Note: pre-defined operations implementation are automatically registered,
      //       but these static variables do not get initialized by the testing framework.
      //       Tests need to explicitly call a function to trigger initialization.
      static void register_ops();
   };

   text_t get_type_name(const std::type_info& arg_a);

   inline text_t get_type_name(const any_t& arg_a)
   {
      return get_type_name(arg_a.type());
   }

   template<class T>
   inline text_t get_type_name()
   {
      return get_type_name(typeid(T));
   }

}

#endif /* DAK_ANY_OP_GET_TYPE_NAME_OP_H */
