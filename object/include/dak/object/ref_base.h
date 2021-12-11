#ifndef DAK_OBJECT_REF_BASE_H
#define DAK_OBJECT_REF_BASE_H

#include <dak/utility/types.h>
#include <dak/object/ref_counted.h>

namespace dak::object
{
   struct value_t;
   struct name_t;
   template <class T> struct ref_t;
   template <class T> struct weak_ref_t;

   //////////////////////////////////////////////////////////////////////////
   //
   // Base class for the smart reference-counted templated pointer.
   // Holds the pointer to the ref_counted_t objects.

   struct ref_base_t
   {
      // Verifies if the reference is valid.
      bool is_valid() const { return my_object != 0 && my_object->my_ref_count > 0; }

      // Verifies if the reference is null, or invalid.
      bool is_null() const { return my_object == 0 || my_object->my_ref_count <= 0; }

      // Comparison and hashing.
      auto operator<=>(const ref_base_t&) const = default;
      uint64_t hash() const { return reinterpret_cast<uint64_t>(my_object); }

   protected:
      // Default constructor.
      ref_base_t() = default;

      // Copy constructors and assignments.
      ref_base_t(const ref_counted_t* obj) { my_object = obj; }
      ref_base_t(const ref_base_t&) = default;
      ref_base_t& operator =(const ref_counted_t* obj) { my_object = obj; return *this; }
      ref_base_t& operator =(const ref_base_t&) = default;

      // Destructor.
      ~ref_base_t() = default;

      template <class T>
      const T* as() const { return static_cast<const T*>(is_valid() ? my_object : nullptr); }

      const ref_counted_t* my_object = nullptr;

      friend struct name_t;
      friend struct value_t;

      template <class T> friend struct ref_t;
      template <class T> friend struct valid_ref_t;
      template <class T> friend struct edit_ref_t;
      template <class T> friend struct weak_ref_t;
   };

   //////////////////////////////////////////////////////////////////////////
   //
   // Base class for the strong smart reference-counted templated pointer.
   // Manages the strong ref count.

   struct strong_ref_base_t : ref_base_t
   {
   protected:
      // Default constructor.
      strong_ref_base_t() = default;

      // Copy constructors and assignments.
      strong_ref_base_t(const ref_counted_t*);
      strong_ref_base_t(const strong_ref_base_t&);
      strong_ref_base_t& operator =(const ref_counted_t*);
      strong_ref_base_t& operator =(const strong_ref_base_t&);

      // Destructor.
      ~strong_ref_base_t();

      // Swap with another reference.
      void swap(strong_ref_base_t& other) { std::swap(my_object, other.my_object); }

   private:
      // Clear the reference. Private because some derived
      // classes guarantee that the reference is valid.
      // Only used to implement common code of op= and destructor.
      void clear();

      friend struct name_t;
      friend struct value_t;
   };

   //////////////////////////////////////////////////////////////////////////
   //
   // Base class for the strong smart reference-counted templated pointer.
   // Manages the strong ref count.

   struct weak_ref_base_t : ref_base_t
   {
   protected:
      // Default constructor.
      weak_ref_base_t() = default;

      // Copy constructors and assignments.
      weak_ref_base_t(const ref_counted_t*);
      weak_ref_base_t(const weak_ref_base_t&);
      weak_ref_base_t& operator =(const ref_counted_t*);
      weak_ref_base_t& operator =(const weak_ref_base_t&);

      // Destructor.
      ~weak_ref_base_t();

      // Swap with another reference.
      void swap(weak_ref_base_t& other) { std::swap(my_object, other.my_object); }

   private:
      // Clear the reference. Private because some derived
      // classes guarantee that the reference is valid.
      // Only used to implement common code of op= and destructor.
      void clear();

      friend struct name_t;
      friend struct value_t;
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

   template <>
   struct hash<dak::object::strong_ref_base_t>
   {
      size_t operator()(const dak::object::strong_ref_base_t& r) const
      {
         return static_cast<size_t>(r.hash());
      }
   };

   template <>
   struct hash<dak::object::weak_ref_base_t>
   {
      size_t operator()(const dak::object::weak_ref_base_t& r) const
      {
         return static_cast<size_t>(r.hash());
      }
   };
}

#endif /* DAK_OBJECT_REF_BASE_H */
