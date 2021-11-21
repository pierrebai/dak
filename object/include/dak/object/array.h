#pragma once

#ifndef DAK_OBJECT_ARRAY_H
#define DAK_OBJECT_ARRAY_H

#include <dak/utility/types.h>
#include <dak/object/element.h>

#include <vector>

namespace dak::object
{
   USING_DAK_UTILITY_TYPES;

   //////////////////////////////////////////////////////////////////////////
   //
   // Array. elements are indexed by an integer, beginning at zero (0).
   //
   // Indexing past the end inserts element in between.
   //
   // Indexing with negative index_t starts from the end of the array,
   // minus one being the last item.

   struct array_t
   {
      // Types used by the array: data container and iterators.
      typedef std::vector<element_t> elements_t;
      typedef elements_t::iterator iterator;
      typedef elements_t::const_iterator const_iterator;

      // Constructors.
      array_t() = default;
      array_t(const array_t &) = default;

      // Assignment. Copy the whole array.
      array_t& operator =(const array_t &) = default;

      // Append the given array.
      array_t& operator +=(const array_t &);

      // Empty array.
      static const array_t empty;

      // Number of elements in the array.
      index_t size() const;

      // Modifications to the array.
      void append(const array_t &);
      bool erase(index_t anIndex);
      element_t & insert(index_t anIndex);
      element_t & grow();

      // Element retrieval.
      element_t & operator [](index_t anIndex);
      const element_t & operator [](index_t anIndex) const;

      // Iterations over the elements.
      iterator begin();
      iterator end();
      const_iterator begin() const;
      const_iterator end() const;

      // Comparisons.
      auto operator <=> (const array_t&) const = default;

   private:
      // Make the given index positive, possibly by resizing the array.
      // Return the positive index.
      index_t make_fit(index_t i);

      // Make the given index positive if possible.
      // Return the positive index or negative if the normalization failed.
      index_t verify_fit(index_t index_t) const;

      elements_t my_elements;

      friend struct ref_t<array_t>;
   };

   DAK_ELEMENT_OPERATOR(+, array_t, element_t);
}

#endif /* DAK_OBJECT_ARRAY_H */
