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
   //
   // Note: no templated version is provided since when you already have
   //       the type it is simpler to call its static make() function directly!

   struct make_op_t : any_op::op_t<make_op_t>
   {
      // Note: pre-defined operations implementation are automatically registered,
      //       but these static variables do not get initialized by the testing framework.
      //       Tests need to explicitly call a function to trigger initialization.
      static void register_ops();
   };

   inline any_t make(const std::type_info& arg_a)
   {
      return make_op_t::call_any_with_types<void>::op(arg_a);
   }
}

#endif /* DAK_OBJECT_MAKE_OP_H */
