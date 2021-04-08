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
   namer_stream_helper_t print(namer_stream_helper_t o, const element_t& v);
   namer_stream_helper_t print(namer_stream_helper_t o, const array_t&);
   namer_stream_helper_t print(namer_stream_helper_t o, const dict_t&);
   namer_stream_helper_t print(namer_stream_helper_t o, const object_t&);
   namer_stream_helper_t print(namer_stream_helper_t o, const modifiable_object_t&);

   template <class T>
   inline namer_stream_helper_t operator <<(namer_stream_helper_t o, const T& v)
   {
      if constexpr (std::is_base_of<name_t, T>())
      {
         o.get_stream() << (o.get_namer().find(v));
         return o;
      }
      else if constexpr (std::is_base_of<dict_t, T>())
      {
         return print(o, v);
      }
      else if constexpr (std::is_base_of<array_t, T>())
      {
         return print(o, v);
      }
      else if constexpr (std::is_base_of<element_t, T>())
      {
         return print(o, v);
      }
      else if constexpr (std::is_base_of<object_t, T>())
      {
         return print(o, v);
      }
      else if constexpr (std::is_base_of<modifiable_object_t, T>())
      {
         return print(o, v);
      }
      else
      {
         o.get_stream() << v;
         return o;
      }
   }
}

#endif /* DAK_OBJECT_STREAM_H */
