#pragma once

#ifndef DAK_OBJECT_REF_ISTREAM_OP_H
#define DAK_OBJECT_REF_ISTREAM_OP_H

#include <dak/object_io/ref_istream.h>

#include <dak/any_op/as_op.h>
#include <dak/any_op/get_type_name_op.h>
#include <dak/any_op/get_type_info_op.h>

#include <iomanip>

namespace dak::object
{
   USING_DAK_UTILITY_TYPES;

   using ref_istream_t = dak::object::ref_istream_t;

   //////////////////////////////////////////////////////////////////////////
   //
   // The input ref stream operation reads values from an input ref stream.
   //
   // The input format reads the name of the type of the value first, then
   // the actual value. This allows auto-decoding when streaming in.
   //
   // This format relies on the existence of implementations of the following
   // operations for a given type:
   //
   //    - get_type_name_op_t
   //    - get_type_info_op_t
   //    - ref_ostream_op_t
   //    - ref_istream_op_t

   struct ref_istream_op_t : any_op::op_t<ref_istream_op_t, const ref_istream_t&>
   {
      // Note: pre-defined operations implementation are automatically registered,
      //       but these static variables do not get initialized by the testing framework.
      //       Tests need to explicitly call a function to trigger initialization.
      static void register_ops();
   };

   const ref_istream_t& operator >>(const ref_istream_t& a_stream, any_t& arg_a);

   template<class T>
   inline const ref_istream_t& operator >>(const ref_istream_t& a_stream, T& arg_a)
   {
      any_t any_a;
      a_stream >> any_a;
      if (any_a.has_value())
         arg_a = any_op::as<T>(any_a);
      return a_stream;
   }
}

#endif /* DAK_OBJECT_REF_ISTREAM_OP_H */
