#pragma once

#ifndef DAK_OBJECT_ELEMENT_H
#define DAK_OBJECT_ELEMENT_H

#include <dak/utility/types.h>
#include <dak/object/name.h>
#include <dak/object/similar.h>
#include <dak/any_op/convert_op.h>

#include <typeinfo>
#include <compare>
#include <functional>

namespace dak::object
{
   USING_DAK_UTILITY_TYPES;
   struct array_t;
   struct dict_t;
   struct object_t;

   //////////////////////////////////////////////////////////////////////////
   //
   // Element in objects, arrays and dictionaries.
   // 
   // Designed to hold certain favored types to simplify generic dynamic
   // object manipulations. Can also contain any data, as the value are
   // held in a any_t (std::any).
   //
   // The favored types are:
   //    - truth values             : bool
   //    - integers                 : int64_t
   //    - index positions          ; index_t
   //    - strong object references : ref_t<object_t>
   //    - weak object references   : weak_ref_t<object_t>
   //    - names                    : name_t
   //    - floating-point values    : double
   //    - arrays                   : array_t
   //    - dictionaries             : dict_t
   //    - text                     : text_t
   // 
   // All of these types have a corresponding explicit as_T function
   // to extract the value, for example as_text.
   // 
   // Some similar types are also kept in the value as converted to
   // a favored value. These are:
   //    - str_ptr_t             : text_t
   //    - valid_ref_t<object_t> : ref_t<object_t>
   //    - edit_ref_t<object_t>  : ref_t<object_t>
   //
   // All types are always copied when assigned to, so beware of assigning
   // dictionaries and arrays!
   //
   // When implicitely converted to a type, the value type is not changed.
   // The value is converted to the closest corresponding value.
   //
   // (All integer-like types are equivalent, so you can read a boolean
   // from an integer. Same for double-like types, float and double.)
   //
   // Also, when converted to a type via the ensure() or reset() functions,
   // if the value was not of that type, it is changed into it. So beware
   // of changing a dict_t into an integer, as the dict_t content is lost!
   //
   // To support access to values containg dict_t and array_t, the value
   // provides the [] operator to access the sub-values of the container.
   // Again, the value will be automatically converted, so if it was not
   // an array_t of a dict_t, its previous content will be lost.
   //
   // To support calling directly values containg functions (std::function),
   // the value provides the template () operator to call the function with
   // its parameters. The value will not be converted, so if it was not a
   // function, a default-constructed return value is returned.

   struct value_t
   {
      static const value_t empty;

      // Create an value of an unfixed type, potentially pre-initialized to a value.
      value_t() = default;

      // Copy the given value.
      value_t(const value_t&) = default;

      // Constructors taking values.

      template <class T>
      value_t(const T& value) : my_data(value) {}

      // Constructors for values that need to be converted
      // before being stored.

      value_t(str_ptr_t value) : value_t(text_t(value ? value : L"")) {}

      template <class T>
      value_t(const ref_t<T>& value) : my_data() { *this = value; }

      template <class T>
      value_t(const valid_ref_t<T>& value) : my_data() { *this = value; }

      template <class T>
      value_t(const edit_ref_t<T>& value) : my_data() { *this = value; }

      template <class T>
      value_t(const weak_ref_t<T>& value) : my_data() { *this = value; }

      ~value_t() = default;

      // Assignments. Changes the type if needed.
      value_t& operator =(const value_t&) = default;

      // Assignments of various types. Changes the type if needed.

      template <class T>
      value_t& operator =(const T& value) { my_data = value; return *this; }

      // Assignment of a few types that we want to modify before assignment.

      value_t& operator =(str_ptr_t value) { my_data = text_t(value ? value : L""); return *this; }

      template <class T>
      value_t& operator =(const ref_t<T> value) { my_data = ref_t<object_t>(value); return *this; }

      template <class T>
      value_t& operator =(const valid_ref_t<T> value) { my_data = ref_t<object_t>(value); return *this; }

      template <class T>
      value_t& operator =(const edit_ref_t<T> value) { my_data = ref_t<object_t>(value); return *this; }

      template <class T>
      value_t& operator =(const weak_ref_t<T> value) { my_data = weak_ref_t<object_t>(value); return *this; }

