#pragma once

#ifndef DAK_OBJECT_EXACT_NAME_H
#define DAK_OBJECT_EXACT_NAME_H

#include <dak/object/name.h>

namespace dak::object
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Exact name. Disregard basename when comparing.
   //
   // Useful when an algorithm needs to distinguish between derived names.
   // For example, when metadata is important in an indexed container.

   struct exact_name_t : name_t
   {
      // Comparison and hash.
      std::strong_ordering operator <=>(const exact_name_t&) const;
      bool operator ==(const exact_name_t&) const;
      uint64_t hash() const;
   };


   //////////////////////////////////////////////////////////////////////////
   //
   // Hashes the name.

   struct exact_name_hasher_t
   {
      inline uint64_t operator ()(const exact_name_t& a_name) const
      {
         return a_name.hash();
      }
   };
}

namespace std
{
   template <>
   struct hash<dak::object::exact_name_t>
   {
      size_t operator()(const dak::object::exact_name_t& n) const
      {
         return static_cast<size_t>(n.hash());
      }
   };
}

#endif /* DAK_OBJECT_EXACT_NAME */
