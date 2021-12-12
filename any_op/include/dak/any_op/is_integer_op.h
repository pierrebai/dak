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

   template<class T>
   inline bool is_integer()
   {
      any_t result = is_integer_op_t::call<T>::op();
      return as<bool>(result);
   }

   inline bool is_integer(const std::type_info& arg_a)
   {
      any_t result = is_integer_op_t::call_extra_any<void>::op(arg_a);
      return as<bool>(result);
   }

}

#endif /* DAK_ANY_OP_IS_INTEGER_OP_H */
