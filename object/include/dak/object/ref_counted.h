#pragma once

#ifndef DAK_OBJECT_REF_COUNTED_H
#define DAK_OBJECT_REF_COUNTED_H

#include <dak/utility/types.h>

#include <compare>

namespace dak::object
{
   struct strong_ref_base_t;
   struct element_t;

   //////////////////////////////////////////////////////////////////////////
   //
   // Reference-counted objects. Support reference counting, but can also
   // be declared on the stack or embedded in another object.
   //
   // Sub-classes of ref_counted_t *must* inherit from it privately to support the
   // restriction on reference-counting vs. stack or embedded instances.

   struct ref_counted_t
   {
      constexpr std::strong_ordering operator<=>(const ref_counted_t&) const noexcept { return std::strong_ordering::equal; }
      constexpr bool operator==(const ref_counted_t&) const noexcept { return true; }

      // Reset the object, in particular removes all references to other objects.
      virtual void clear() = 0;

   protected:
      ref_counted_t() = default;
      ref_counted_t(const ref_counted_t &);
      ref_counted_t& operator =(const ref_counted_t &);
      virtual ~ref_counted_t() = default;

   private:
      void add_ref() const;
      void sub_ref() const;

      void add_weak() const;
      void sub_weak() const;

      void check_ref() const;

      mutable int32_t my_ref_count = 0;
      mutable int32_t my_weak_count = 0;

      friend struct ref_base_t;
      friend struct strong_ref_base_t;
      friend struct weak_ref_base_t;
      friend struct element_t;
   };

   //////////////////////////////////////////////////////////////////////////
   //
   // Declare and defines typical necessary functions for dynamic objects.
   //
   // Use the macro in the public section of a class that derived
   // from ref_counted_t.
   //
   // It declares a make() function and teh necessary friends.

   #define DAK_OBJECT_REF_COUNTED(T)                              \
      static edit_ref_t<T> make()                                 \
      {                                                           \
         return edit_ref_t<T>(new T);                             \
      }                                                           \
                                                                  \
      static edit_ref_t<T> make(const T& other)                   \
      {                                                           \
         return edit_ref_t<T>(new T(other));                      \
      }                                                           \
                                                                  \
      static edit_ref_t<T> make(const valid_ref_t<T>& other)      \
      {                                                           \
         return edit_ref_t<T>(new T(other));                      \
      }                                                           \
                                                                  \
      T() = default;                                              \
      T(const T&) = default;                                      \
      T(const valid_ref_t<T>& other) : T(*other) {}               \
                                                                  \
      friend struct ref_t<T>;                                     \
      friend struct valid_ref_t<T>;                               \
      friend struct edit_ref_t<T>;                                \
      friend struct weak_ref_t<T>;                                \
      friend struct element_t;                                    \
      friend struct transaction_t

}

#endif /* DAK_OBJECT_REF_COUNTED_H */
