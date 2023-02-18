#pragma once

#ifndef DAK_OBJECT_REF_OSTREAM_OP_H
#define DAK_OBJECT_REF_OSTREAM_OP_H

#include <dak/object_io/ref_ostream.h>

#include <dak/any_op/as_op.h>
#include <dak/utility/type_info.h>

#include <iomanip>

namespace dak::object
{
   USING_DAK_UTILITY_TYPES;

   //////////////////////////////////////////////////////////////////////////
   //
   // The output ref stream operation writes values to an output ref stream.
   //
   // The output format writes the name of the type of the value first, then
   // the actual value. This allows auto-decoding when streaming in. Since
   // the value can be a complex type, this process is recursive.
   // 
   // This format is enforced by the << operator.
   // 
   // It prints the name of the type being output (via get_type_name_op_t)
   // followed by a numeric id that will represent the type if encountered
   // again. The association between the type and its id is registered in
   // the ref-ostream.
   // 
   // The value is printed via either ref_ostream_op_t or ostream_op_t.
   // A type that needs to write a reference or a name or contains sub-values
   // that may need to write such types, refs or names must implement the
   // ref-ostream-op. For simple types, ostream-op is sufficient. This is
   // good: most types don't need to known about the object library, only
   // the any-op library and its ostream-op.
   //
   // This format relies on the existence of implementations of the following
   // functions or operations for a given type:
   //
   //    - get_type_name : converts a type_info_t to a type name
   //    - ref_ostream_op_t or ostream_op_t : writes a value

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
