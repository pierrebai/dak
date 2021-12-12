#pragma once

#ifndef DAK_OBJECT_MAKE_OP_H
#define DAK_OBJECT_MAKE_OP_H

#include <dak/any_op/op.h>
#include <dak/any_op/as_op.h>

#include <dak/object/edit_ref.h>

namespace dak::object
{
   //////////////////////////////////////////////////////////////////////////
   //
   // The make operation creates an object with default initialization
   // and returns the a reference, ref_t<T>.

   struct make_object_op_t : any_op::op_t<make_object_op_t>
   {
      // Note: pre-defined operations implementation are automatically registered,
      //       but these static variables do not get initialized by the testing framework.
      //       Tests need to explicitly call a function to trigger initialization.
      static void register_ops();
   };

   template<class T>
   inline ref_t<T> make_object()
   {
      any_t result = make_object_op_t::call<T>::op();
      return any_op::as<ref_t<T>>(result);
   }

   inline any_t make_object(const std::type_info& arg_a)
   {
      return make_object_op_t::call_extra_any<void>::op(arg_a);
   }
}

#endif /* DAK_OBJECT_MAKE_OP_H */
