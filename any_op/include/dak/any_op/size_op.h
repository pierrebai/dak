#pragma once

#ifndef DAK_ANY_OP_SIZE_OP_H
#define DAK_ANY_OP_SIZE_OP_H

#include <dak/any_op/op.h>

namespace dak::any_op
{

   //////////////////////////////////////////////////////////////////////////
   //
   // The size operation returns the size of a container type.
   //
   // That is, the number of elements it contains.

   struct size_op_t : op_t<size_op_t>
   {
      // Note: pre-defined operations implementation are automatically registered,
      //       but these static variables do not get initialized by the testing framework.
      //       Tests need to explicitly call a function to trigger initialization.
      static void register_ops();
   };

   inline uint64_t size(const std::any& arg_a)
   {
      const std::any result = size_op_t::call_any<>::op(arg_a);
      if (result.has_value())
         return std::any_cast<uint64_t>(result);
      else
         return 0;
   }

   template<class A>
   inline uint64_t size(const A& arg_a)
   {
      const std::any result = size_op_t::call<>::op(arg_a);
      if (result.has_value())
         return std::any_cast<uint64_t>(result);
      else
         return 0;
   }

}

#endif /* DAK_ANY_OP_SIZE_OP_H */
