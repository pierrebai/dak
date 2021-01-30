#pragma once

#ifndef DAK_ANY_OP_TO_TEXT_OP_H
#define DAK_ANY_OP_TO_TEXT_OP_H

#include <dak/any_op/unary_op.h>

namespace dak::any_op
{

   //////////////////////////////////////////////////////////////////////////
   //
   // The to-text operation returns a textual representation of the type.

   struct to_text_op_t : unary_op_t<to_text_op_t>
   {
      text_t operator()(const std::any& arg_a) const
      {
         return call(arg_a);
      }

      template<class A>
      text_t operator()(const A& arg_a) const
      {
         return call<A>(arg_a);
      }

      static text_t call(const std::any& arg_a)
      {
         const std::any result = call_op(arg_a);
         if (result.has_value())
            return *std::any_cast<text_t>(&result);
         else
            return {};
      }

      template<class A>
      static text_t call(const A& arg_a)
      {
         return call(std::make_any<A>());
      }

      // Note: pre-defined operations implementation are automatically registered,
      //       but these static variables do not get initialized by the testing framework.
      //       Tests need to explicitly call a function to trigger initialization.
      static void register_ops();
   };

   extern const to_text_op_t to_text;
}

#endif /* DAK_ANY_OP_TO_TEXT_OP_H */
