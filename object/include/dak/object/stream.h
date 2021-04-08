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

namespace dak::object
{
   USING_DAK_UTILITY_TYPES;

   //////////////////////////////////////////////////////////////////////////
   //
   // Helper to output names into a stream.

   struct namer_stream_helper_t
   {
      namer_stream_helper_t(std::wostream& s, const namer_t& n) : my_stream(s), my_namer(n) {}

      std::wostream& get_stream() const { return my_stream; }
      const namer_t& get_namer() const { return my_namer; }

   private:
      std::wostream& my_stream;
      const namer_t& my_namer;
   };


   //////////////////////////////////////////////////////////////////////////
   //
   // Stream operations on known data types.
   //
   // By default, uses the standard output stream. Specialized for our own types.

   namer_stream_helper_t operator <<(std::wostream& o, const namer_t&);
   const namer_stream_helper_t& print(const namer_stream_helper_t& nsh, const element_t& e);
   const namer_stream_helper_t& print(const namer_stream_helper_t& nsh, const array_t& a);
   const namer_stream_helper_t& print(const namer_stream_helper_t& nsh, const dict_t& d);
   const namer_stream_helper_t& print(const namer_stream_helper_t& nsh, const object_t& o);

   template <class T>
   inline const namer_stream_helper_t& operator <<(const namer_stream_helper_t& nsh, const T& v)
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
      else
      {
         nsh.get_stream() << v;
         return nsh;
      }
   }
}

#endif /* DAK_OBJECT_STREAM_H */
