#ifndef DAK_OBJECT_EDIT_REF_H
#define DAK_OBJECT_EDIT_REF_H

#include <dak/object/valid_ref.h>
#include <dak/object/transaction.h>

namespace dak::object
{
   struct transaction_t;

   //////////////////////////////////////////////////////////////////////////
   //
   // A non-null smart reference-counted pointer to a modifiable ref_counted_t object.

   template<class T> struct edit_ref_t : valid_ref_t<T>
   {
      // Copy constructors.
      edit_ref_t(const edit_ref_t<T>& other) = default;
      edit_ref_t(edit_ref_t<T> && other) = default;

      // Constructors from valid ref and transaction.
      explicit edit_ref_t(const valid_ref_t<T>& other, transaction_t& trans) : valid_ref_t<T>(other) { trans.add(*this); }

      // Constructors from possibly invalid ref and transaction.
      explicit edit_ref_t(const ref_t<T>& other, transaction_t& trans) : valid_ref_t<T>(other) { trans.add(*this); }

      // Constructors from weak ref and transaction.
      explicit edit_ref_t(const weak_ref_t<T>& other, transaction_t& trans) : valid_ref_t<T>(other) { trans.add(*this); }

      // Constructors from similar edit ref.
      template <class O>
      edit_ref_t(const edit_ref_t<O>& other) : valid_ref_t<T>(other) {}

      // Constructors from similar valid ref and transaction.
      template <class O>
      explicit edit_ref_t(const valid_ref_t<O>& other, transaction_t& trans) : valid_ref_t<T>(other) { trans.add(*this); }

      // Constructors from similar possibly invalid ref and transaction.
      template <class O>
      explicit edit_ref_t(const ref_t<O>& other, transaction_t& trans) : valid_ref_t<T>(other) { trans.add(*this); }

      // Constructors from similar weak ref and transaction.
      template <class O>
      explicit edit_ref_t(const weak_ref_t<O>& other, transaction_t& trans) : valid_ref_t<T>(other) { trans.add(*this); }

      // Copy from edit ref.
      //
      // Note: do *not* provide assigment operator for other ref types
      //       as we need a transaction to make an edit ref.
      edit_ref_t<T>& operator =(const edit_ref_t<T>& other) = default;
      edit_ref_t<T>& operator =(edit_ref_t<T>&& other) = default;

      // Copy from similar edit ref.
      //
      // Note: do *not* provide assigment operator for other ref types
      //       as we need a transaction to make an edit ref.
      template <class O>
      edit_ref_t<T>& operator =(const edit_ref_t<O>& other) { valid_ref_t<T>::operator =(other); return *this; }

      // Swap with another edit reference.
      void swap(edit_ref_t<T>& other) { ref_t::swap(other); }

      // Do not allow modifiable access as a ref_t or valid_ref_t.
      // This prevent swapping with a ref_t or valid_ref_t or
      // being sliced into one and then assigned to.
      // Allowing this would break the invariant that the object was added to a transation_t
      // or that the reference is valid.
      operator ref_t<T>& () = delete;
      operator valid_ref_t<T>& () = delete;

      // Access to the referenced object.
      operator T* () const { return const_cast<T*>(static_cast<const T*>(this->my_object)); }
      T* operator ->() const { return const_cast<T*>(static_cast<const T*>(this->my_object)); }
      T& operator *() const { return const_cast<T&>(static_cast<const T&>(*this->my_object)); }

      // Element retrieval.
      // Non-const version inserts when the name is not found.
      value_t& operator [](const name_t& n) const;

   protected:
      edit_ref_t(T* t) : valid_ref_t<T>(t) {}
      edit_ref_t<T>& operator =(const T* t) { valid_ref_t<T>::operator =(t); return *this; }

      friend T;
      friend struct value_t;
   };


   //////////////////////////////////////////////////////////////////////////
   //
   // Now we can implement the weak_ref_t functions taking edit_ref_t.

   template <class T>
   weak_ref_t<T>::weak_ref_t(const edit_ref_t<T>& other) : weak_ref_t(other.as<T>()) {}

   template <class T>
   template <class O>
   weak_ref_t<T>::weak_ref_t(const edit_ref_t<O>& other) : weak_ref_t(other.as<O>()) {}

   template <class T>
   weak_ref_t<T>& weak_ref_t<T>::operator =(const edit_ref_t<T>& other) { return operator =(other.as<T>()); }

   template <class T>
   template <class O>
   weak_ref_t<T>& weak_ref_t<T>::operator =(const edit_ref_t<O>& other) { return operator =(other.as<O>()); }

}

namespace std
{
   template <class T>
   struct hash<dak::object::edit_ref_t<T>>
   {
      size_t operator()(const dak::object::edit_ref_t<T>& r) const
      {
         return static_cast<size_t>(r.hash());
      }
   };
}

#endif /* DAK_OBJECT_EDIT_REF_H */
