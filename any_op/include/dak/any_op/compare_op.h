#pragma once

#ifndef DAK_ANY_OP_COMPARE_OP_H
#define DAK_ANY_OP_COMPARE_OP_H

#include <dak/any_op/binary_op.h>

namespace dak::any_op
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Comparison possible results.
   //
   // Note: incomparable should result in operator== returning false,
   //       operator!= returning true, and all relative operators
   //       (<, >, <=, >=) returning false.

   enum class comparison_t : int8_t
   {
      incomparable = 0,
      equal = 1,
      less = 2,
      more = 4,
      less_or_equal = less | equal,
      more_or_equal = more | equal,
   };

   inline bool is(const comparison_t result, const comparison_t desired)
   {
      return 0 != (uint8_t(result) & uint8_t(desired));
   }


   //////////////////////////////////////////////////////////////////////////
   //
   // The compare operation compares two values.
   // 
   // Note: returns comparison_t::incomparable if two values cannot be compared.

   struct compare_op_t : binary_op_t<compare_op_t>
   {
      constexpr static comparison_t equal = comparison_t::equal;
      constexpr static comparison_t less = comparison_t::less;
      constexpr static comparison_t more = comparison_t::more;
      constexpr static comparison_t incomparable = comparison_t::incomparable;

      static comparison_t call(const std::any& arg_a, const std::any& arg_b)
      {
         if (!arg_a.has_value())
         {
            return !arg_b.has_value() ? equal : less;
         }
         else if (!arg_b.has_value())
         {
            return more;
         }

         const std::any result = call_op(arg_a, arg_b);
         if (result.has_value())
            return std::any_cast<comparison_t>(result);

         return incomparable;
      }

      template<class A>
      static comparison_t call(const A& arg_a, const A& arg_b)
      {
         return call(std::any(arg_a), std::any(arg_b));
      }

      // Note: pre-defined operations implementation are automatically registered,
      //       but these static variables do not get initialized by the testing framework.
      //       Tests need to explicitly call a function to trigger initialization.
      static void register_ops();
   };


   //////////////////////////////////////////////////////////////////////////
   //
   // Comparison C++ operators.

   inline bool operator==(const std::any& arg_a, const std::any& arg_b)
   {
      return compare_op_t::call(arg_a, arg_b) == compare_op_t::equal;
   }

   inline bool operator<(const std::any& arg_a, const std::any& arg_b)
   {
      return compare_op_t::call(arg_a, arg_b) == compare_op_t::less;
   }

   inline bool operator>(const std::any& arg_a, const std::any& arg_b)
   {
      return compare_op_t::call(arg_a, arg_b) == compare_op_t::more;
   }

   inline bool operator!=(const std::any& arg_a, const std::any& arg_b)
   {
      return compare_op_t::call(arg_a, arg_b) != compare_op_t::equal;
   }

   inline bool operator<=(const std::any& arg_a, const std::any& arg_b)
   {
      return is(compare_op_t::call(arg_a, arg_b), comparison_t::less_or_equal);
   }

   inline bool operator>=(const std::any& arg_a, const std::any& arg_b)
   {
      return is(compare_op_t::call(arg_a, arg_b), comparison_t::more_or_equal);
   }
}

#endif /* DAK_ANY_OP_COMPARE_OP_H */
