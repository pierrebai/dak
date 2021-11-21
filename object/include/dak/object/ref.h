#ifndef DAK_OBJECT_REF_H
#define DAK_OBJECT_REF_H

#include <dak/utility/types.h>
#include <dak/object/name.h>
#include <dak/object/ref_counted.h>

#include <exception>

namespace dak::object
{
   struct element_t;
   struct name_t;

   //////////////////////////////////////////////////////////////////////////
   //
   // Base class for the smart reference-counted templated pointer.
   // Holds references to ref_counted_t objects.
   //
   // Holds the common code.

   struct ref_base_t
   {
      void clear();
      bool is_valid() const;
      bool is_null() const;

      auto operator<=>(const ref_base_t&) const = default;

   protected:
      // Constructors.
      ref_base_t() = default;

      // Copy.
      ref_base_t(const ref_counted_t*);
      ref_base_t(const ref_base_t&);
      ref_base_t& operator =(const ref_counted_t*);
      ref_base_t& operator =(const ref_base_t&);

      // Destructor.
      ~ref_base_t();

   protected:
      const ref_counted_t* my_object = nullptr;

      friend struct name_t;
   };

   //////////////////////////////////////////////////////////////////////////
   //
   // A smart reference-counted pointer to a ref_counted_t object.
   // Must be converted to valid_ref_t to access its content.
   //
   // You cannot create an initialized instance of a smart pointer directly.
   // To create one, call the make() function on the type T.
   // See for example: object_t::make() in object.h.

   template<class T> struct ref_t : ref_base_t
   {
      // Constructors.
      ref_t() : ref_base_t() {}
      ref_t(const ref_t<T>& other) : ref_base_t(other) {}

      template <class OTHER>
      ref_t(const ref_t<OTHER>& other) : ref_t(static_cast<const OTHER *>(other.my_object)) {}

      // Copy.
      ref_t<T>& operator =(const ref_t<T>& other) { ref_base_t::operator =(other); return *this; }

   private:
      ref_t(const T* t) : ref_base_t(t) {}
      ref_t<T>& operator =(const T* t) { ref_base_t::operator =(t); return *this; }

      friend T;
      friend struct name_t;
      friend struct element_t;
   };


   //////////////////////////////////////////////////////////////////////////
   //
   // A non-null smart reference-counted pointer to a ref_counted_t object.

   template<class T> struct valid_ref_t : ref_t<T>
   {
      // Constructors.
      valid_ref_t(const valid_ref_t<T>& other) : ref_t<T>(other) {}
      explicit valid_ref_t(const ref_t<T>& other) : ref_t<T>(other) { if (ref_base_t::is_null()) throw std::exception("invalid valid ref"); }

      template <class OTHER>
      valid_ref_t(const valid_ref_t<OTHER>& other) : ref_t<T>(other) {}

      template <class OTHER>
      explicit valid_ref_t(const ref_t<OTHER>& other) : ref_t<T>(other) { if (ref_base_t::is_null()) throw std::exception("invalid valid ref"); }

      // Copy.
      valid_ref_t<T>& operator =(const valid_ref_t<T>& other) { ref_t<T>::operator =(other); return *this; }
      valid_ref_t<T>& operator =(const ref_t<T>& other) { if (other.is_null()) throw std::exception("invalid valid ref"); ref_t<T>::operator =(other); return *this; }

      // Access to the referenced object.
      operator const T* () const { return static_cast<const T*>(this->my_object); }
      const T* operator ->() const { return static_cast<const T*>(this->my_object); }
      const T& operator *() const { return static_cast<const T&>(*this->my_object); }

      // Element retrieval.
      // Non-const version inserts when the name is not found.
      const element_t& operator [](const name_t& n) const;
   };
}

#endif /* DAK_REF_H */
