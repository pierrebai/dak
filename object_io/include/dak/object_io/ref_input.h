#pragma once

#ifndef DAK_OBJECT_REF_INPUT_H
#define DAK_OBJECT_REF_INPUT_H

#include <dak/utility/types.h>

#include <dak/object/object.h>
#include <dak/object/ref.h>
#include <dak/object/namespace.h>
#include <dak/object/exact_name.h>
#include <dak/object/transaction.h>

#include <unordered_map>

namespace dak::object
{
   USING_DAK_UTILITY_TYPES;


   //////////////////////////////////////////////////////////////////////////
   //
   // Input object from a file or stream.
   // 
   // Most functions are const so that a temporary ref stream can be passed
   // as a const value to the stream operator. This allows creating the
   // ref stream and sue it immediately in one expression.

   struct ref_input_t
   {
      // Input to handle reading object reference, names, namespaces, etc.
      //
      // Requires a transaction to create new names and namespace into the given base namespace.
      ref_input_t(const valid_ref_t<namespace_t>& into_ns, transaction_t& transaction);

      // Control if the output should be aborted when an unknown object is written.
      bool abort_on_unknown() const { return my_abort_on_unknown; }
      void set_abort_on_unknown(bool abort) { my_abort_on_unknown = abort; }

      // Target namespace that will receive sub-namespace and names.
      const valid_ref_t<namespace_t>& get_namespace() const { return my_target_namespace; }

      // Transaction used to add new names to the target namespace.
      transaction_t& get_transaction() const { return my_transaction; }

      // Retrieve the object reference corresponding to the id.
      const edit_ref_t<object_t>& get_object_with_id(int64_t id) const;

      // Add the object reference corresponding to the id.
      void add_object_with_id(const edit_ref_t<object_t>& obj, int64_t id) const;

      // Retrieve the name corresponding to the id.
      const exact_name_t& get_name_with_id(int64_t id) const;

      // Add the name corresponding to the id.
      void add_name_with_id(const exact_name_t& name, int64_t id) const;

      // Retrieve the type corresponding to the id.
      // Returns typeid(void) for unknown ids.
      const datatype_t& get_type_with_id(int64_t id) const;

      // Add the type corresponding to the id.
      void add_type_with_id(const datatype_t& a_type, int64_t id) const;

      // Reset the tracked object references, names and types.
      void clear();

   private:
      // Internal data is kept as mutable so that a temporary ref stream
      // can be passed as a const value to the stream operator.

      using object_ids_t = std::unordered_map<int64_t, edit_ref_t<object_t>>;
      using name_ids_t = std::unordered_map<int64_t, exact_name_t>;
      using type_ids_t = std::unordered_map<int64_t, const datatype_t*>;

      mutable object_ids_t my_object_with_ids;
      mutable name_ids_t   my_name_with_ids;
      mutable type_ids_t   my_type_with_ids;

      transaction_t&           my_transaction;
      valid_ref_t<namespace_t> my_target_namespace;
      bool                     my_abort_on_unknown = false;
   };
}

#endif /* DAK_OBJECT_REF_INPUT_H */
