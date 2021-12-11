#pragma once

#ifndef DAK_OBJECT_REF_ISTREAM_OP_H
#define DAK_OBJECT_REF_ISTREAM_OP_H

#include <dak/object/ref_istream.h>

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
   // The input refstream operation reads the value from an input ref stream.

   struct ref_istream_op_t : any_op::op_t<ref_istream_op_t, const ref_istream_t&>
   {
      // Note: pre-defined operations implementation are automatically registered,
      //       but these static variables do not get initialized by the testing framework.
      //       Tests need to explicitly call a function to trigger initialization.
      static void register_ops();
   };

   inline const ref_istream_t& operator >>(const ref_istream_t& a_stream, any_t& arg_a)
   {
      auto& istr = a_stream.get_stream();

      text_t tn;
      istr >> std::ws >> tn >> std::ws;
      const std::type_info& info = any_op::get_type_info(tn);
      if (info == typeid(void))
      {
         istr.setstate(std::ios::failbit);
         return a_stream;
      }

      any_t result = ref_istream_op_t::call_extra_any<any_t>::op(a_stream, std::type_index(info));
      if (!result.has_value())
      {
         istr.setstate(std::ios::failbit);
         return a_stream;
      }

      arg_a = result;
      return a_stream;
   }

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
