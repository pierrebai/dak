#pragma once

#ifndef DAK_OBJECT_OBJECT_H
#define DAK_OBJECT_OBJECT_H

#include <dak/utility/types.h>
#include "dak/object/element.h"
#include <dak/object/name.h>
#include <dak/object/ref_counted.h>
#include <dak/object/ref.h>

#include <map>

namespace dak::object
{
   USING_DAK_UTILITY_TYPES;
   struct transaction_t;
   struct element_t;

   //////////////////////////////////////////////////////////////////////////
   //
   // Object. Lookup data when given a name.
   //
   // Automatically adds elements when referenced via the [] operator.

   struct object_t : protected ref_counted_t
   {
      // Types used by the object: data container and iterators.
      typedef std::map<name_t, element_t> elements_t;
      typedef elements_t::iterator iterator;
      typedef elements_t::const_iterator const_iterator;

      // Make a ref-counted instance.
      static edit_ref_t<object_t> make();
      static edit_ref_t<object_t> make(const object_t&);
      static edit_ref_t<object_t> make(valid_ref_t<object_t>&);

      // Constructors.
      object_t() = default;
      object_t(const object_t&) = default;

      // Assignment. Copy the whole object.
      object_t& operator =(const object_t&) = default;

      // Append the given object.
      object_t& operator +=(const object_t&);

      // Number of elements in the object.
      index_t size() const;

      // Modifications to the object.
      void append(const object_t&);
      bool erase(const name_t&);
      void swap(object_t&);

      // Element containment check.
      bool contains(const name_t&) const;

      // Element retrieval.
      // Non-const version inserts when the name is not found.
      element_t& operator [](const name_t&);
      const element_t& operator [](const name_t&) const;

      element_t& get(const name_t& n) { return (*this)[n]; }
      const element_t& get(const name_t& n) const { return (*this)[n]; }

      // Iterations over the elements.
      iterator begin();
      iterator end();
      const_iterator begin() const;
      const_iterator end() const;

      // Comparisons.
      auto operator <=> (const object_t&) const = default;

      object_t& modify(transaction_t&) const;

   protected:
      elements_t my_elements;

      friend struct ref_t<object_t>;
      friend struct valid_ref_t<object_t>;
      friend struct edit_ref_t<object_t>;
      friend struct element_t;
      friend struct transaction_t;
   };
}

namespace dak::object
{
   template<class T>
   inline const element_t& valid_ref_t<T>::operator [](const name_t& n) const { return (**this)[n]; }

   template<class T>
   inline element_t& edit_ref_t<T>::operator [](const name_t& n) const { return (**this)[n]; }
}

#endif /* DAK_OBJECT_OBJECT_H */
