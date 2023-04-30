#pragma once

#ifndef DAK_ANY_OP_AS_OP_H
#define DAK_ANY_OP_AS_OP_H

#include <dak/any_op/op.h>
#include <dak/any_op/is_compatible_op.h>
#include <dak/any_op/convert_op.h>

namespace dak::any_op
{
   //////////////////////////////////////////////////////////////////////////
   //
   // The as operation casts an any_t to a reference type, if possible.
   //
   // The identity conversion, from T to T, does not need to be registered
   // when calling through the as() function below.
   //
   // If the value could not be cast, a default-constructed value
   // of the destination type is returned.

   template<class TO>
   inline const TO& as(const any_t& arg_a)
   {
      if (arg_a.type() == typeid(TO))
         return std::any_cast<const TO&>(arg_a);

      static const TO empty{};
      return empty;
   }

   template<class TO>
   inline TO& as(any_t& arg_a)
   {
      if (arg_a.type() == typeid(TO))
         return std::any_cast<TO&>(arg_a);

      if (is_compatible<TO>(arg_a))
      {
         arg_a = convert<TO>(arg_a);
         return std::any_cast<TO&>(arg_a);
      }

      static TO empty{};
      return empty;
   }

   template<class TO, class FROM>
   inline TO as(const FROM& arg_a)
   {
      if constexpr (std::is_same_v<TO, FROM>)
         return arg_a;

      if constexpr (std::is_base_of_v<TO, FROM>)
         return arg_a;

      if (is_compatible<TO>(arg_a))
         return convert<TO>(arg_a);

      static TO empty{};
      return empty;
   }

}

#endif /* DAK_ANY_OP_AS_OP_H */
