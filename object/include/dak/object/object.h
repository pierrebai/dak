#pragma once

#ifndef DAK_OBJECT_OBJECT_H
#define DAK_OBJECT_OBJECT_H

#include <dak/utility/types.h>
#include <dak/object/value.h>
#include <dak/object/name.h>
#include <dak/object/ref_counted.h>
#include <dak/object/edit_ref.h>

#include <map>

namespace dak::object
{
   USING_DAK_UTILITY_TYPES;
   struct transaction_t;
   struct value_t;

   //////////////////////////////////////////////////////////////////////////
   //
   // Object. Lookup data when given a name.
   //
   // Automatically adds values when referenced via the [] operator.

   struct object_t : protected ref_counted_t
   {
      // Types used by the object: data container and iterators.
      typedef std::map<name_t, value_t> values_t;
      typedef values_t::iterator iterator;
      typedef values_t::const_iterator const_iterator;

      DAK_OBJECT_REF_COUNTED(object_t);

      // Assignment. Copy the whole object.
      object_t& operator =(const object_t&) = default;

      // Append the given object.
      object_t& operator +=(const object_t&);

      // Number of values in the object.
      index_t size() const;

      // Modifications to the object.
      void append(const object_t&);
      bool erase(const name_t&);
      void swap(object_t&);

      // Reset the object.
      void clear() override;

      // Element containment check.
      bool contains(const name_t&) const;

      // Element retrieval.
      // Non-const version inserts when the name is not found.
      value_t& operator [](const name_t&);
      const value_t& operator [](const name_t&) const;

      value_t& get(const name_t& n) { return (*this)[n]; }
      const value_t& get(const name_t& n) const { return (*this)[n]; }

      // Iterations over the values.
      iterator begin();
      iterator end();
      const_iterator begin() const;
      const_iterator end() const;

      // Comparisons.
      auto operator <=> (const object_t&) const = default;

      // Modification in a transaction.
      edit_ref_t<object_t> modify(transaction_t&) const;

   protected:
      values_t my_values;
   };


   //////////////////////////////////////////////////////////////////////////
   //
   // Register any_op operations on object_t, array_t, dict_t, value_t and ref_t<object_t>.

   void register_object_ops();
}

namespace dak::object
{
   template<class T>
   inline const value_t& valid_ref_t<T>::operator [](const name_t& n) const { return (**this)[n]; }

   template<class T>
   inline value_t& edit_ref_t<T>::operator [](const name_t& n) const { return (**this)[n]; }
}

#endif /* DAK_OBJECT_OBJECT_H */
