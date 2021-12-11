
#ifndef DAK_OBJECT_DICT_H
#define DAK_OBJECT_DICT_H

#include <dak/utility/types.h>
#include <dak/object/value.h>
#include <dak/object/ref_counted.h>

#include <map>

namespace dak::object
{
   USING_DAK_UTILITY_TYPES;

   //////////////////////////////////////////////////////////////////////////
   //
   // Dictionary. Lookup data when given a name.
   //
   // Automatically adds values when referenced via the [] operator.

   struct dict_t
   {
      // Types used by the dictionary: data container and iterators.
      typedef std::map<name_t, value_t> values_t;
      typedef values_t::iterator iterator;
      typedef values_t::const_iterator const_iterator;

      // Constructors.
      dict_t() = default;
      dict_t(const dict_t&) = default;

      // Assignment. Copy the whole dictionary.
      dict_t& operator =(const dict_t&) = default;

      // Append the given dictionary.
      dict_t& operator +=(const dict_t &);

      // Empty dictionary.
      static const dict_t empty;

      // Number of values in the dictionary.
      index_t size() const;

      // Modifications to the dictionary.
      void append(const dict_t &);
      bool erase(const name_t &);
      bool contains(const name_t &) const;

      // Element retrieval.
      value_t & operator [](const name_t &);
      const value_t & operator [](const name_t &) const;

      // Iterations over the values.
      iterator begin();
      iterator end();
      const_iterator begin() const;
      const_iterator end() const;

      // Comparisons.
      auto operator <=> (const dict_t&) const = default;

   protected:
      values_t my_values;

      friend struct ref_t<dict_t>;
   };

   DAK_ELEMENT_OPERATOR(+, dict_t, value_t);
}

#endif /* DAK_OBJECT_DICT_H */
