#pragma once

#ifndef DAK_ANY_OP_IS_COMPATIBLE_OP_H
#define DAK_ANY_OP_IS_COMPATIBLE_OP_H

#include <dak/any_op/op.h>

namespace dak::any_op
{

   //////////////////////////////////////////////////////////////////////////
   //
   // The is-compatible operation returns true if a the types are compatible.
   // That is, the second can be converted to the first.
   //
   // To remember the order, it is the same order as an assignement: TO = FROM

   struct is_compatible_op_t : op_t<is_compatible_op_t>
   {
      // Note: pre-defined operations implementation are automatically registered,
      //       but these static variables do not get initialized by the testing framework.
      //       Tests need to explicitly call a function to trigger initialization.
      static void register_ops();
   };

   bool is_compatible(const type_info_t& to_type, const type_info_t& from_type);

   template<class TO>
   inline bool is_compatible(const any_t& from_value)
   {
      return is_compatible(typeid(TO), from_value.type());
   }

   template<class TO, class FROM>
   inline bool is_compatible()
   {
      return is_compatible(typeid(TO), typeid(FROM));
   }
}

#endif /* DAK_ANY_OP_IS_COMPATIBLE_OP_H */
