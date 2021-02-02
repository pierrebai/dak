#pragma once

#ifndef DAK_ANY_OP_TO_TEXT_OP_H
#define DAK_ANY_OP_TO_TEXT_OP_H

#include <dak/any_op/op.h>

namespace dak::any_op
{

   //////////////////////////////////////////////////////////////////////////
   //
   // The to-text operation returns a textual representation of the type.

   struct to_text_op_t : op_t<to_text_op_t>
   {
      // Note: pre-defined operations implementation are automatically registered,
      //       but these static variables do not get initialized by the testing framework.
      //       Tests need to explicitly call a function to trigger initialization.
      static void register_ops();
   };

   inline text_t to_text(const std::any& arg_a)
   {
      const std::any result = to_text_op_t::call_any<>::op(arg_a);
      if (result.has_value())
         return *std::any_cast<text_t>(&result);
      else
         return {};
   }

   template<class A>
   inline text_t to_text(const A& arg_a)
   {
      const std::any result = to_text_op_t::call<>::op(arg_a);
      if (result.has_value())
         return *std::any_cast<text_t>(&result);
      else
         return {};
   }

}

#endif /* DAK_ANY_OP_TO_TEXT_OP_H */
