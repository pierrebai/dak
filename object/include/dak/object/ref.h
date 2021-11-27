#ifndef DAK_OBJECT_REF_H
#define DAK_OBJECT_REF_H

#include <dak/utility/types.h>
#include <dak/object/ref_counted.h>
#include <dak/object/transaction.h>

#include <exception>

namespace dak::object
{
   struct element_t;
   struct name_t;
   struct transaction_t;

   //////////////////////////////////////////////////////////////////////////
   //
   // Base class for the smart reference-counted templated pointer.
   // Holds references to ref_counted_t objects.
   //
   // Holds the common code.

   struct ref_base_t
   {
      // Verifies if the reference is valid.
      bool is_valid() const { return my_object != 0; }

      // Verifies if the reference is null, or invalid.
      bool is_null() const { return my_object == 0; }

      // Comparison and hashing.
      auto operator<=>(const ref_base_t&) const = default;
      uint64_t hash() const { return reinterpret_cast<uint64_t>(my_object); }

   protected:
      // Default constructor.
      ref_base_t() = default;

      // Copy constructors and assignments.
      ref_base_t(const ref_counted_t*);
      ref_base_t(const ref_base_t&);
      ref_base_t& operator =(const ref_counted_t*);
      ref_base_t& operator =(const ref_base_t&);

      // Destructor.
      ~ref_base_t();

   protected:
      const ref_counted_t* my_object = nullptr;

      friend struct name_t;
      friend struct element_t;

   private:
      // Clear the reference. Private because some derived
      // classes guarantee that the reference is valid.
      // Only used to implement common code of op= and destructor.
      void clear();
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
      // Invalid ref constructors.
      ref_t() : ref_base_t() {}

      // Copy constructors.
      ref_t(const ref_t<T>& other) : ref_base_t(other) {}

      // Copy from similar ref constructors.
      template <class O>
      ref_t(const ref_t<O>& other) : ref_t(static_cast<const O *>(other.my_object)) {}

      // Copy from other ref.
      ref_t<T>& operator =(const ref_t<T>& other) { ref_base_t::operator =(other); return *this; }

      // Copy from similar ref.
      template <class O>
      ref_t<T>& operator =(const ref_t<O>& other) { return operator =(static_cast<const O*>(other.my_object)); }

   protected:
      ref_t(const T* t) : ref_base_t(t) {}
      ref_t<T>& operator =(const T* t) { ref_base_t::operator =(t); return *this; }

      friend T;
      friend struct element_t;
   };


   //////////////////////////////////////////////////////////////////////////
   //
   // A non-null smart reference-counted pointer to a ref_counted_t object.

   template<class T> struct valid_ref_t : ref_t<T>
   {
      // Copy constructors.
      valid_ref_t(const valid_ref_t<T>& other) : ref_t<T>(other) {}

      // Constructors from possibly invalid ref.
      explicit valid_ref_t(const ref_t<T>& other) : ref_t<T>(other) { if (ref_base_t::is_null()) throw std::exception("invalid valid ref"); }

      // Constructors from similar valid ref.
      template <class O>
      valid_ref_t(const valid_ref_t<O>& other) : ref_t<T>(other) {}

      // Constructors from similar possibly invalid ref.
      template <class O>
      explicit valid_ref_t(const ref_t<O>& other) : ref_t<T>(other) { if (ref_base_t::is_null()) throw std::exception("invalid valid ref"); }

      // Copy from other valid ref.
      valid_ref_t<T>& operator =(const valid_ref_t<T>& other) { ref_t<T>::operator =(other); return *this; }

      // Copy from possibly invalid ref.
      valid_ref_t<T>& operator =(const ref_t<T>& other) { if (other.is_null()) throw std::exception("invalid valid ref"); ref_t<T>::operator =(other); return *this; }

      // Copy from similar valid ref.
      template <class O>
      valid_ref_t<T>& operator =(const valid_ref_t<O>& other) { ref_t<T>::operator =(other); return *this; }

      // Copy from similar possibly invalid ref.
      template <class O>
      valid_ref_t<T>& operator =(const ref_t<O>& other) { if (other.is_null()) throw std::exception("invalid valid ref"); ref_t<T>::operator =(other); return *this; }

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


   //////////////////////////////////////////////////////////////////////////
   //
   // A non-null smart reference-counted pointer to a modifiable ref_counted_t object.

   template<class T> struct edit_ref_t : valid_ref_t<T>
   {
      // Copy constructors.
      edit_ref_t(const edit_ref_t<T>& other) : valid_ref_t<T>(other) {}

      // Constructors from valid ref and transaction.
      explicit edit_ref_t(const valid_ref_t<T>& other, transaction_t& trans) : valid_ref_t<T>(other) { trans.add(*this); }

      // Constructors from possibly invalid ref and transaction.
      explicit edit_ref_t(const ref_t<T>& other, transaction_t& trans) : valid_ref_t<T>(other) { trans.add(*this); }

      // Constructors from similar edit ref.
      template <class O>
      edit_ref_t(const edit_ref_t<O>& other) : valid_ref_t<T>(other) {}

      // Constructors from similar valid ref and transaction.
      template <class O>
      explicit edit_ref_t(const valid_ref_t<O>& other, transaction_t& trans) : valid_ref_t<T>(other) { trans.add(*this); }

      // Constructors from similar possibly invalid ref and transaction.
      template <class O>
      explicit edit_ref_t(const ref_t<O>& other, transaction_t& trans) : valid_ref_t<T>(other) { trans.add(*this); }

      // Copy from edit ref.
      edit_ref_t<T>& operator =(const edit_ref_t<T>& other) { valid_ref_t<T>::operator =(other); return *this; }

      // Copy from similar edit ref.
      template <class O>
      edit_ref_t<T>& operator =(const edit_ref_t<O>& other) { valid_ref_t<T>::operator =(other); return *this; }

      // Access to the referenced object.
      operator T* () const { return const_cast<T*>(static_cast<const T*>(this->my_object)); }
      T* operator ->() const { return const_cast<T*>(static_cast<const T*>(this->my_object)); }
      T& operator *() const { return const_cast<T&>(static_cast<const T&>(*this->my_object)); }

      // Element retrieval.
      // Non-const version inserts when the name is not found.
      element_t& operator [](const name_t& n) const;

   protected:
      edit_ref_t(T* t) : valid_ref_t<T>(t) {}

      friend T;
      friend struct element_t;
   };
}

namespace std
{
   template <>
   struct hash<dak::object::ref_base_t>
   {
      size_t operator()(const dak::object::ref_base_t& r) const
      {
         return static_cast<size_t>(r.hash());
      }
   };
}

#endif /* DAK_REF_H */
