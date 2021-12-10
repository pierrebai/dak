#include "dak/object/element.h"
#include "dak/object/dict.h"
#include "dak/object/array.h"
#include "dak/object/object.h"

#include <dak/any_op/compare_op.h>
#include <dak/any_op/size_op.h>
#include <dak/any_op/make_op.h>
#include <dak/any_op/is_compatible_op.h>

#include <exception>
#include <wchar.h>

namespace dak::object
{
   const element_t element_t::empty;

//////////////////////////////////////////////////////////////////////////
   //
   // Inner helpers.

   void element_t::reset(datatype_t a_type)
   {
      my_data = any_op::make<void>();
   }

   bool element_t::is_compatible(datatype_t a_type) const
   {
      return any_op::is_compatible(get_type(), a_type);
   }

   void element_t::ensure(datatype_t a_type)
   {
      if (is_compatible(a_type))
         return;

      my_data = any_op::convert(my_data, a_type);

      if (!my_data.has_value())
         my_data = any_op::make(a_type);
   }

   bool element_t::verify(datatype_t a_type)
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

   const array_t& element_t::as_array() const
   {
      if (is_compatible(typeid(array_t)))
         return std::any_cast<const array_t&>(my_data);

      return array_t::empty;
   }

   const dict_t& element_t::as_dict() const
   {
      if (is_compatible(typeid(dict_t)))
         return std::any_cast<const dict_t&>(my_data);

      return dict_t::empty;
   }

   const text_t& element_t::as_text() const
   {
      if (is_compatible(typeid(text_t)))
         return std::any_cast<const text_t&>(my_data);

      static const text_t empty;
      return empty;
   }


   //////////////////////////////////////////////////////////////////////////
   //
   // Modifiable data access. Change the type if needed.

   array_t& element_t::as_array()
   {
      ensure(typeid(array_t));
      return std::any_cast<array_t&>(my_data);
   }

   dict_t& element_t::as_dict()
   {
      ensure(typeid(dict_t));
      return std::any_cast<dict_t&>(my_data);
   }

   text_t& element_t::as_text()
   {
      ensure(typeid(text_t));
      return std::any_cast<text_t&>(my_data);
   }


   //////////////////////////////////////////////////////////////////////////
   //
   // Array conversion + immediate array op.

   element_t & element_t::operator [](index_t anIndex)
   {
      return as_array()[anIndex];
   }

   const element_t & element_t::operator [](index_t anIndex) const
   {
      if (!is_compatible(typeid(array_t)))
         return empty;

      return const_cast<array_t&>(const_cast<element_t&>(*this).as_array())[anIndex];
   }

   bool element_t::erase(index_t anIndex)
   {
      return as_array().erase(anIndex);
   }

   void element_t::append(const array_t & a)
   {
      return as_array().append(a);
   }

   element_t & element_t::insert(index_t anIndex)
   {
      return as_array().insert(anIndex);
   }

   element_t & element_t::grow()
   {
      return as_array().grow();
   }


   //////////////////////////////////////////////////////////////////////////
   //
   // Dict conversion + immediate dict op.

   void element_t::append(const dict_t & d)
   {
      as_dict().append(d);
   }

   bool element_t::erase(const name_t& n)
   {
      return as_dict().erase(n);
   }

   bool element_t::contains(const name_t& n) const
   {
      if (!is_compatible(typeid(dict_t)))
         return false;

      return const_cast<element_t&>(*this).as_dict().contains(n);
   }

   element_t & element_t::operator [](const name_t& n)
   {
      return as_dict()[n];
   }

   const element_t & element_t::operator [](const name_t& n) const
   {
      if (!is_compatible(typeid(dict_t)))
         return empty;

      return const_cast<dict_t&>(const_cast<element_t&>(*this).as_dict())[n];
   }


   //////////////////////////////////////////////////////////////////////////
   //
   // Size and data.

   index_t element_t::size() const
   {
      return static_cast<index_t>(any_op::size(my_data));
   }

   datatype_t element_t::get_type() const
   {
      return my_data.type();
   }


   //////////////////////////////////////////////////////////////////////////
   //
   // Comparison operators.

   std::partial_ordering element_t::operator <=> (const element_t& e) const
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

   bool element_t::operator == (const element_t& e) const
   {
      return any_op::is(any_op::compare(my_data, e.my_data), any_op::comparison_t::equal);
   }

}

