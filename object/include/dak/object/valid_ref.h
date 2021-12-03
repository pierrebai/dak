#ifndef DAK_OBJECT_VALID_REF_H
#define DAK_OBJECT_VALID_REF_H

#include <dak/object/ref.h>

#include <exception>

namespace dak::object
{
   //////////////////////////////////////////////////////////////////////////
   //
   // A non-null smart reference-counted pointer to a ref_counted_t object.

   template<class T>
   struct valid_ref_t : ref_t<T>
   {
      // Copy constructors.
      valid_ref_t(const valid_ref_t<T>& other) = default;
      valid_ref_t(valid_ref_t<T>&& other) = default;

      // Constructors from possibly invalid ref.
      explicit valid_ref_t(const ref_t<T>& other) : ref_t<T>(other) { if (strong_ref_base_t::is_null()) throw std::exception("invalid valid ref"); }

      // Constructors from similar valid ref.
      template <class O>
      valid_ref_t(const valid_ref_t<O>& other) : ref_t<T>(other) {}

      // Constructors from similar possibly invalid ref.
      template <class O>
      explicit valid_ref_t(const ref_t<O>& other) : ref_t<T>(other) { if (strong_ref_base_t::is_null()) throw std::exception("invalid valid ref"); }

      // Copy from other valid ref.
      valid_ref_t<T>& operator =(const valid_ref_t<T>& other) = default;
      valid_ref_t<T>& operator =(valid_ref_t<T>&& other) = default;

      // Copy from possibly invalid ref.
      valid_ref_t<T>& operator =(const ref_t<T>& other) { if (other.is_null()) throw std::exception("invalid valid ref"); ref_t<T>::operator =(other); return *this; }

      // Copy from similar valid ref.
      template <class O>
      valid_ref_t<T>& operator =(const valid_ref_t<O>& other) { ref_t<T>::operator =(other); return *this; }

      // Copy from similar possibly invalid ref.
      template <class O>
      valid_ref_t<T>& operator =(const ref_t<O>& other) { if (other.is_null()) throw std::exception("invalid valid ref"); ref_t<T>::operator =(other); return *this; }

      // Swap with another valid reference.
      void swap(valid_ref_t<T>& other) { ref_t<T>::swap(other); }

      // Do not allow modifiable access as a ref_t.
      // This prevent swapping with a ref_t or being sliced into one and then assigned to.
      // Allowing this would break the invariant that the reference is valid.
      operator ref_t<T>& () = delete;

      // Access to the referenced object.
      operator const T* () const { return static_cast<const T*>(this->my_object); }
      const T* operator ->() const { return static_cast<const T*>(this->my_object); }
      const T& operator *() const { return static_cast<const T&>(*this->my_object); }

      // Element retrieval.
      // Non-const version inserts when the name is not found.
      const element_t& operator [](const name_t& n) const;

   protected:
      valid_ref_t(const T* t) : ref_t<T>(t) {}

      friend T;
      friend struct element_t;
   };
}

namespace std
{
   template <class T>
   struct hash<dak::object::valid_ref_t<T>>
   {
      size_t operator()(const dak::object::valid_ref_t<T>& r) const
      {
         return static_cast<size_t>(r.hash());
      }
   };
}

#endif /* DAK_OBJECT_VALID_REF_H */
