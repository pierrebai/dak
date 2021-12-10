#pragma once

#ifndef DAK_OBJECT_ELEMENT_H
#define DAK_OBJECT_ELEMENT_H

#include <dak/utility/types.h>
#include <dak/object/name.h>
#include <dak/object/similar.h>
#include <dak/any_op/convert_op.h>

#include <typeinfo>
#include <compare>

namespace dak::object
{
   USING_DAK_UTILITY_TYPES;
   struct array_t;
   struct dict_t;
   struct object_t;

   using datatype_t = const std::type_info&;

//////////////////////////////////////////////////////////////////////////
   //
   // Element in arrays and dictionaries. Can contain any data,
   // as the value are held in a std::any (any_t).
   //
   // All types are always copied when assigned to, so beware of assigning
   // dictionaries and arrays!
   //
   // When implicitely converted to a type, the element type is not changed.
   // The value is converted to the closest corresponding value.
   //
   // (All integer-like types are equivalent, so you can read a boolean
   // from an integer. Same for double-like types, float and double.)
   //
   // Also, when converted to a type via the ensure() or reset() functions,
   // if the element was not of that type, it is changed into it. So beware
   // of changing a dict_t into an integer, as the dict_t content is lost!
   //
   // To support access to elements containg dict_t and array_t, the element
   // provides the [] operator to access the sub-elements of the container.
   // Again, the element will be automatically converted, so if it was not
   // an array_t of a dict_t, its previous content will be lost.

   struct element_t
   {
      static const element_t empty;

      // Create an element of an unfixed type, potentially pre-initialized to a value.
      element_t() = default;

      // Copy the given element.
      element_t(const element_t&) = default;

      // Constructors taking values.

      template <class T>
      explicit element_t(const T& value) : my_data(value) {}

      // Constructors taking values that we want to modify.

      explicit element_t(str_ptr_t value) : element_t(text_t(value ? value : L"")) {}

      template <class T>
      explicit element_t(const valid_ref_t<T>& value) : my_data(ref_t<T>(value)) {}

      template <class T>
      explicit element_t(const edit_ref_t<T>& value) : my_data(ref_t<T>(value)) {}

      ~element_t() = default;

      // Assignments. Changes the type if needed.
      element_t& operator =(const element_t&) = default;

      // Assignments of various types. Changes the type if needed.

      template <class T>
      element_t& operator =(const T& value) { my_data = value; return *this; }

      // Assignment of a few types that we want to modify before assignment.

      element_t& operator =(str_ptr_t value) { my_data = text_t(value ? value : L""); return *this; }

      template <class T>
      element_t& operator =(const valid_ref_t<T> value) { my_data = ref_t<T>(value); return *this; }

      template <class T>
      element_t& operator =(const edit_ref_t<T> value) { my_data = ref_t<T>(value); return *this; }

      // Verify if there is any data.
      // TODO: create a is_valid() any_op.
      bool is_valid() const { return my_data.has_value(); }

      // Data access. Does not change the type.

      template <class T>
      T as() const { return any_op::convert<T>(my_data); }

      bool as_boolean() const { return as<bool>(); }
      int64_t as_integer() const { return as<int64_t>(); }
      ref_t<object_t> as_ref() const { return as<ref_t<object_t>>(); }
      weak_ref_t<object_t> as_weak_ref() const { return as<weak_ref_t<object_t>>(); }
      name_t as_name() const { return as<name_t>(); }
      double as_real() const { return as<double>(); }
      const array_t& as_array() const;
      const dict_t& as_dict() const;
      const text_t& as_text() const;
      const any_t& as_data() const { return my_data; }

      operator char() const { return as<char>(); }
      operator wchar_t() const { return as<wchar_t>(); }
      operator text_t() const { return as<text_t>(); }
      operator bool() const { return as<bool>(); }
      operator int16_t() const { return as<int16_t>(); }
      operator int32_t() const { return as<int32_t>(); }
      operator int64_t() const { return as<int64_t>(); }
      operator uint16_t() const { return as<uint16_t>(); }
      operator uint32_t() const { return as<uint32_t>(); }
      operator uint64_t() const { return as<uint64_t>(); }
      operator float() const { return as<float>(); }
      operator double() const { return as<double>(); }
      operator const array_t &() const { return as_array(); }
      operator const dict_t &() const { return as_dict(); }
      operator name_t() const { return as<name_t>(); }
      operator ref_t<object_t>() const { return as<ref_t<object_t>>(); }
      operator weak_ref_t<object_t>() const { return as<weak_ref_t<object_t>>(); }
      operator const any_t& () const { return my_data; }

      // Modifiable data access. Change the type if needed.

      array_t& as_array();
      dict_t& as_dict();
      text_t& as_text();

