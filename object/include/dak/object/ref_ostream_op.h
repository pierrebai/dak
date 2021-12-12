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
   // The output ref stream operation writes the value to an output ref stream.

   struct ref_ostream_op_t : any_op::op_t<ref_ostream_op_t, const ref_ostream_t&>
   {
      // Note: pre-defined operations implementation are automatically registered,
      //       but these static variables do not get initialized by the testing framework.
      //       Tests need to explicitly call a function to trigger initialization.
      static void register_ops();
   };

   inline const ref_ostream_t& operator <<(const ref_ostream_t& a_stream, const any_t& arg_a)
   {
      auto& ostr = a_stream.get_stream();

      const any_t tn = any_op::get_type_name(arg_a);
      if (!tn.has_value())
      {
         ostr.setstate(std::ios::failbit);
         return a_stream;
      }

      ostr << any_op::as<text_t>(tn) << L' ';

      any_t res = ref_ostream_op_t::call_any<>::op(a_stream, arg_a);
      if (!res.has_value() || !any_op::as<bool>(res))
         a_stream.get_stream().setstate(std::ios::failbit);

      return a_stream;
   }

   template<class A>
   inline const ref_ostream_t& operator <<(const ref_ostream_t& a_stream, const A& arg_a)
   {
      return a_stream << any_t(arg_a);
   }
}

#endif /* DAK_OBJECT_REF_OSTREAM_OP_H */
