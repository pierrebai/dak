#pragma once

#ifndef DAK_ANY_OP_IS_REAL_OP_H
#define DAK_ANY_OP_IS_REAL_OP_H

#include <dak/any_op/op.h>

namespace dak::any_op
{

   //////////////////////////////////////////////////////////////////////////
   //
   // The is-real operation returns true if a the type is real.

   struct is_real_op_t : op_t<is_real_op_t>
   {
      // Note: pre-defined operations implementation are automatically registered,
      //       but these static variables do not get initialized by the testing framework.
      //       Tests need to explicitly call a function to trigger initialization.
      static void register_ops();
   };

   template<class T>
   inline bool is_real()
   {
      any_t result = is_real_op_t::call<T>::op();
      if (result.has_value())
         return std::any_cast<bool>(result);
      else
         return false;
   }

   inline bool is_real(const std::type_info& arg_a)
   {
      any_t result = is_real_op_t::call_extra_any<void>::op(arg_a);
      if (result.has_value())
         return std::any_cast<bool>(result);
      else
         return false;
   }

}

#endif /* DAK_ANY_OP_IS_REAL_OP_H */
