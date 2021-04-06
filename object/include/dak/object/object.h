#pragma once

#ifndef DAK_OBJECT_OBJECT_H
#define DAK_OBJECT_OBJECT_H

#include <dak/utility/types.h>
#include <dak/object/element.h>
#include <dak/object/ref_counted.h>

#include <map>

namespace dak::object
{
   USING_DAK_UTILITY_TYPES;

   //////////////////////////////////////////////////////////////////////////
   //
   // Object. Lookup data when given a name.
   //
   // Automatically adds elements when referenced via the [] operator.

   struct modifiable_object_t : protected ref_counted_t
   {
      // Types used by the object: data container and iterators.
      typedef std::map<name_t, element_t> elements_t;
      typedef elements_t::iterator iterator;
      typedef elements_t::const_iterator const_iterator;

      // Constructors.
      modifiable_object_t() = default;
      modifiable_object_t(const modifiable_object_t &) = default;

      // Assignment. Copy the whole object.
      modifiable_object_t& operator =(const modifiable_object_t &) = default;

      // Append the given object.
      modifiable_object_t& operator +=(const modifiable_object_t &);

      // Number of elements in the object.
      index_t size() const;

      // Modifications to the object.
      void append(const modifiable_object_t &);
      bool erase(const name_t &);
      bool contains(const name_t &) const;

      // Element retrieval.
      element_t & operator [](const name_t &);
      const element_t & operator [](const name_t &) const;

      // Iterations over the elements.
      iterator begin();
      iterator end();
      const_iterator begin() const;
      const_iterator end() const;

      // Comparisons.
      auto operator <=> (const modifiable_object_t&) const = default;

   protected:
      elements_t my_elements;

      friend struct ref_t<modifiable_object_t>;

      // Make a ref-counted instance.
      static ref_t<object_t> make();
      static ref_t<object_t> make(const object_t&);

   };

   struct object_t : private modifiable_object_t
   {
      // Types used by the object: data container and iterators.
      using modifiable_object_t::elements_t;
      using modifiable_object_t::iterator;
      using modifiable_object_t::const_iterator;

      // Constructors.
      object_t() = default;
      object_t(const object_t &) = default;

      // Make a ref-counted instance.
      static ref_t<object_t> make();
      static ref_t<object_t> make(const object_t &);

      // Empty object.
      static const object_t empty;

      // Number of elements in the object.
      index_t size() const { return modifiable_object_t::size(); }

      // Modifications to the object.
      bool contains(const name_t &a_name) const { return modifiable_object_t::contains(a_name); }

      // Element retrieval.
      const element_t & operator [](const name_t & a_name) const { return modifiable_object_t::operator[](a_name); }

      // Iterations over the elements.
      const_iterator begin() const  { return modifiable_object_t::begin(); }
      const_iterator end() const { return modifiable_object_t::end(); }

      // Comparisons.
      auto operator <=> (const object_t&) const = default;

   protected:
      friend struct ref_t<object_t>;
   };
}

#endif /* DAK_OBJECT_OBJECT_H */
