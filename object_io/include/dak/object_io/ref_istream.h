#pragma once

#ifndef DAK_OBJECT_REF_ISTREAM_H
#define DAK_OBJECT_REF_ISTREAM_H

#include <dak/object_io/ref_input.h>

#include <iostream>

namespace dak::object
{
   USING_DAK_UTILITY_TYPES;


   //////////////////////////////////////////////////////////////////////////
   //
   // Input stream wrapper to input object from a stream.
   // 
   // Input from the stream is done via the operator >> defined by the
   // ref_istream_op_t and the type-specific implementations of this
   // ref-istream-op registered by various types.
   //
   // The ref-istream itself only serves to hold the underlying stream and
   // record the object references, names and types that have already been
   // read. The magic really occurs within ref-istream-op and its >> op.
   //
   // Most functions are const so that a temporary ref stream can be passed
   // as a const value to the stream operator. This allows creating the
   // ref stream and use it immediately in one expression.

   struct ref_istream_t : ref_input_t
   {
      // Wrap an input stream to handle reading object reference, names, namespaces, etc.
      //
      // Requires a transaction to create new names and namespace into the given base namespace.
      ref_istream_t(std::wistream& s, const valid_ref_t<namespace_t>& into_ns, transaction_t& transaction);

      // Abort the input, called on errors, when abort_on_unknown() is true.
      void abort() const override;

      // Underlying stream.
      std::wistream& get_stream() const { return my_stream; }

      // Try to read the given sigil character.
      // Consumes it and return true if found.
      // Put back the character read and return false if not found.
      bool parse_optional_sigil(const wchar_t expected_sigil) const;

      // Try to read the given sigil character.
      // Consumes it and return true if found.
      // Set the stream fail flag and return false if not found.
      bool parse_sigil(const wchar_t expected_sigil) const;

      // Parse option end sigil, just like parse_optional_sigil
      // but with a different name to make parsing code clearer.
      bool is_end(const wchar_t possible_end) const
      {
         return parse_optional_sigil(possible_end);
      }

   private:
      std::wistream&             my_stream;
   };
}

#endif /* DAK_OBJECT_REF_ISTREAM_H */
