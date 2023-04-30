#pragma once

#ifndef DAK_ANY_OP_CONVERT_OP_H
#define DAK_ANY_OP_CONVERT_OP_H

#include <dak/any_op/op.h>

#include <type_traits>

namespace dak::any_op
{
   //////////////////////////////////////////////////////////////////////////
   //
   // The convert operation converts a value to another type.
   //
   // The identity conversion, from T to T, does not need to be registered
   // when calling through the convert() function below, but does need to
   // be registered if called directly through convert_op_t, but you should
   // not do that.
   //
   // If the value could not be converted, a default-constructed value
   // of the destination type is returned.

   struct convert_op_t : op_t<convert_op_t>
   {
      // Note: pre-defined operations implementation are automatically registered,
      //       but these static variables do not get initialized by the testing framework.
      //       Tests need to explicitly call a function to trigger initialization.
      static void register_ops();
   };

   template<class TO>
   inline TO convert(const any_t& arg_a)
   {
      if (const TO* value = std::any_cast<TO>(&arg_a))
         return *value;

      any_t result = convert_op_t::call_any<TO>::op(arg_a);
      if (!result.has_value())
         return TO{};

      return std::any_cast<TO>(result);
   }

   template<class TO, class FROM>
   inline TO convert(const FROM& arg_a)
   {
      if constexpr (std::is_same_v<TO, FROM>)
         return arg_a;

      if constexpr (std::is_base_of_v<TO, FROM>)
         return arg_a;

      any_t result = convert_op_t::call<TO>::op(arg_a);
      if (!result.has_value())
         return TO{};

      return std::any_cast<TO>(result);
   }

   inline any_t convert(const any_t& arg_a, const type_info_t& some_type)
   {
      return convert_op_t::call_any_with_types<void>::op<any_t>(arg_a, some_type);
   }

}

#endif /* DAK_ANY_OP_CONVERT_OP_H */
