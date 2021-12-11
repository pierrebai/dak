#pragma once

#ifndef DAK_OBJECT_REF_ISTREAM_H
#define DAK_OBJECT_REF_ISTREAM_H

#include <dak/utility/types.h>
#include <dak/object/object.h>
#include <dak/object/ref.h>
#include <dak/object/namespace.h>
#include <dak/object/exact_name.h>
#include <dak/object/transaction.h>

#include <iostream>
#include <unordered_map>

namespace dak::object
{
   USING_DAK_UTILITY_TYPES;


   //////////////////////////////////////////////////////////////////////////
   //
   // Input stream wrapper to input object from a stream.
   //
   // Most functions are const so that a temporary ref stream can be passed
   // as a const value to the stream operator. This allows creating the
   // ref stream and sue it immediately in one expression.

   struct ref_istream_t
   {
      // Wrap an input stream to handle reading object reference, names, namespaces, etc.
      //
      // Requires a transaction to create new names and namespace into the given base namespace.
      ref_istream_t(std::wistream& s, const valid_ref_t<namespace_t>& into_ns, transaction_t& transaction);


      //////////////////////////////////////////////////////////////////////////
      //
      // Underlying stream, namespace and transaction.

      std::wistream& get_stream() const { return my_stream; }

      const valid_ref_t<namespace_t>& get_namespace() const { return my_target_namespace; }

      transaction_t& get_transaction() const { return my_transaction; }


      //////////////////////////////////////////////////////////////////////////
      //
      // Input stream tracked objects and names.

      // Retrieve the object reference corresponding to the id.
      const edit_ref_t<object_t>& get_object_with_id(int64_t id) const;

      // Add the object reference corresponding to the id.
      void add_object_with_id(const edit_ref_t<object_t>& obj, int64_t id) const;

      // Retrieve the name corresponding to the id.
      const exact_name_t& get_name_with_id(int64_t id) const;

      // Add the name corresponding to the id.
      void add_name_with_id(const exact_name_t& obj, int64_t id) const;

      // Reset the tracked object references.
      void clear();


      //////////////////////////////////////////////////////////////////////////
      //
      // Input stream sigil parsers.

      // Try to read the given sigil character.
      // Consumes it and return true if found.
      // Put back the character read and return false if not found.
      bool parse_optional_sigil(const wchar_t expected_sigil) const;

      // Try to read the given sigil character.
      // Consumes it and return true if found.
      // Set the stream fail flag and return false if not found.
      bool parse_sigil(const wchar_t expected_sigil) const;

      // Try to read the given sigil text.
      // Consumes it and return true if found.
      // Set the stream fail flag and return false if not found.
      bool parse_sigil(const str_ptr_t expected_sigil) const;

      // Parse option end sigil, just like parse_optional_sigil
      // but with a different name to make parsing code clearer.
      bool is_end(const wchar_t possible_end) const
      {
         return parse_optional_sigil(possible_end);
      }

   private:
      // Kept as mutable so that a temporary ref stream can be passed
      // as a const value to the stream operator.
      mutable std::unordered_map<int64_t, edit_ref_t<object_t>> my_object_with_ids;

      // Kept as mutable so that a temporary ref stream can be passed
      // as a const value to the stream operator.
      mutable std::unordered_map<int64_t, exact_name_t> my_name_with_ids;

      std::wistream&             my_stream;
      transaction_t&             my_transaction;
      valid_ref_t<namespace_t>   my_target_namespace;
   };
}

#endif /* DAK_OBJECT_REF_ISTREAM_H */