      // Verify if there is any data.
      bool is_valid() const { return my_data.has_value(); }

      // Data access. Does not change the type.

      template <class T>
      T as() const { return my_data.has_value() ? any_op::convert<T>(my_data) : T{}; }

      template <class T>
      operator T() const { return as<T>(); }

      bool as_boolean() const { return as<bool>(); }
      int64_t as_integer() const { return as<int64_t>(); }
      index_t as_index() const { return as<index_t>(); }
      const ref_t<object_t>& as_ref() const;
      const weak_ref_t<object_t>& as_weak_ref() const;
      name_t as_name() const { return as<name_t>(); }
      double as_real() const { return as<double>(); }
      const array_t& as_array() const;
      const dict_t& as_dict() const;
      const text_t& as_text() const;
      const any_t& as_any() const { return my_data; }

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
      operator const ref_t<object_t>&() const { return as_ref(); }
      operator const weak_ref_t<object_t>&() const { return as_weak_ref(); }
      operator const any_t& () const { return my_data; }

      // Modifiable data access. Change the type if needed.

      array_t& as_array();
      dict_t& as_dict();
      text_t& as_text();
      any_t& as_any() { return my_data; }

      operator text_t& () { return as_text(); }
      operator array_t& () { return as_array(); }
      operator dict_t& () { return as_dict(); }

      // Array conversion + immediate array_t op.

      value_t & operator [](index_t an_index);
      const value_t & operator [](index_t an_index) const;
      bool erase(index_t an_index);
      void append(const array_t &);
      value_t & insert(index_t an_index);
      value_t & grow();

      // Dict conversion + immediate dict_t op.

      void append(const dict_t &);
      bool erase(const name_t &);
      bool contains(const name_t &) const;
      value_t & operator [](const name_t &);
      const value_t & operator [](const name_t &) const;

      // Function conversion + immediate call.
      template <class RET, class ...ARGS>
      RET call(ARGS&&... args) const;

      template <class ...ARGS>
      void operator()(ARGS&&... args) const;

      // Array, dict_t and text return the length, others return zero.
      index_t size() const;

      // Current type of data contained in the value.
      const type_info_t& get_type_info() const;

      // All integer-like types are equivalent, so you can read a boolean
      // from an integer. Same for double-like types, float and double.
      bool is_compatible(const type_info_t& a_type) const;

      // Clear the old data and set the type. Clear even if same type.
      void reset(const type_info_t& = typeid(void));

      // Reset if currently not the requested type.
      // Tries to preserve as much of the old value as possible.
      void ensure(const type_info_t&);

      // Verify if it has the requested type or unknown, in which case set the type.
      // Returns true if the type was already correct or successfully set.
      // Returns false if the type was different.
      bool verify(const type_info_t&);

      // Comparison.
      std::partial_ordering operator <=> (const value_t&) const;
      bool operator == (const value_t&) const;

      bool is_similar(const value_t& other, const visited_refs_t& visited) const;

   protected:
      any_t my_data;
   };


   //////////////////////////////////////////////////////////////////////////
   //
   // Function conversion + immediate call.

   template <class RET, class ...ARGS>
   inline RET value_t::call(ARGS&&... args) const
   {
      using func_t = std::function<RET(ARGS... args)>;
      const func_t* const func = std::any_cast<func_t>(&my_data);
      if (func == nullptr)
         return {};

      return (*func)(std::forward<ARGS>(args)...);
   }

   template <class ...ARGS>
   inline void value_t::operator()(ARGS&&... args) const
   {
      using func_t = std::function<void(ARGS... args)>;
      const func_t* const func = std::any_cast<func_t>(&my_data);
      if (func == nullptr)
         return;

      (*func)(std::forward<ARGS>(args)...);
   }


   //////////////////////////////////////////////////////////////////////////
   //
   // Conversion operators.

   // This defines the operator x= for the type t.
   // For example, it defines += for int32.
   // It does so by extracting the value t from the value, then applying
   // the operator, then assigning the value back to the value.

