#pragma once

#ifndef DAK_ANY_OP_STREAM_OP_H
#define DAK_ANY_OP_STREAM_OP_H

#include <dak/any_op/unary_op.h>

#include <ostream>

namespace dak::any_op
{

   //////////////////////////////////////////////////////////////////////////
   //
   // The stream operation writes the value to an output stream.

   struct stream_op_t : unary_op_t<stream_op_t, std::wostream&>
   {
      static std::wostream& call(std::wostream& a_stream, const std::any& arg_a)
      {
         call_op(a_stream, arg_a);
         return a_stream;
      }

      template<class A>
      static std::wostream& call(std::wostream& a_stream, const A& arg_a)
      {
         return call(a_stream, std::make_any<A>(arg_a));
      }

      // Note: pre-defined operations implementation are automatically registered,
      //       but these static variables do not get initialized by the testing framework.
      //       Tests need to explicitly call a function to trigger initialization.
      static void register_ops();
   };

   template<class A>
   inline
   std::wostream& stream(std::wostream& a_stream, const A& arg_a)
   {
      return stream_op_t::call<A>(a_stream, arg_a);
   }

   inline std::wostream& stream(std::wostream& a_stream, const std::any& arg_a)
   {
      return stream_op_t::call(a_stream, arg_a);
   }

   std::wostream& operator<<(std::wostream& a_stream, const std::any& a_value);
}

#endif /* DAK_ANY_OP_STREAM_OP_H */
