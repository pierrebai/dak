#pragma once

#ifndef DAK_OBJECT_ELEMENT_H
#define DAK_OBJECT_ELEMENT_H

#include <dak/utility/types.h>
#include <dak/object/name.h>

namespace dak::object
{
   USING_DAK_UTILITY_TYPES;
   struct array_t;
   struct dict_t;
   struct object_t;

   //////////////////////////////////////////////////////////////////////////
   //
   // Types that can be kept in an element.

   enum class datatype_t : uint8_t
   {
      unknown, boolean, integer, ref, name, real, array, dict, text
   };

   //////////////////////////////////////////////////////////////////////////
   //
   // Element in arrays and dictionaries. Can represent all data
   // types. Simple ones are inlined, other allocated on the heap.
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
      // Create an element of an unfixed type, potentially pre-initialized to a value.
      element_t();

      // Copy the given element.
      element_t(const element_t &);

      element_t(const text_t &);
      element_t(wchar_t);
      element_t(char);
      element_t(str_ptr_t);
      element_t(bool);
      element_t(int16_t);
      element_t(int32_t);
      element_t(int64_t);
      element_t(uint16_t);
      element_t(uint32_t);
      element_t(uint64_t);
      element_t(float);
      element_t(double);
      element_t(const array_t &);
      element_t(const dict_t &);
      element_t(const name_t &);
      ~element_t();

      static const element_t empty;

      // Assignments. Changes the type if needed.
      element_t& operator =(const element_t &);

      // Assignments of various types. Changes the type if needed.
      element_t& operator =(const text_t &);
      element_t& operator =(wchar_t);
      element_t& operator =(char);
      element_t& operator =(str_ptr_t);
      element_t& operator =(bool);
      element_t& operator =(int16_t);
      element_t& operator =(int32_t);
      element_t& operator =(int64_t);
      element_t& operator =(uint16_t);
      element_t& operator =(uint32_t);
      element_t& operator =(uint64_t);
      element_t& operator =(float);
      element_t& operator =(double);
      element_t& operator =(const array_t &);
      element_t& operator =(const dict_t &);
      element_t& operator =(const name_t &);

      // Data access. Does not change the type.
      operator char() const;
      operator wchar_t() const;
      operator text_t() const;
      operator str_ptr_t() const;
      operator bool() const;
      operator int16_t() const;
      operator int32_t() const;
      operator int64_t() const;
      operator uint16_t() const;
      operator uint32_t() const;
      operator uint64_t() const;
      operator float() const;
      operator double() const;
      operator const array_t &() const;
      operator const dict_t &() const;
      operator name_t() const;

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
      datatype_t type() const;

      // All integer-like types are equivalent, so you can read a boolean
      // from an integer. Same for double-like types, float and double.
      bool compatible(datatype_t aType) const;

      // Clear the old data and set the type. Clear even if same type.
      void reset(datatype_t = datatype_t::unknown);

      // Reset if currently not the requested type.
      // Tries to preserve as much of the old value as possible.
      void ensure(datatype_t);

      // Verify if it has the requested type or unknown, in which case set the type.
      // Returns true if the type was already correct or successfully set.
      // Returns false if the type was different.
      bool verify(datatype_t);

      // Comparison.
      bool operator == (const element_t&) const;
      bool operator != (const element_t&) const;

   protected:
      element_t(datatype_t);
      element_t(datatype_t, int64_t);
      element_t(datatype_t, double);

      // Used by fast element sub-classes. See fast_element.h.
      element_t& make_proxy(element_t &);
      element_t& make_permanent();

      union
      {
         int64_t                 my_i;
         double                  my_r;
         dict_t *                my_d;
         array_t *               my_a;
         element_t *             my_e;
         const element_t*        my_ce;
         text_t *                my_t;
         name_t::rc_sub_names_t* my_n;
         object_t *              my_o;
      };
      datatype_t my_type = datatype_t::unknown;

      friend struct dict_t;
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
