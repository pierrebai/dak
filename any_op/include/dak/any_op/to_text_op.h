#pragma once

#ifndef DAK_ANY_OP_TO_TEXT_OP_H
#define DAK_ANY_OP_TO_TEXT_OP_H

#include <dak/any_op/op.h>
#include <dak/any_op/as_op.h>

namespace dak::any_op
{

   //////////////////////////////////////////////////////////////////////////
   //
   // The to-text operation returns a textual representation of the value.

   struct to_text_op_t : op_t<to_text_op_t>
   {
      // Note: pre-defined operations implementation are automatically registered,
      //       but these static variables do not get initialized by the testing framework.
      //       Tests need to explicitly call a function to trigger initialization.
      static void register_ops();
   };

   text_t to_text(const any_t& arg_a);

   template<class A>
   inline text_t to_text(const A& arg_a)
   {
      return to_text(any_t(arg_a));
   }

}

#endif /* DAK_ANY_OP_TO_TEXT_OP_H */
