#include "dak/object/value.h"
#include "dak/object/dict.h"
#include "dak/object/array.h"
#include "dak/object/object.h"

#include <dak/any_op/compare_op.h>
#include <dak/any_op/size_op.h>
#include <dak/any_op/construct_op.h>
#include <dak/any_op/is_compatible_op.h>

#include <exception>
#include <wchar.h>

namespace dak::object
{
   const value_t value_t::empty;

   //////////////////////////////////////////////////////////////////////////
   //
   // Inner helpers.

   void value_t::reset(datatype_t a_type)
   {
      my_data = any_op::construct(a_type);
   }

   bool value_t::is_compatible(datatype_t a_type) const
   {
      return any_op::is_compatible(get_type(), a_type);
   }

   void value_t::ensure(datatype_t a_type)
   {
      if (is_compatible(a_type))
         return;

      if (my_data.has_value())
         my_data = any_op::convert(my_data, a_type);

      // Note: don't convert this into an 'else' of the above 'if'
      //       because any_op_convert() can return an invalid data.
      if (!my_data.has_value())
         my_data = any_op::construct(a_type);
   }

   bool value_t::verify(datatype_t a_type)
   {
      if (is_compatible(a_type))
         return true;

      if (get_type() == typeid(void))
      {
         reset(a_type);
         return true;
      }

      return false;
   }


   //////////////////////////////////////////////////////////////////////////
   //
   // Explicit conversions.

   const array_t& value_t::as_array() const
   {
      if (is_compatible(typeid(array_t)))
         return std::any_cast<const array_t&>(my_data);

      return array_t::empty;
   }

   const dict_t& value_t::as_dict() const
   {
      if (is_compatible(typeid(dict_t)))
         return std::any_cast<const dict_t&>(my_data);

      return dict_t::empty;
   }

   const ref_t<object_t>& value_t::as_ref() const
   {
      if (is_compatible(typeid(ref_t<object_t>)))
         return std::any_cast<const ref_t<object_t>&>(my_data);

      static const ref_t<object_t> empty;
      return empty;
   }

   const weak_ref_t<object_t>& value_t::as_weak_ref() const
   {
      if (is_compatible(typeid(weak_ref_t<object_t>)))
         return std::any_cast<const weak_ref_t<object_t>&>(my_data);

      static const weak_ref_t<object_t> empty;
      return empty;
   }

   const text_t& value_t::as_text() const
   {
      if (is_compatible(typeid(text_t)))
         return std::any_cast<const text_t&>(my_data);

      static const text_t empty;
      return empty;
   }


   //////////////////////////////////////////////////////////////////////////
   //
   // Modifiable data access. Change the type if needed.

   array_t& value_t::as_array()
   {
      ensure(typeid(array_t));
      return std::any_cast<array_t&>(my_data);
   }

   dict_t& value_t::as_dict()
   {
      ensure(typeid(dict_t));
      return std::any_cast<dict_t&>(my_data);
   }

   text_t& value_t::as_text()
   {
      ensure(typeid(text_t));
      return std::any_cast<text_t&>(my_data);
   }


   //////////////////////////////////////////////////////////////////////////
   //
   // Array conversion + immediate array op.

   value_t & value_t::operator [](index_t anIndex)
   {
      return as_array()[anIndex];
   }

   const value_t & value_t::operator [](index_t anIndex) const
   {
      if (!is_compatible(typeid(array_t)))
         return empty;

      return const_cast<array_t&>(const_cast<value_t&>(*this).as_array())[anIndex];
   }

   bool value_t::erase(index_t anIndex)
   {
      return as_array().erase(anIndex);
   }

   void value_t::append(const array_t & a)
   {
      return as_array().append(a);
   }

   value_t & value_t::insert(index_t anIndex)
   {
      return as_array().insert(anIndex);
   }

   value_t & value_t::grow()
   {
      return as_array().grow();
   }


   //////////////////////////////////////////////////////////////////////////
   //
   // Dict conversion + immediate dict op.

   void value_t::append(const dict_t & d)
   {
      as_dict().append(d);
   }

   bool value_t::erase(const name_t& n)
   {
      return as_dict().erase(n);
   }

   bool value_t::contains(const name_t& n) const
   {
      if (!is_compatible(typeid(dict_t)))
         return false;

      return const_cast<value_t&>(*this).as_dict().contains(n);
   }

   value_t & value_t::operator [](const name_t& n)
   {
      return as_dict()[n];
   }

   const value_t & value_t::operator [](const name_t& n) const
   {
      if (!is_compatible(typeid(dict_t)))
         return empty;

      return const_cast<dict_t&>(const_cast<value_t&>(*this).as_dict())[n];
   }


   //////////////////////////////////////////////////////////////////////////
   //
   // Size and data.

   index_t value_t::size() const
   {
      return static_cast<index_t>(any_op::size(my_data));
   }

   datatype_t value_t::get_type() const
   {
      return my_data.type();
   }


   //////////////////////////////////////////////////////////////////////////
   //
   // Comparison operators.

   std::partial_ordering value_t::operator <=> (const value_t& e) const
   {
      const auto result = any_op::compare(my_data, e.my_data);
      if (any_op::is(any_op::compare(my_data, e.my_data), any_op::comparison_t::equal))
         return std::partial_ordering::equivalent;

      if (any_op::is(any_op::compare(my_data, e.my_data), any_op::comparison_t::less))
         return std::partial_ordering::less;

      if (any_op::is(any_op::compare(my_data, e.my_data), any_op::comparison_t::more))
         return std::partial_ordering::greater;

      return std::partial_ordering::unordered;
   }

   bool value_t::operator == (const value_t& e) const
   {
      return any_op::is(any_op::compare(my_data, e.my_data), any_op::comparison_t::equal);
   }

}

