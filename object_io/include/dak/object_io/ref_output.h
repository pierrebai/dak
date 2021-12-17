#pragma once

#ifndef DAK_OBJECT_REF_OUTPUT_H
#define DAK_OBJECT_REF_OUTPUT_H

#include <dak/utility/types.h>

#include <dak/object/name.h>
#include <dak/object/object.h>
#include <dak/object/ref.h>
#include <dak/object/exact_name.h>

#include <unordered_map>

namespace dak::object
{
   USING_DAK_UTILITY_TYPES;

   //////////////////////////////////////////////////////////////////////////
   //
   // Support base class to output objects into a file or stream.
   // 
   // This base class provides functions to registers object references,
   // types, and names and associate them with numeric ids.
   // 
   // Output to the stream is done via the operator << defined by the
   // ref_ostream_op_t and the implementation registered by various types.
   //
   // Most functions are const so that a temporary ref output can be created
   // used  immediately in one expression.

   struct ref_output_t
   {
      // Default constructor.
      ref_output_t() = default;

      // Control if the output should be aborted when an unknown object is written.
      bool abort_on_unknown() const { return my_abort_on_unknown; }
      void set_abort_on_unknown(bool abort) { my_abort_on_unknown = abort; }

      // Retrieve the id of an object reference .
      int64_t get_object_id(const ref_t<object_t>& object) const;

      // Retrieve the id of a name.
      int64_t get_name_id(const exact_name_t& name) const;

      // Retrieve the id of a type.
      int64_t get_type_id(const datatype_t& a_type) const;

      // Reset the tracked objects, types and names.
      void clear();

   private:
      // The maps of already written object references, types and
      // names are used to avoid infinite recursion due to mutually
      // referencing objects and names.
      // 
      // They also shortens the output by writing the objects
      // types and names only once.
      // 
      // An object, type or name is written only the first time it is
      // encountered. Subsequent uses only write the associated id
      // as a *negative* value. Invalid (null) items are written
      // as zero.
      //
      // The data is iept as mutable so that a temporary ref output
      // can be created as a temp variable and passed as a const value
      // to the operators.

      using object_ids_t = std::unordered_map<ref_t<object_t>, int64_t>;
      using name_ids_t = std::unordered_map<exact_name_t, int64_t>;
      using type_ids_t = std::unordered_map<const datatype_t*, int64_t>;

      mutable object_ids_t my_object_ids;
      mutable name_ids_t   my_name_ids;
      mutable type_ids_t   my_type_ids;
      bool                 my_abort_on_unknown = false;
   };

}

#endif /* DAK_OBJECT_REF_OUTPUT_H */