      operator text_t& () { return as_text(); }
      operator array_t& () { return as_array(); }
      operator dict_t& () { return as_dict(); }

      // Array conversion + immediate array_t op.

      element_t & operator [](index_t an_index);
      const element_t & operator [](index_t an_index) const;
      bool erase(index_t an_index);
      void append(const array_t &);
      element_t & insert(index_t an_index);
      element_t & grow();

      // Dict conversion + immediate dict_t op.

      void append(const dict_t &);
      bool erase(const name_t &);
      bool contains(const name_t &) const;
      element_t & operator [](const name_t &);
      const element_t & operator [](const name_t &) const;

      // Array, dict_t and text return the length, others return zero.
      index_t size() const;

      // Current type of data contained in the element.
      datatype_t get_type() const;

      // All integer-like types are equivalent, so you can read a boolean
      // from an integer. Same for double-like types, float and double.
      bool is_compatible(datatype_t aType) const;

      // Clear the old data and set the type. Clear even if same type.
      void reset(datatype_t = typeid(void));

      // Reset if currently not the requested type.
      // Tries to preserve as much of the old value as possible.
      void ensure(datatype_t);

      // Verify if it has the requested type or unknown, in which case set the type.
      // Returns true if the type was already correct or successfully set.
      // Returns false if the type was different.
      bool verify(datatype_t);

      // Comparison.
      std::partial_ordering operator <=> (const element_t&) const;
      bool operator == (const element_t&) const;

      bool is_similar(const element_t& other, const visited_refs_t& visited) const;

   protected:
      any_t my_data;
   };


   //////////////////////////////////////////////////////////////////////////
   //
   // Conversion operators.

   // This defines the operator x= for the type t.
   // For example, it defines += for int32.
   // It does so by extracting the value t from the element, then applying
   // the operator, then assigning the value back to the element.

   #define DAK_ELEMENT_OPERATOR(x, t, e) inline e& operator x=(e& a, const t& b) { t c = const_cast<const e&>(a); c x= b; a = c; return a; }

   // This defines the x= operator for integer-like types.

   #define DAK_ELEMENT_INT_OPERATORS(x, e) \
      DAK_ELEMENT_OPERATOR(x, wchar_t, e)  \
      DAK_ELEMENT_OPERATOR(x, char, e)     \
      DAK_ELEMENT_OPERATOR(x, int16_t, e)    \
      DAK_ELEMENT_OPERATOR(x, int32_t, e)    \
      DAK_ELEMENT_OPERATOR(x, int64_t, e)    \
      DAK_ELEMENT_OPERATOR(x, uint16_t, e)     \
      DAK_ELEMENT_OPERATOR(x, uint32_t, e)    \
      DAK_ELEMENT_OPERATOR(x, uint64_t, e)    \

   // This defines the x= operator for floating-point-like types.

  #define DAK_ELEMENT_REAL_OPERATORS(x, e) \
      DAK_ELEMENT_OPERATOR(x, float, e)    \
      DAK_ELEMENT_OPERATOR(x, double, e)   \

   // This defines the x= operator for container types.

  #define DAK_ELEMENT_CONTAINER_OPERATORS(x, e) \
      DAK_ELEMENT_OPERATOR(x, array_t, e)         \
      DAK_ELEMENT_OPERATOR(x, dict_t, e)

   // This defines the x= operator for the text type.

   #define DAK_ELEMENT_TEXT_OPERATORS(x, e) \
         DAK_ELEMENT_OPERATOR(x, text_t, e) \
         inline e& operator += (e& a, str_ptr_t b) { text_t c = const_cast<const e&>(a); c x= b; a = c; return a; }

   // Define the desired operators for each type.

   DAK_ELEMENT_INT_OPERATORS(+, element_t);
   DAK_ELEMENT_INT_OPERATORS(-, element_t);
   DAK_ELEMENT_INT_OPERATORS(*, element_t);
   DAK_ELEMENT_INT_OPERATORS(/, element_t);
   DAK_ELEMENT_INT_OPERATORS(&, element_t);
   DAK_ELEMENT_INT_OPERATORS(|, element_t);
   DAK_ELEMENT_INT_OPERATORS(^, element_t);
   DAK_ELEMENT_INT_OPERATORS(%, element_t);
   DAK_ELEMENT_INT_OPERATORS(<<, element_t);
   DAK_ELEMENT_INT_OPERATORS(>>, element_t);

   DAK_ELEMENT_REAL_OPERATORS(+, element_t);
   DAK_ELEMENT_REAL_OPERATORS(-, element_t);
   DAK_ELEMENT_REAL_OPERATORS(*, element_t);
   DAK_ELEMENT_REAL_OPERATORS(/, element_t);

   DAK_ELEMENT_TEXT_OPERATORS(+, element_t);
}

#endif /* DAK_OBJECT_ELEMENT_H */
