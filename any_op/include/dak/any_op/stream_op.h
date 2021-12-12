#pragma once

#ifndef DAK_ANY_OP_STREAM_OP_H
#define DAK_ANY_OP_STREAM_OP_H

#include <dak/any_op/op.h>
#include <dak/any_op/as_op.h>

#include <ostream>
#include <istream>

namespace dak::any_op
{

   //////////////////////////////////////////////////////////////////////////
   //
   // The output stream operation writes the value to an output stream.

   struct ostream_op_t : op_t<ostream_op_t, std::wostream&>
   {
      // Note: pre-defined operations implementation are automatically registered,
      //       but these static variables do not get initialized by the testing framework.
      //       Tests need to explicitly call a function to trigger initialization.
      static void register_ops();
   };

   inline std::wostream& stream(std::wostream& a_stream, const any_t& arg_a)
   {
      ostream_op_t::call_any<>::op(a_stream, arg_a);
      return a_stream;
   }

   template<class A>
   inline std::wostream& stream(std::wostream& a_stream, const A& arg_a)
   {
      ostream_op_t::call<>::op(a_stream, arg_a);
      return a_stream;
   }

   std::wostream& operator<<(std::wostream& a_stream, const any_t& a_value);


   //////////////////////////////////////////////////////////////////////////
   //
   // The input stream operation reads the value to an input stream.
   // The any_t must already be filled with the expected type of the input,
   // which means the caller must have an external way of pre-determining
   // this type before the call.

   struct istream_op_t : op_t<istream_op_t, std::wistream&>
   {
      // Note: pre-defined operations implementation are automatically registered,
      //       but these static variables do not get initialized by the testing framework.
      //       Tests need to explicitly call a function to trigger initialization.
      static void register_ops();
   };

   inline std::wistream& stream(std::wistream& a_stream, any_t& arg_a)
   {
      any_t result = istream_op_t::call_any_with_types<any_t>::op(a_stream, std::type_index(std::type_index(arg_a.type())));
      if (result.has_value())
         arg_a = result;
      return a_stream;
   }

   template<class A>
   inline std::wistream& stream(std::wistream& a_stream, A& arg_a)
   {
      any_t result = istream_op_t::call_any_with_types<any_t>::op(a_stream, std::type_index(typeid(A)));
      arg_a = as<A>(result);
      return a_stream;
   }

   std::wistream& operator>>(std::wistream& a_stream, any_t& a_value);
}

#endif /* DAK_ANY_OP_STREAM_OP_H */
