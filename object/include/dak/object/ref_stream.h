#pragma once

#ifndef DAK_OBJECT_REF_STREAM_H
#define DAK_OBJECT_REF_STREAM_H

#include <dak/object/stream.h>

namespace dak::object
{
   USING_DAK_UTILITY_TYPES;

   //////////////////////////////////////////////////////////////////////////
   //
   // Output stream wrapper to output object refs into a stream.

   struct ref_stream_t
   {
      // Wrap an output stream to handle object refs.
      ref_stream_t(std::wostream& s) : my_stream(s) {}

      // Get the underlying stream.
      std::wostream& get_stream() const { return my_stream; }

      // Print an object through its reference.
      //
      // The first time an object is seen, it is output with a positive reference id.
      // Afterward, only the reference id is printed, as a negative value.
      // Empty references are printed as a zero reference id.
      const ref_stream_t& print(const ref_t<object_t>& o) const;
      const ref_stream_t& print(const element_t& e) const;
      const ref_stream_t& print(const array_t& a) const;
      const ref_stream_t& print(const dict_t& d) const;
      const ref_stream_t& print(const object_t& o) const;

      // Retrieve the reference id of an object.
      int64_t get_object_id(const ref_t<object_t>& object) const;

      // Reset the tracked object references.
      void clear();

   private:
      std::wostream& my_stream;

      // Kept as mutable so that a const ref stream can be passed
      // as a temporary value to the stream operator.
      mutable std::map<const ref_t<object_t>, int64_t> my_object_ids;
   };


   //////////////////////////////////////////////////////////////////////////
   //
   // Output streaming operator.
   //
   // Use the normal stream operator, except for object references.

   template <class T>
   inline const ref_stream_t& operator <<(const ref_stream_t& rstr, const T& value)
   {
      // Note: it is *important* to keep the chain of else-if so that the final
      //       else if *not* compiled when a constexpr conditional matches,
      //       otherwise that else will get compiled and fail.
      if constexpr (std::is_base_of<element_t, T>())
      {
         return rstr.print(value);
      }
      else if constexpr (std::is_base_of<ref_t<object_t>, T>())
      {
         return rstr.print(value);
      }
      else if constexpr (std::is_base_of<dict_t, T>())
      {
         return rstr.print(value);
      }
      else if constexpr (std::is_base_of<array_t, T>())
      {
         return rstr.print(value);
      }
      else if constexpr (std::is_base_of<object_t, T>())
      {
         return rstr.print(value);
      }
      else
      {
         rstr.get_stream() << value;
         return rstr;
      }
   }
}

#endif /* DAK_OBJECT_STREAM_H */
