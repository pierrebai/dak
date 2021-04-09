#pragma once

#ifndef DAK_OBJECT_STREAM_H
#define DAK_OBJECT_STREAM_H

#include <dak/utility/types.h>
#include <dak/object/array.h>
#include <dak/object/dict.h>
#include <dak/object/namer.h>
#include <dak/object/object.h>

#include <iostream>
#include <type_traits>
#include <map>

namespace dak::object
{
   USING_DAK_UTILITY_TYPES;

   //////////////////////////////////////////////////////////////////////////
   //
   // Helper to output names and objects into a stream.

   struct stream_helper_t
   {
      stream_helper_t(std::wostream& s, const namer_t& n) : my_stream(s), my_namer(n) {}

      std::wostream& get_stream() const { return my_stream; }
      const namer_t& get_namer() const { return my_namer; }

      int64_t get_object_id(const ref_t<const object_t>& object) const;
      void clear();

   private:
      std::wostream& my_stream;
      const namer_t& my_namer;

      mutable std::map<const ref_t<const object_t>, int64_t> my_object_ids;
   };


   //////////////////////////////////////////////////////////////////////////
   //
   // Stream operations on known data types.
   //
   // By default, uses the standard output stream. Specialized for our own types.

   stream_helper_t operator <<(std::wostream& o, const namer_t&);
   const stream_helper_t& print(const stream_helper_t& nsh, const element_t& e);
   const stream_helper_t& print(const stream_helper_t& nsh, const array_t& a);
   const stream_helper_t& print(const stream_helper_t& nsh, const dict_t& d);
   const stream_helper_t& print(const stream_helper_t& nsh, const object_t& o);
   const stream_helper_t& print(const stream_helper_t& nsh, const ref_t<const object_t>& o);

   template <class T>
   inline const stream_helper_t& operator <<(const stream_helper_t& nsh, const T& v)
   {
      if constexpr (std::is_base_of<name_t, T>())
      {
         nsh.get_stream() << (nsh.get_namer().find(v));
         return nsh;
      }
      else if constexpr (std::is_base_of<dict_t, T>())
      {
         return print(nsh, v);
      }
      else if constexpr (std::is_base_of<array_t, T>())
      {
         return print(nsh, v);
      }
      else if constexpr (std::is_base_of<element_t, T>())
      {
         return print(nsh, v);
      }
      else if constexpr (std::is_base_of<object_t, T>())
      {
         return print(nsh, v);
      }
      else if constexpr (std::is_base_of<ref_t<const object_t>, T>())
      {
         return print(nsh, v);
      }
      else
      {
         nsh.get_stream() << v;
         return nsh;
      }
   }
}

#endif /* DAK_OBJECT_STREAM_H */
