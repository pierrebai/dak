#ifndef DAK_OBJECT_REF_H
#define DAK_OBJECT_REF_H

#include <dak/object/ref_base.h>
#include <dak/object/weak_ref.h>

namespace dak::object
{
   //////////////////////////////////////////////////////////////////////////
   //
   // A smart reference-counted pointer to a ref_counted_t object.
   // Must be converted to valid_ref_t to access its content.
   //
   // You cannot create an initialized instance of a smart pointer directly.
   // To create one, call the make() function on the type T. See for example:
   // object_t::make() in object.h.

   template<class T>
   struct ref_t : strong_ref_base_t
   {
      // Invalid ref constructors.
      ref_t() : strong_ref_base_t() {}

      // Copy constructors.
      ref_t(const ref_t<T>& other) = default;
      ref_t(ref_t<T>&& other) = default;

      // Copy from similar ref constructors.
      template <class O>
      ref_t(const ref_t<O>& other) : ref_t(static_cast<const O*>(other.my_object)) {}

      // Constructors from a weak reference.
      explicit ref_t(const weak_ref_t<T>& other) : ref_t<T>(static_cast<const T*>(other.is_valid() ? other.my_object : nullptr)) {}

      template <class O>
      explicit ref_t(const weak_ref_t<O>& other) : ref_t<T>(static_cast<const O*>(other.is_valid() ? other.my_object : nullptr)) {}

      // Copy from other ref.
      ref_t<T>& operator =(const ref_t<T>& other) = default;
      ref_t<T>& operator =(ref_t<T>&& other) = default;

      // Copy from a weak reference.
      ref_t<T>& operator =(const weak_ref_t<T>& other) { return operator =(static_cast<const T*>(other.is_valid() ? other.my_object : nullptr)); }

      template <class O>
      ref_t<T>& operator =(const weak_ref_t<O>& other) { return operator =(static_cast<const O*>(other.is_valid() ? other.my_object : nullptr)); }

      // Copy from similar ref.
      template <class O>
      ref_t<T>& operator =(const ref_t<O>& other) { return operator =(static_cast<const O*>(other.my_object)); }

      // Swap with another reference.
      void swap(ref_t<T>& other) { strong_ref_base_t::swap(other); }

   protected:
      ref_t(const T* t) : strong_ref_base_t(t) {}
      ref_t<T>& operator =(const T* t) { strong_ref_base_t::operator =(t); return *this; }

      friend T;
      friend struct element_t;
   };

   template <class T>
   weak_ref_t<T>::weak_ref_t(const ref_t<T>& other) : weak_ref_t(static_cast<const T*>(other.my_object)) {}

   template <class T>
   template <class O>
   weak_ref_t<T>::weak_ref_t(const ref_t<O>& other) : weak_ref_t(static_cast<const O*>(other.my_object)) {}

   template <class T>
   weak_ref_t<T>& weak_ref_t<T>::operator =(const ref_t<T>& other) { return operator =(static_cast<const T*>(other.my_object)); }

   template <class T>
   template <class O>
   weak_ref_t<T>& weak_ref_t<T>::operator =(const ref_t<O>& other) { return operator =(static_cast<const O*>(other.my_object)); }

}

namespace std
{
   template <class T>
   struct hash<dak::object::ref_t<T>>
   {
      size_t operator()(const dak::object::ref_t<T>& r) const
      {
         return static_cast<size_t>(r.hash());
      }
   };
}

#endif /* DAK_OBJECT_REF_H */
