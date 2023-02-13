#pragma once

#ifndef DAK_OBJECT_CONSTANT_H
#define DAK_OBJECT_CONSTANT_H

#include <dak/utility/types.h>
#include <dak/object/value.h>
#include <dak/object/name.h>
#include <dak/object/ref_counted.h>
#include <dak/object/edit_ref.h>

#include <map>

namespace dak::object
{
   USING_DAK_UTILITY_TYPES;
   struct value_t;

   //////////////////////////////////////////////////////////////////////////
   //
   // Constant. Lookup data when given a name, but do not allow modifying it

   struct constant_t : protected ref_counted_t
   {
      // Types used by the object: data container and iterators.
      typedef std::map<name_t, value_t> values_t;
      typedef values_t::const_iterator const_iterator;

      DAK_OBJECT_REF_COUNTED(constant_t);

      // Number of values in the object.
      index_t size() const;

      // Element containment check.
      bool contains(const name_t&) const;

      // Element retrieval.
      const value_t& operator [](const name_t&) const;

      const value_t& get(const name_t& n) const { return (*this)[n]; }

      // Iterations over the values.
      const_iterator begin() const;
      const_iterator end() const;

      // Comparisons.
      auto operator <=> (const constant_t&) const = default;

   protected:
      // Reset the object.
      void clear() override;

      values_t my_values;
   };

   //////////////////////////////////////////////////////////////////////////
   //
   // Implementation of element lookup.

   template<class T>
   inline const value_t& valid_ref_t<T>::operator [](const name_t& n) const { return (**this)[n]; }
}

#endif /* DAK_OBJECT_CONSTANT_H */
