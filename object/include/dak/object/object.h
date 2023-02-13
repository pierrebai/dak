#pragma once

#ifndef DAK_OBJECT_OBJECT_H
#define DAK_OBJECT_OBJECT_H

#include <dak/object/constant.h>

namespace dak::object
{
   struct transaction_t;

   //////////////////////////////////////////////////////////////////////////
   //
   // Object. Lookup data when given a name.
   //
   // Automatically adds values when referenced via the [] operator.

   struct object_t : constant_t
   {
      // Types used by the object: data container and iterators.
      typedef values_t::iterator iterator;

      DAK_OBJECT_REF_COUNTED(object_t);

      // Assignment. Copy the whole object.
      object_t& operator =(const object_t&) = default;

      // Append the given object.
      object_t& operator +=(const object_t&);

      // Modifications to the object.
      void append(const object_t&);
      bool erase(const name_t&);
      void swap(object_t&);

      // Reset the object.
      using constant_t::clear;

      // Element retrieval.
      // Non-const version inserts when the name is not found.
      value_t& operator [](const name_t&);
      const value_t& operator [](const name_t& n) const { return constant_t::operator [](n); }

      value_t& get(const name_t& n) { return (*this)[n]; }
      const value_t& get(const name_t& n) const { return (*this)[n]; }

      // Iterations over the values.
      iterator begin();
      iterator end();
      const_iterator begin() const { return constant_t::begin(); }
      const_iterator end() const { return constant_t::end(); }

      // Comparisons.
      auto operator <=> (const object_t&) const = default;

      // Modification in a transaction.
      edit_ref_t<object_t> modify(transaction_t&) const;
   };


   //////////////////////////////////////////////////////////////////////////
   //
   // Register any_op operations on object_t, array_t, dict_t, value_t and ref_t<object_t>.

   void register_object_ops();

   //////////////////////////////////////////////////////////////////////////
   //
   // Implementation of element lookup.

   template<class T>
   inline value_t& edit_ref_t<T>::operator [](const name_t& n) const { return (**this)[n]; }
}

#endif /* DAK_OBJECT_OBJECT_H */
