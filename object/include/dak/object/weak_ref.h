#ifndef DAK_OBJECT_WEAK_REF_H
#define DAK_OBJECT_WEAK_REF_H

#include <dak/object/ref_base.h>

namespace dak::object
{
   template <class T> struct ref_t;
   template <class T> struct valid_ref_t;
   template <class T> struct edit_ref_t;

   //////////////////////////////////////////////////////////////////////////
   //
   // A weak reference-counted pointer to a ref_counted_t object.
   // If only weak references exist, the object is cleared.
   // (Its clear() function gets called by the last strong reference.)
   // 
   // When using a weak reference, if the strong ref count is zero,
   // the weak ref acts as if the pointer were null.
   // 
   // Must be converted to a valid_ref_t to access its content.
   //
   // You cannot create an initialized instance of a smart pointer directly.
   // To create one, call the make() function on the type T. See for example:
   // object_t::make() in object.h.

   template<class T>
   struct weak_ref_t : weak_ref_base_t
   {
      // Invalid weak ref constructors.
      weak_ref_t() : weak_ref_base_t() {}

      // Copy constructors.
      weak_ref_t(const weak_ref_t<T>& other) = default;
      weak_ref_t(weak_ref_t<T>&& other) = default;

      // Copy from similar weak ref constructors.
      template <class O>
      weak_ref_t(const weak_ref_t<O>& other) : weak_ref_t(static_cast<const O*>(other.my_object)) {}

      // Copy from similar ref constructors.
      weak_ref_t(const ref_t<T>& other);

      template <class O>
      weak_ref_t(const ref_t<O>& other);

      // Copy from similar valid ref constructors.
      weak_ref_t(const valid_ref_t<T>& other);

      template <class O>
      weak_ref_t(const valid_ref_t<O>& other);

      // Copy from similar edit ref constructors.
      weak_ref_t(const edit_ref_t<T>& other);

      template <class O>
      weak_ref_t(const edit_ref_t<O>& other);

      // Copy from other weak ref.
      weak_ref_t<T>& operator =(const weak_ref_t<T>& other) = default;
      weak_ref_t<T>& operator =(weak_ref_t<T>&& other) = default;

      // Copy from similar weak ref.
      template <class O>
      weak_ref_t<T>& operator =(const weak_ref_t<O>& other) { return operator =(static_cast<const O*>(other.my_object)); }

      // Copy from similar ref.
      weak_ref_t<T>& operator =(const ref_t<T>& other);

      template <class O>
      weak_ref_t<T>& operator =(const ref_t<O>& other);

      // Copy from similar valid ref.
      weak_ref_t<T>& operator =(const valid_ref_t<T>& other);

      template <class O>
      weak_ref_t<T>& operator =(const valid_ref_t<O>& other);

      // Copy from similar edit ref.
      weak_ref_t<T>& operator =(const edit_ref_t<T>& other);

      template <class O>
      weak_ref_t<T>& operator =(const edit_ref_t<O>& other);

      // Swap with another reference.
      void swap(weak_ref_t<T>& other) { weak_ref_base_t::swap(other); }

   protected:
      weak_ref_t(const T* t) : weak_ref_base_t(t) {}
      weak_ref_t<T>& operator =(const T* t) { weak_ref_base_t::operator =(t); return *this; }

      friend T;
      friend struct element_t;
   };
}

namespace std
{
   template <class T>
   struct hash<dak::object::weak_ref_t<T>>
   {
      size_t operator()(const dak::object::weak_ref_t<T>& r) const
      {
         return static_cast<size_t>(r.hash());
      }
   };
}

#endif /* DAK_OBJECT_WEAK_REF_H */
