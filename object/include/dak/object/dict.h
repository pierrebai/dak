#pragma once

#ifndef DAK_OBJECT_DICT_H
#define DAK_OBJECT_DICT_H

#include <dak/utility/types.h>
#include <dak/object/element.h>
#include <dak/object/ref_counted.h>

#include <map>

namespace dak::object
{
   USING_DAK_UTILITY_TYPES;

   //////////////////////////////////////////////////////////////////////////
   //
   // Dictionary. Lookup data when given a name.
   //
   // Automatically adds elements when referenced via the [] operator.

   struct dict_t : private ref_counted_t
   {
      // Types used by the dictionary: data container and iterators.
      typedef std::map<name_t, element_t> elements_t;
      typedef elements_t::iterator iterator;
      typedef elements_t::const_iterator const_iterator;

      // Constructors.
      dict_t() = default;
      dict_t(const dict_t&) = default;

      // Assignment. Copy the whole dictionary.
      dict_t& operator =(const dict_t&) = default;

      // Append the given dictionary.
      dict_t& operator +=(const dict_t &);

      // Make a ref-counted instance.
      static ref_t<dict_t> make();
      static ref_t<dict_t> make(const dict_t &);

      // Empty dictionary.
      static const dict_t empty;

      // Number of elements in the dictionary.
      index_t size() const;

      // Modifications to the dictionary.
      void append(const dict_t &);
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
      auto operator <=> (const dict_t&) const = default;

   protected:
      elements_t my_elements;

      friend struct ref_t<dict_t>;
   };

   DAK_ELEMENT_OPERATOR(+, dict_t, element_t);
}

#endif /* DAK_OBJECT_DICT_H */
