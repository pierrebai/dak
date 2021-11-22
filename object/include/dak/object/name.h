#pragma once

#ifndef DAK_OBJECT_NAME_H
#define DAK_OBJECT_NAME_H

#include <dak/utility/types.h>

namespace dak::object
{
   USING_DAK_UTILITY_TYPES;

   //////////////////////////////////////////////////////////////////////////
   //
   // Name. Efficient when used as key.

   struct name_t
   {
      // Emptu name constructor.
      name_t() = default;

      // Valid name constructors.
      name_t(str_ptr_t a_label) : my_name(a_label) {}
      name_t(const text_t& a_label);

      // Destructor.
      ~name_t() = default;

      // Return the text of the name.
      str_ptr_t to_text() const { return my_name ? my_name : L""; }

      // Validity.
      bool is_valid() const { return my_name != nullptr; }

      // Comparison method.
      auto operator <=>(const name_t&) const = default;

      uint64_t hash() const { return reinterpret_cast<uint64_t>(this); }

   protected:
      str_ptr_t my_name = nullptr;

      friend struct element_t;
      friend struct dict_t;
   };

   //////////////////////////////////////////////////////////////////////////
   //
   // Hashes the name.

   struct name_hasher_t
   {
      inline uint64_t operator ()(const name_t& a_name) const
      {
         return a_name.hash();
      }
   };
}

#endif /* DAK_OBJECT_NAME */
