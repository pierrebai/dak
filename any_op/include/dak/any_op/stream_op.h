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
   //
   // Note: the stream is received by pointer to travel in a std::any.

   struct stream_op_t : unary_op_t<stream_op_t, std::wostream&>
   {
      static std::wostream& call(std::wostream& a_stream, const std::any& arg_b)
      {
         call_op(a_stream, arg_b);
         return a_stream;
      }

      template<class A>
      static std::wostream& call(std::wostream& a_stream, const A& arg_b)
      {
         return call(a_stream, std::make_any<A>());
      }

      // Note: pre-defined operations implementation are automatically registered,
      //       but these static variables do not get initialized by the testing framework.
      //       Tests need to explicitly call a function to trigger initialization.
      static void register_ops();
   };

   std::wostream& operator<<(std::wostream& a_stream, const std::any& a_value);
}

#endif /* DAK_ANY_OP_STREAM_OP_H */
