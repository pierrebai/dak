#pragma once

#ifndef DAK_OBJECT_REF_OSTREAM_H
#define DAK_OBJECT_REF_OSTREAM_H

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

   struct ref_ostream_indent_t;


   //////////////////////////////////////////////////////////////////////////
   //
   // Output stream wrapper to output object into a stream.
   //
   // Most functions are const so that a temporary ref stream can be passed
   // as a const value to the stream operator. This allows creating the
   // ref stream and sue it immediately in one expression.

   struct ref_ostream_t
   {
      // Wrap an output stream to handle object refs.
      ref_ostream_t(std::wostream& s) : my_stream(s) {}


      //////////////////////////////////////////////////////////////////////////
      //
      // Underlying stream.

      std::wostream& get_stream() const { return my_stream; }


      //////////////////////////////////////////////////////////////////////////
      //
      // Output stream tracked objects.

      // Retrieve the id of an object reference .
      int64_t get_object_id(const ref_t<object_t>& object) const;

      // Retrieve the id of a name.
      int64_t get_name_id(const exact_name_t& name) const;

      // Reset the tracked object references.
      void clear();


      //////////////////////////////////////////////////////////////////////////
      //
      // Output stream formatting and indentation.

      // Output a end-line and indent the next line to the current indentation.
      const ref_ostream_t& end_line() const;

   private:
      // Map of already written object references, used to avoid
      // infinite recursion due to mutually referencing objects.
      // 
      // An object is written only the first time it is encountered.
      // Subsequent references to it only write the associated id
      // as a *negative* value. Invalid (null) references are written
      // as zero.
      //
      // Kept as mutable so that a temporary ref stream can be passed
      // as a const value to the stream operator.
      mutable std::unordered_map<ref_t<object_t>, int64_t> my_object_ids;

      // Map of already written names, used to avoid infinite recursion
      // due to names using each other as metadata.
      //
      // The numbering scheme is the same as for the object references.
      mutable std::unordered_map<exact_name_t, int64_t> my_name_ids;

      // The current indentation output after a new-line.
      mutable int32_t my_indentation = 0;

      std::wostream& my_stream;

      friend struct ref_ostream_indent_t;
   };


   //////////////////////////////////////////////////////////////////////////
   //
   // Increase the indentation of a ref_ostream_t while this object exists.

   struct ref_ostream_indent_t
   {
      ref_ostream_indent_t(const ref_ostream_t& ostr, const text_t& open, const text_t& close);
      ~ref_ostream_indent_t();

   private:
      const ref_ostream_t& my_ostr;
      const text_t my_close;
   };
}

#endif /* DAK_OBJECT_REF_OSTREAM_H */
