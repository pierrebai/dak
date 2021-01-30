#pragma once

#ifndef DAK_ANY_OP_IS_COMPATIBLE_OP_H
#define DAK_ANY_OP_IS_COMPATIBLE_OP_H

#include <dak/any_op/nullary_op.h>

namespace dak::any_op
{

   //////////////////////////////////////////////////////////////////////////
   //
   // The is-compatible operation returns true if a the types are compatible.
   // That is, the first can be converted to the second.

   struct is_compatible_op_t : nullary_op_t<is_compatible_op_t>
   {
      // Note: pre-defined operations implementation are automatically registered,
      //       but these static variables do not get initialized by the testing framework.
      //       Tests need to explicitly call a function to trigger initialization.
      static void register_ops();
   };

   template<class TO>
   inline bool is_compatible(const std::any& arg_b)
   {
      const std::any result = is_compatible_op_t::call_any_op(std::type_index(typeid(TO)), std::type_index(arg_b.type()));
      if (result.has_value())
         return std::any_cast<bool>(result);
      else
         return false;
   }

   template<class TO, class FROM>
   inline bool is_compatible()
   {
      const std::any result = is_compatible_op_t::call_op<TO, FROM>();
      if (result.has_value())
         return std::any_cast<bool>(result);
      else
         return false;
   }

}

#endif /* DAK_ANY_OP_IS_COMPATIBLE_OP_H */
