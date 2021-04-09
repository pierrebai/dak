#ifndef DAK_OBJECT_REF_H
#define DAK_OBJECT_REF_H

#include <dak/utility/types.h>
#include <dak/object/name.h>
#include <dak/object/ref_counted.h>

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

   protected:
      // Constructors.
      ref_base_t() = default;

      // Copy.
      ref_base_t(ref_counted_t*);
      ref_base_t(const ref_base_t&);
      ref_base_t& operator =(ref_counted_t*);
      ref_base_t& operator =(const ref_base_t&);

      // Destructor.
      ~ref_base_t();

   protected:
      ref_counted_t* my_object = nullptr;

      friend struct name_t;
   };

   //////////////////////////////////////////////////////////////////////////
   //
   // A smart reference-counted pointer to a ref_counted_t object.
   //
   // You cannot create an initialized instance of a smart pointer directly.
   // To create one, call the make() function on the type T.
   // See for example: object_t::make() in object.h.

   template<class T> struct ref_t : ref_base_t
   {
      // Constructors.
      ref_t() : ref_base_t() {}
      ref_t(const ref_t<T>& other) : ref_base_t(other) {}

      // Copy.
      ref_t<T>& operator =(const ref_t<T>& other) { ref_base_t::operator =(other); return *this; }

      // Access to the referenced object.
      operator T*() const { return static_cast<T*>(my_object); }
      T* operator ->() const { return static_cast<T*>(my_object); }
      T& operator *() const { return static_cast<T&>(*my_object); }

      // Element retrieval.
      // Non-const version inserts when the name is not found.
      const element_t& operator [](const name_t& n) const;

   private:
      ref_t(T* t) : ref_base_t((ref_counted_t*) t) {}
      ref_t<T>& operator =(T* t) { ref_base_t::operator =(t); return *this; }

      friend T;
      friend struct name_t;
      friend struct element_t;
   };
}

#endif /* DAK_REF_H */
