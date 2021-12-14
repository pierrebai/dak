#pragma once

#ifndef DAK_OBJECT_REF_ISTREAM_H
#define DAK_OBJECT_REF_ISTREAM_H

#include <dak/object/ref_input.h>

#include <iostream>

namespace dak::object
{
   USING_DAK_UTILITY_TYPES;


   //////////////////////////////////////////////////////////////////////////
   //
   // Input stream wrapper to input object from a stream.
   // 
   // Input to the stream is done via the operator >> defined by the
   // ref_istream_op_t and the implementation registered by various types.
   //
   // Most functions are const so that a temporary ref stream can be passed
   // as a const value to the stream operator. This allows creating the
   // ref stream and sue it immediately in one expression.

   struct ref_istream_t : ref_input_t
   {
      // Wrap an input stream to handle reading object reference, names, namespaces, etc.
      //
      // Requires a transaction to create new names and namespace into the given base namespace.
      ref_istream_t(std::wistream& s, const valid_ref_t<namespace_t>& into_ns, transaction_t& transaction);

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
