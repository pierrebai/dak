#pragma once

#ifndef DAK_ANY_OP_IS_UNSIGNED_OP_H
#define DAK_ANY_OP_IS_UNSIGNED_OP_H

#include <dak/any_op/op.h>
#include <dak/any_op/as_op.h>

namespace dak::any_op
{

   //////////////////////////////////////////////////////////////////////////
   //
   // The is-unsigned operation returns true if a the type is unsigned.

   struct is_unsigned_op_t : op_t<is_unsigned_op_t>
   {
      // Note: pre-defined operations implementation are automatically registered,
      //       but these static variables do not get initialized by the testing framework.
      //       Tests need to explicitly call a function to trigger initialization.
      static void register_ops();
   };

   template<class T>
   inline bool is_unsigned()
   {
      any_t result = is_unsigned_op_t::call<T>::op();
      return as<bool>(result);
   }

   inline bool is_unsigned(const std::type_info& arg_a)
   {
      any_t result = is_unsigned_op_t::call_extra_any<void>::op(arg_a);
      return as<bool>(result);
   }

}

#endif /* DAK_ANY_OP_IS_UNSIGNED_OP_H */
