#pragma once

#ifndef DAK_ANY_OP_SIZE_OP_H
#define DAK_ANY_OP_SIZE_OP_H

#include <dak/any_op/op.h>
#include <dak/any_op/as_op.h>

namespace dak::any_op
{

   //////////////////////////////////////////////////////////////////////////
   //
   // The size operation returns the size of a container value.
   //
   // That is, the number of values it contains.
   //
   // Return zero if the value is not a known container.

   struct size_op_t : op_t<size_op_t>
   {
      // Note: pre-defined operations implementation are automatically registered,
      //       but these static variables do not get initialized by the testing framework.
      //       Tests need to explicitly call a function to trigger initialization.
      static void register_ops();
   };

   uint64_t size(const any_t& arg_a);

   template<class A>
   inline uint64_t size(const A& arg_a)
   {
      return size(any_t(arg_a));
   }

}

#endif /* DAK_ANY_OP_SIZE_OP_H */
