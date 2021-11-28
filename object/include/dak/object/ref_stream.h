#pragma once

#ifndef DAK_OBJECT_REF_STREAM_H
#define DAK_OBJECT_REF_STREAM_H

#include <dak/utility/types.h>
#include <dak/object/array.h>
#include <dak/object/dict.h>
#include <dak/object/object.h>
#include <dak/object/namespace.h>

#include <iostream>

namespace dak::object
{
   USING_DAK_UTILITY_TYPES;

   //////////////////////////////////////////////////////////////////////////
   //
   // Output stream wrapper to output object into a stream.

   struct ref_ostream_t
   {
      // Wrap an output stream to handle object refs.
      ref_ostream_t(std::wostream& s) : my_stream(s) {}

      // Get the underlying stream.
      std::wostream& get_stream() const { return my_stream; }

      // Print an object through its reference.
      //
      // The first time an object is seen, it is output with a positive reference id.
      // Afterward, only the reference id is printed, as a negative value.
      // Empty references are printed as a zero reference id.
      const ref_ostream_t& print(const ref_t<object_t>& r) const;
      const ref_ostream_t& print(const element_t& e) const;
      const ref_ostream_t& print(const array_t& a) const;
      const ref_ostream_t& print(const dict_t& d) const;
      const ref_ostream_t& print(const object_t& o) const;
      const ref_ostream_t& print(const name_t& n) const;
      const ref_ostream_t& print(const namespace_t& ns) const;

      // Retrieve the reference id of an object.
      int64_t get_object_id(const ref_t<object_t>& object) const;

      // Reset the tracked object references.
      void clear();

   private:
      // Kept as mutable so that a const ref stream can be passed
      // as a temporary value to the stream operator.
      mutable std::map<const ref_t<object_t>, int64_t> my_object_ids;

      std::wostream& my_stream;
   };


   //////////////////////////////////////////////////////////////////////////
   //
   // Output streaming operator.
   //
   // Use the normal stream operator, except for object references.

   template <class T>
   inline const ref_ostream_t& operator <<(const ref_ostream_t& rstr, const T& value)
   {
      // Note: it is *important* to keep the chain of else-if so that the final
      //       else if *not* compiled when a constexpr conditional matches,
      //       otherwise that else will get compiled and fail.
      if constexpr (std::is_base_of<element_t, T>())
      {
         return rstr.print(value);
      }
      else if constexpr (std::is_base_of<name_t, T>())
      {
         return rstr.print(value);
      }
      else if constexpr (std::is_base_of<namespace_t, T>())
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


   //////////////////////////////////////////////////////////////////////////
   //
   // Input stream wrapper to input object from a stream.

   struct ref_istream_t
   {
      // The known namespace that can be searched for names.
      using namespaces_t = std::vector<valid_ref_t<namespace_t>>;

      // Wrap an input stream to handle object refs.
      ref_istream_t(std::wistream& s, namespaces_t known_ns);
      ref_istream_t(std::wistream& s, const valid_ref_t<namespace_t>& known_ns);

      // Get the underlying stream.
      std::wistream& get_stream() const { return my_stream; }

      // Parse an object through its reference.
      //
      // The first time an object is seen, it is output with a positive reference id.
      // Afterward, only the reference id is printed, as a negative value.
      // Empty references are printed as a zero reference id.
      const ref_istream_t& parse(ref_t<object_t>& r) const;
      const ref_istream_t& parse(element_t& e) const;
      const ref_istream_t& parse(array_t& a) const;
      const ref_istream_t& parse(dict_t& d) const;
      const ref_istream_t& parse(object_t& o) const;
      const ref_istream_t& parse(name_t& n) const;

      // Retrieve the object reference corresponding to the id.
      ref_t<object_t> get_object_with_id(int64_t id) const;

      // Add the object reference corresponding to the id.
      void add_object_with_id(const valid_ref_t<object_t>& obj, int64_t id) const;

      // Reset the tracked object references.
      void clear();

   private:
      // Kept as mutable so that a const ref stream can be passed
      // as a temporary value to the stream operator.
      mutable std::map<int64_t, ref_t<object_t>> my_object_with_ids;

      std::wistream& my_stream;
      namespace_t    my_top_namespace;
   };


   //////////////////////////////////////////////////////////////////////////
   //
   // Input streaming operator.
   //
   // Use the normal stream operator, except for object references.

   template <class T>
   inline const ref_istream_t& operator >>(const ref_istream_t& rstr, T& value)
   {
      // Note: it is *important* to keep the chain of else-if so that the final
      //       else if *not* compiled when a constexpr conditional matches,
      //       otherwise that else will get compiled and fail.
      if constexpr (std::is_base_of<element_t, T>())
      {
         return rstr.parse(value);
      }
      else if constexpr (std::is_base_of<name_t, T>())
      {
         return rstr.parse(value);
      }
      else if constexpr (std::is_base_of<ref_t<object_t>, T>())
      {
         return rstr.parse(value);
      }
      else if constexpr (std::is_base_of<dict_t, T>())
      {
         return rstr.parse(value);
      }
      else if constexpr (std::is_base_of<array_t, T>())
      {
         return rstr.parse(value);
      }
      else if constexpr (std::is_base_of<object_t, T>())
      {
         return rstr.parse(value);
      }
      else
      {
         rstr.get_stream() >> value;
         return rstr;
      }
   }
}

#endif /* DAK_OBJECT_STREAM_H */
