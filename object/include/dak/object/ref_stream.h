#pragma once

#ifndef DAK_OBJECT_REF_STREAM_H
#define DAK_OBJECT_REF_STREAM_H

#include <dak/utility/types.h>
#include <dak/object/array.h>
#include <dak/object/dict.h>
#include <dak/object/object.h>
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
      const ref_ostream_t& print(const weak_ref_t<object_t>& r) const;
      const ref_ostream_t& print(const element_t& e) const;
      const ref_ostream_t& print(const array_t& a) const;
      const ref_ostream_t& print(const dict_t& d) const;
      const ref_ostream_t& print(const any_t& d) const;
      const ref_ostream_t& print(const object_t& o) const;
      const ref_ostream_t& print(const name_t& n) const;
      const ref_ostream_t& print(const weak_ref_t<namespace_t>& ns) const;

      // Retrieve the id of an object reference .
      int64_t get_object_id(const ref_t<object_t>& object) const;

      // Retrieve the id of a name.
      int64_t get_name_id(const exact_name_t& name) const;

      // Reset the tracked object references.
      void clear();

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
      else if constexpr (std::is_base_of<weak_ref_t<object_t>, T>())
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
      else if constexpr (std::is_base_of<any_t, T>())
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
      // Wrap an input stream to handle reading object reference, names, namespaces, etc.
      //
      // Requires a transaction to create new names and namespace into the given base namespace.
      ref_istream_t(std::wistream& s, const valid_ref_t<namespace_t>& into_ns, transaction_t& transaction);

      // Get the underlying stream.
      std::wistream& get_stream() const { return my_stream; }

      // Parse an object through its reference.
      //
      // The first time an object is seen, it is output with a positive reference id.
      // Afterward, only the reference id is printed, as a negative value.
      // Empty references are printed as a zero reference id.
      const ref_istream_t& parse(ref_t<object_t>& r) const;
      const ref_istream_t& parse(weak_ref_t<object_t>& r) const;
      const ref_istream_t& parse(element_t& e) const;
      const ref_istream_t& parse(array_t& a) const;
      const ref_istream_t& parse(dict_t& d) const;
      const ref_istream_t& parse(any_t& d) const;
      const ref_istream_t& parse(object_t& o) const;
      const ref_istream_t& parse(name_t& n) const;

      // Retrieve the object reference corresponding to the id.
      const ref_t<object_t>& get_object_with_id(int64_t id) const;

      // Add the object reference corresponding to the id.
      void add_object_with_id(const ref_t<object_t>& obj, int64_t id) const;

      // Retrieve the name corresponding to the id.
      const exact_name_t& get_name_with_id(int64_t id) const;

      // Add the name corresponding to the id.
      void add_name_with_id(const exact_name_t& obj, int64_t id) const;

      // Reset the tracked object references.
      void clear();

   private:
      // Kept as mutable so that a temporary ref stream can be passed
      // as a const value to the stream operator.
      mutable std::unordered_map<int64_t, ref_t<object_t>> my_object_with_ids;

      // Kept as mutable so that a temporary ref stream can be passed
      // as a const value to the stream operator.
      mutable std::unordered_map<int64_t, exact_name_t> my_name_with_ids;

      std::wistream&             my_stream;
      transaction_t&             my_transaction;
      valid_ref_t<namespace_t>   my_target_namespace;
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
      else if constexpr (std::is_base_of<weak_ref_t<object_t>, T>())
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
      else if constexpr (std::is_base_of<any_t, T>())
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