   #define DAK_ELEMENT_OPERATOR(x, t, e) inline e& operator x=(e& a, const t& b) { t c = const_cast<const e&>(a); c x= b; a = c; return a; }

   // This defines the x= operator for integer-like types.

   #define DAK_ELEMENT_INT_OPERATORS(x, e) \
      DAK_ELEMENT_OPERATOR(x, wchar_t, e)  \
      DAK_ELEMENT_OPERATOR(x, char, e)     \
      DAK_ELEMENT_OPERATOR(x, int16_t, e)  \
      DAK_ELEMENT_OPERATOR(x, int32_t, e)  \
      DAK_ELEMENT_OPERATOR(x, int64_t, e)  \
      DAK_ELEMENT_OPERATOR(x, uint16_t, e) \
      DAK_ELEMENT_OPERATOR(x, uint32_t, e) \
      DAK_ELEMENT_OPERATOR(x, uint64_t, e)

   // This defines the x= operator for floating-point-like types.

  #define DAK_ELEMENT_REAL_OPERATORS(x, e) \
      DAK_ELEMENT_OPERATOR(x, float, e)    \
      DAK_ELEMENT_OPERATOR(x, double, e)   \

   // This defines the x= operator for container types.

  #define DAK_ELEMENT_CONTAINER_OPERATORS(x, e) \
      DAK_ELEMENT_OPERATOR(x, array_t, e)       \
      DAK_ELEMENT_OPERATOR(x, dict_t, e)

   // This defines the x= operator for the text type.

   #define DAK_ELEMENT_TEXT_OPERATORS(x, e) \
         DAK_ELEMENT_OPERATOR(x, text_t, e) \
         inline e& operator += (e& a, str_ptr_t b) { text_t c = const_cast<const e&>(a); c x= b; a = c; return a; }

   // Define the desired operators for each type.

   DAK_ELEMENT_INT_OPERATORS(+, value_t);
   DAK_ELEMENT_INT_OPERATORS(-, value_t);
   DAK_ELEMENT_INT_OPERATORS(*, value_t);
   DAK_ELEMENT_INT_OPERATORS(/, value_t);
   DAK_ELEMENT_INT_OPERATORS(&, value_t);
   DAK_ELEMENT_INT_OPERATORS(|, value_t);
   DAK_ELEMENT_INT_OPERATORS(^, value_t);
   DAK_ELEMENT_INT_OPERATORS(%, value_t);
   DAK_ELEMENT_INT_OPERATORS(<<, value_t);
   DAK_ELEMENT_INT_OPERATORS(>>, value_t);

   DAK_ELEMENT_REAL_OPERATORS(+, value_t);
   DAK_ELEMENT_REAL_OPERATORS(-, value_t);
   DAK_ELEMENT_REAL_OPERATORS(*, value_t);
   DAK_ELEMENT_REAL_OPERATORS(/, value_t);

   DAK_ELEMENT_TEXT_OPERATORS(+, value_t);

   //////////////////////////////////////////////////////////////////////////
   //
   // Now we can implement the ref_t and weak_ref_t functions taking value_t.

   template <class T>
   ref_t<T>& ref_t<T>::operator =(const value_t& other)
   {
      if (other.is_compatible(typeid(ref_t<T>)))
         *this = other.as<ref_t<T>>();
      else if (other.is_compatible(typeid(weak_ref_t<T>)))
         *this = other.as<weak_ref_t<T>>();
      return *this;
   }

   template <class T>
   valid_ref_t<T>& valid_ref_t<T>::operator =(const value_t& other)
   {
      if (other.is_compatible(typeid(ref_t<T>)))
         *this = other.as<ref_t<T>>();
      else if (other.is_compatible(typeid(weak_ref_t<T>)))
         *this = other.as<weak_ref_t<T>>();
      return *this;
   }

   template <class T>
   weak_ref_t<T>& weak_ref_t<T>::operator =(const value_t& other)
   {
      if (other.is_compatible(typeid(ref_t<T>)))
         *this = other.as<ref_t<T>>();
      else if (other.is_compatible(typeid(weak_ref_t<T>)))
         *this = other.as<weak_ref_t<T>>();
      return *this;
   }
}

#endif /* DAK_OBJECT_ELEMENT_H */
