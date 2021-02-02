#pragma once

#ifndef DAK_ANY_OP_CONVERT_OP_H
#define DAK_ANY_OP_CONVERT_OP_H

#include <dak/any_op/op.h>

namespace dak::any_op
{
   //////////////////////////////////////////////////////////////////////////
   //
   // The convert operation converts a type to another.

   struct convert_op_t : op_t<convert_op_t>
   {
      // Note: pre-defined operations implementation are automatically registered,
      //       but these static variables do not get initialized by the testing framework.
      //       Tests need to explicitly call a function to trigger initialization.
      static void register_ops();
   };

   template<class TO>
   inline TO convert(const std::any& arg_a)
   {
      const std::any result = convert_op_t::call_any<TO>::op(arg_a);
      if (result.has_value())
         return std::any_cast<TO>(result);
      else
         return TO{};
   }

   template<class TO, class FROM>
   inline TO convert(const FROM& arg_a)
   {
      const std::any result = convert_op_t::call<TO>::op(arg_a);
      if (result.has_value())
         return std::any_cast<TO>(result);
      else
         return TO{};
   }

}

#endif /* DAK_ANY_OP_CONVERT_OP_H */
