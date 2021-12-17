#pragma once

#ifndef DAK_OBJECT_REF_OSTREAM_H
#define DAK_OBJECT_REF_OSTREAM_H

#include <dak/object_io/ref_output.h>

#include <iostream>

namespace dak::object
{
   struct ref_ostream_indent_t;


   //////////////////////////////////////////////////////////////////////////
   //
   // Output stream wrapper to output object into a stream.
   // 
   // Output to the ref-ostream is done via the operator << defined by the
   // ref_ostream_op_t and the type-specific implementations of this
   // ref-ostream-op registered by various types.
   // 
   // The ref-ostream itself only serves to hold the underlying stream and
   // record the object references, names and types that have already been
   // streamed. The magic really occurs within ref-ostream-op and its << op.
   //
   // Most functions are const so that a temporary ref stream can be passed
   // as a const value to the stream operator. This allows creating the
   // ref stream and sue it immediately in one expression.

   struct ref_ostream_t : ref_output_t
   {
      // Wrap an output stream to handle object refs.
      ref_ostream_t(std::wostream& s) : my_stream(s) {}

      // Underlying stream.
      std::wostream& get_stream() const { return my_stream; }

      // Output a end-line and indent the next line to the current indentation.
      const ref_ostream_t& end_line() const;

   private:
      // The current indentation output after a new-line.
      mutable int32_t my_indentation = 0;
      std::wostream&  my_stream;

      friend struct ref_ostream_indent_t;
   };


   //////////////////////////////////////////////////////////////////////////
   //
   // Increase the indentation of a ref_ostream_t while this object exists.
   // The indentation occurs between the two given open/close delimiters.

   struct ref_ostream_indent_t
   {
      ref_ostream_indent_t(const ref_ostream_t& ostr,
         const text_t& open, const text_t& close, int32_t indent_by = 2);
      ~ref_ostream_indent_t();

   private:
      const ref_ostream_t& my_ostr;
      const text_t my_close;
      const int32_t my_indent_by = 0;
   };
}

#endif /* DAK_OBJECT_REF_OSTREAM_H */
