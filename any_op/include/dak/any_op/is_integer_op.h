#pragma once

#ifndef DAK_ANY_OP_IS_INTEGER_OP_H
#define DAK_ANY_OP_IS_INTEGER_OP_H

#include <dak/any_op/op.h>
#include <dak/any_op/as_op.h>

namespace dak::any_op
{

   //////////////////////////////////////////////////////////////////////////
   //
   // The is-integer operation returns true if a the type is integer.

   struct is_integer_op_t : op_t<is_integer_op_t>
   {
      // Note: pre-defined operations implementation are automatically registered,
      //       but these static variables do not get initialized by the testing framework.
      //       Tests need to explicitly call a function to trigger initialization.
      static void register_ops();
   };

   bool is_integer(const std::type_info& arg_a);

   template<class T>
   inline bool is_integer()
   {
      return is_integer(typeid(T));
   }
}

#endif /* DAK_ANY_OP_IS_INTEGER_OP_H */
