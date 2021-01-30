#pragma once

#ifndef DAK_ANY_OP_CONVERT_OP_H
#define DAK_ANY_OP_CONVERT_OP_H

#include <dak/any_op/unary_op.h>

namespace dak::any_op
{
   //////////////////////////////////////////////////////////////////////////
   //
   // The convert operation converts a a type to another.

   struct convert_op_t : unary_op_t<convert_op_t>
   {
      template<class TO>
      static TO call(const std::any& arg_a)
      {
         const std::any result = call_op<TO>(arg_a);
         if (result.has_value())
            return std::any_cast<TO>(result);
         else
            return TO {};
      }

      template<class TO, class FROM>
      static TO call(const FROM& arg_a)
      {
         const std::any result = call_op<TO>(arg_a);
         if (result.has_value())
            return std::any_cast<TO>(result);
         else
            return TO {};
      }

      // Note: pre-defined operations implementation are automatically registered,
      //       but these static variables do not get initialized by the testing framework.
      //       Tests need to explicitly call a function to trigger initialization.
      static void register_ops();
   };
}

#endif /* DAK_ANY_OP_CONVERT_OP_H */
