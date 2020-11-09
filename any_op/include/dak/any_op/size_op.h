#pragma once

#ifndef DAK_ANY_OP_SIZE_OP_H
#define DAK_ANY_OP_SIZE_OP_H

#include <dak/any_op/unary_op.h>

namespace dak::any_op
{

   //////////////////////////////////////////////////////////////////////////
   //
   // The size operation returns the size of a container type.
   //
   // That is, the number of elements it contains.

   struct size_op_t : unary_op_t<size_op_t>
   {
      static uint64_t call(const std::any& arg_a)
      {
         const std::any result = call_op(arg_a);
         if (result.has_value())
            return std::any_cast<uint64_t>(result);
         else
            return 0;
      }

      template<class A>
      static uint64_t call(const A& arg_a)
      {
         return call(std::make_any<A>());
      }

      // Note: pre-defined operations implementation are automatically registered,
      //       but these static variables do not get initialized by the testing framework.
      //       Tests need to explicitly call a function to trigger initialization.
      static void register_ops();
   };
}

#endif /* DAK_ANY_OP_SIZE_OP_H */
