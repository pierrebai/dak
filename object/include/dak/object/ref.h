#ifndef DAK_OBJECT_REF_H
#define DAK_OBJECT_REF_H

#include <dak/object/ref_base.h>
#include <dak/object/weak_ref.h>

namespace dak::object
{
   struct value_t;

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
      ref_t(const weak_ref_t<T>& other) : ref_t<T>(other.as<T>()) {}

      template <class O>
      ref_t(const weak_ref_t<O>& other) : ref_t<T>(other.as<O>()) {}

      // Constructor from value_t.
      ref_t(const value_t& other) { *this = other; }

      // Copy from other ref.
      ref_t<T>& operator =(const ref_t<T>& other) = default;
      ref_t<T>& operator =(ref_t<T>&& other) = default;

      // Copy from similar ref.
      template <class O>
      ref_t<T>& operator =(const ref_t<O>& other) { return operator =(other.as<O>()); }

      // Copy from a weak reference.
      ref_t<T>& operator =(const weak_ref_t<T>& other) { return operator =(other.as<T>()); }

      template <class O>
      ref_t<T>& operator =(const weak_ref_t<O>& other) { return operator =(other.as<O>()); }

      // Copy from value_t.
      ref_t<T>& operator =(const value_t& other);

      // Swap with another reference.
      void swap(ref_t<T>& other) { strong_ref_base_t::swap(other); }

   protected:
      ref_t(const T* t) : strong_ref_base_t(t) {}
      ref_t<T>& operator =(const T* t) { strong_ref_base_t::operator =(t); return *this; }

      template <class O>
      ref_t(const O* t) : strong_ref_base_t(dynamic_cast<const T*>(t)) {}

      template <class O>
      ref_t<T>& operator =(const O* t) { strong_ref_base_t::operator =(dynamic_cast<const T *>(t)); return *this; }

      friend T;
      friend struct value_t;
   };


   //////////////////////////////////////////////////////////////////////////
   //
   // Now we can implement the weak_ref_t functions taking ref_t.

   template <class T>
   weak_ref_t<T>::weak_ref_t(const ref_t<T>& other) : weak_ref_t(other.as<T>()) {}

   template <class T>
   template <class O>
   weak_ref_t<T>::weak_ref_t(const ref_t<O>& other) : weak_ref_t(other.as<O>()) {}

   template <class T>
   weak_ref_t<T>& weak_ref_t<T>::operator =(const ref_t<T>& other) { return operator =(other.as<T>()); }

   template <class T>
   template <class O>
   weak_ref_t<T>& weak_ref_t<T>::operator =(const ref_t<O>& other) { return operator =(other.as<O>()); }


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
