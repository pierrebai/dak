#pragma once

#ifndef DAK_ANY_OP_COMPARE_OP_H
#define DAK_ANY_OP_COMPARE_OP_H

#include <dak/any_op/op.h>
#include <dak/any_op/as_op.h>

namespace dak::any_op
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Comparison results.
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

   struct compare_op_t : op_t<compare_op_t>
   {
      // Note: pre-defined operations implementation are automatically registered,
      //       but these static variables do not get initialized by the testing framework.
      //       Tests need to explicitly call a function to trigger initialization.
      static void register_ops();
   };


   //////////////////////////////////////////////////////////////////////////
   //
   // Comparison function.

   comparison_t compare(const any_t& arg_a, const any_t& arg_b);

   template<class A>
   inline comparison_t compare(const A& arg_a, const A& arg_b)
   {
      return compare(any_t(arg_a), any_t(arg_b));
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Comparison C++ operators.

   inline bool operator==(const any_t& arg_a, const any_t& arg_b)
   {
      return compare(arg_a, arg_b) == comparison_t::equal;
   }

   inline bool operator<(const any_t& arg_a, const any_t& arg_b)
   {
      return compare(arg_a, arg_b) == comparison_t::less;
   }

   inline bool operator>(const any_t& arg_a, const any_t& arg_b)
   {
      return compare(arg_a, arg_b) == comparison_t::more;
   }

   inline bool operator!=(const any_t& arg_a, const any_t& arg_b)
   {
      return compare(arg_a, arg_b) != comparison_t::equal;
   }

   inline bool operator<=(const any_t& arg_a, const any_t& arg_b)
   {
      return is(compare(arg_a, arg_b), comparison_t::less_or_equal);
   }

   inline bool operator>=(const any_t& arg_a, const any_t& arg_b)
   {
      return is(compare(arg_a, arg_b), comparison_t::more_or_equal);
   }
}

#endif /* DAK_ANY_OP_COMPARE_OP_H */
