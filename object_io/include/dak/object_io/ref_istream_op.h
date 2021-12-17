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

   //////////////////////////////////////////////////////////////////////////
   //
   // The input ref stream operation reads values from an input ref stream.
   //
   // The input format first reads the name of a type, so that it can know
   // what type of values it needs to read. Then,it reads the actual value.
   // This allows decoding any type of any value without knowing in advance
   // the type of the value.
   //
   // This format is enforced by the >> operator.
   // 
   // It discovers the type of the value it will need to read by first reading
   // the name of the type being input and finding the corresponding C++ type
   // via get_type_info_op_t. The name is followed by a numeric id that will
   // represent the type if encountered again. The association between the
   // type and its id is registered in the ref-istream.
   // 
   // The value is read via either ref_istream_op_t or istream_op_t.
   // A type that needs to read a reference or a name or contains sub-values
   // that may need to read such types, refs or names must implement the
   // ref-istream-op. For simple types, istream-op is sufficient. This is
   // good: most types don't need to known about the object library, only
   // the any-op library and its istream-op.
   //
   // This format relies on the existence of implementations of the following
   // operations for a given type:
   //
   //    - get_type_info_op_t : converts type name to C++ std::type_info
   //    - ref_istream_op_t or istream_op_t : reads a value

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
