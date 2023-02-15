#pragma once

#ifndef DAK_ANY_OP_CONSTRUCT_OP_H
#define DAK_ANY_OP_CONSTRUCT_OP_H

#include <dak/any_op/op.h>
#include <dak/any_op/as_op.h>

namespace dak::any_op
{
   //////////////////////////////////////////////////////////////////////////
   //
   // The make operation creates a value with default initialization.
   //
   // Note: no templated version is provided since when you already have
   //       the type it is simpler to call the constructor directly!

   struct construct_op_t : op_t<construct_op_t>
   {
      // Note: pre-defined operations implementation are automatically registered,
      //       but these static variables do not get initialized by the testing framework.
      //       Tests need to explicitly call a function to trigger initialization.
      static void register_ops();
   };

   inline any_t construct(const std::type_info& arg_a)
   {
      return construct_op_t::call_any_with_types<void>::op(arg_a);
   }
}

#endif /* DAK_ANY_OP_CONSTRUCT_OP_H */
