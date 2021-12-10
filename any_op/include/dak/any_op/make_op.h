#pragma once

#ifndef DAK_ANY_OP_MAKE_OP_H
#define DAK_ANY_OP_MAKE_OP_H

#include <dak/any_op/op.h>

namespace dak::any_op
{
   //////////////////////////////////////////////////////////////////////////
   //
   // The make operation creates a value with default initialization.

   struct make_op_t : op_t<make_op_t>
   {
      // Note: pre-defined operations implementation are automatically registered,
      //       but these static variables do not get initialized by the testing framework.
      //       Tests need to explicitly call a function to trigger initialization.
      static void register_ops();
   };

   template<class T>
   inline any_t make()
   {
      any_t result = make_op_t::call<T>::op();
      if (result.has_value())
         return result;
      else
         return any_t();
   }

   inline any_t make(const std::type_info& arg_a)
   {
      any_t result = make_op_t::call_extra_any<void>::op(arg_a);
      if (result.has_value())
         return result;
      else
         return any_t();
   }
}

#endif /* DAK_ANY_OP_MAKE_OP_H */
