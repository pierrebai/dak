#pragma once

#ifndef DAK_OBJECT_REF_OSTREAM_OP_H
#define DAK_OBJECT_REF_OSTREAM_OP_H

#include <dak/object/ref_ostream.h>

#include <dak/any_op/as_op.h>
#include <dak/any_op/get_type_name_op.h>
#include <dak/any_op/get_type_info_op.h>

#include <iomanip>

namespace dak::object
{
   USING_DAK_UTILITY_TYPES;

   using ref_ostream_t = dak::object::ref_ostream_t;

   //////////////////////////////////////////////////////////////////////////
   //
   // The output ref stream operation writes values to an output ref stream.
   //
   // The output format writes the name of the type of the value first, then
   // the actual value. This allows auto-decoding when streaming in.
   //
   // This format relies on the existence of implementations of the following
   // operations for a given type:
   //
   //    - get_type_name_op_t
   //    - get_type_info_op_t
   //    - ref_ostream_op_t
   //    - ref_istream_op_t

   struct ref_ostream_op_t : any_op::op_t<ref_ostream_op_t, const ref_ostream_t&>
   {
      // Note: pre-defined operations implementation are automatically registered,
      //       but these static variables do not get initialized by the testing framework.
      //       Tests need to explicitly call a function to trigger initialization.
      static void register_ops();
   };

   const ref_ostream_t& operator <<(const ref_ostream_t& a_stream, const any_t& arg_a);

   template<class A>
   inline const ref_ostream_t& operator <<(const ref_ostream_t& a_stream, const A& arg_a)
   {
      return a_stream << any_t(arg_a);
   }
}

#endif /* DAK_OBJECT_REF_OSTREAM_OP_H */
