#pragma once

#ifndef DAK_ANY_OP_STREAM_OP_H
#define DAK_ANY_OP_STREAM_OP_H

#include <dak/any_op/op.h>

#include <ostream>

namespace dak::any_op
{

   //////////////////////////////////////////////////////////////////////////
   //
   // The stream operation writes the value to an output stream.

   struct stream_op_t : op_t<stream_op_t, std::wostream&>
   {
      // Note: pre-defined operations implementation are automatically registered,
      //       but these static variables do not get initialized by the testing framework.
      //       Tests need to explicitly call a function to trigger initialization.
      static void register_ops();
   };

   inline std::wostream& stream(std::wostream& a_stream, const std::any& arg_a)
   {
      stream_op_t::call_any<>::op(a_stream, arg_a);
      return a_stream;
   }

   template<class A>
   inline std::wostream& stream(std::wostream& a_stream, const A& arg_a)
   {
      stream_op_t::call<>::op(a_stream, arg_a);
      return a_stream;
   }

   std::wostream& operator<<(std::wostream& a_stream, const std::any& a_value);
}

#endif /* DAK_ANY_OP_STREAM_OP_H */
