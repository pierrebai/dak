#pragma once

#ifndef DAK_OBJECT_ARRAY_H
#define DAK_OBJECT_ARRAY_H

#include <dak/utility/types.h>
#include <dak/object/value.h>

#include <vector>

namespace dak::object
{
   USING_DAK_UTILITY_TYPES;

   //////////////////////////////////////////////////////////////////////////
   //
   // Array. values are indexed by an integer, beginning at zero (0).
   //
   // Indexing past the end inserts value in between.
   //
   // Indexing with negative index_t starts from the end of the array,
   // minus one being the last item.

   struct array_t
   {
      // Types used by the array: data container and iterators.
      typedef std::vector<value_t> values_t;
      typedef values_t::iterator iterator;
      typedef values_t::const_iterator const_iterator;

      // Constructors.
      array_t() = default;
      array_t(const array_t &) = default;

      // Assignment. Copy the whole array.
      array_t& operator =(const array_t &) = default;

      // Append the given array.
      array_t& operator +=(const array_t &);

      // Empty array.
      static const array_t empty;

      // Number of values in the array.
      index_t size() const;

      // Modifications to the array.
      void append(const array_t &);
      void append(const value_t&);
      bool erase(index_t anIndex);
      value_t & insert(index_t anIndex);
      value_t & grow();

      // Element retrieval.
      value_t & operator [](index_t anIndex);
      const value_t & operator [](index_t anIndex) const;

      // Iterations over the values.
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

      values_t my_values;

      friend struct ref_t<array_t>;
   };

   DAK_ELEMENT_OPERATOR(+, array_t, value_t);
}

#endif /* DAK_OBJECT_ARRAY_H */
