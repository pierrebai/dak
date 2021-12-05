#include "dak/object/element.h"
#include "dak/object/dict.h"
#include "dak/object/array.h"
#include "dak/object/object.h"

#include <dak/any_op/compare_op.h>
#include <dak/any_op/size_op.h>

#include <exception>
#include <wchar.h>

namespace dak::object
{
   using namespace dak::any_op;

   const element_t element_t::empty;

   //////////////////////////////////////////////////////////////////////////
   //
   // Inner helpers.

   void element_t::reset(datatype_t a_type)
   {
      switch(my_type)
      {
         default:
         case datatype_t::unknown:
         case datatype_t::boolean:
         case datatype_t::integer:
         case datatype_t::real:     my_i = 0;                                    break;
         case datatype_t::ref:      if (my_o) my_o->sub_ref(); my_o = nullptr;   break;
         case datatype_t::weak_ref: if (my_o) my_o->sub_weak(); my_o = nullptr;  break;
         case datatype_t::name:     if (my_n) my_n->sub_ref(); my_n = nullptr;   break;
         case datatype_t::array:    delete my_a; my_a = nullptr;                 break;
         case datatype_t::dict:     delete my_d; my_d = nullptr;                 break;
         case datatype_t::text:     delete my_t; my_t = nullptr;                 break;
         case datatype_t::data:     delete my_y; my_y = nullptr;                 break;
      }

      my_type = a_type;

      switch(my_type)
      {
         default:
         case datatype_t::unknown:
         case datatype_t::boolean:
         case datatype_t::integer:
         case datatype_t::real:
         case datatype_t::weak_ref:
         case datatype_t::ref:   my_o = nullptr;     break;
         case datatype_t::name:  my_n = nullptr;     break;
         case datatype_t::text:  my_t = new text_t;  break;
         case datatype_t::array: my_a = new array_t; break;
         case datatype_t::dict:  my_d = new dict_t;  break;
         case datatype_t::data:  my_y = new any_t;   break;
      }
   }

   bool element_t::is_compatible(datatype_t a_type) const
   {
      switch(my_type)
      {
         default:
         case datatype_t::unknown:
         case datatype_t::real:
         case datatype_t::ref:
         case datatype_t::weak_ref:
         case datatype_t::name:
         case datatype_t::array:
         case datatype_t::dict:
         case datatype_t::data:
         case datatype_t::text:    return my_type == a_type;
         case datatype_t::boolean:
         case datatype_t::integer: return datatype_t::boolean == a_type
                                    ||  datatype_t::integer == a_type;
      }
   }

   void element_t::ensure(datatype_t a_type)
   {
      if (is_compatible(a_type))
         return;

      // Try to preserve as much of the existing value as possible.
      switch (a_type)
      {
         default:
         case datatype_t::unknown:
         case datatype_t::ref:
         case datatype_t::weak_ref:
         case datatype_t::name:
         case datatype_t::text:
         case datatype_t::array:
         case datatype_t::dict:
         case datatype_t::data:
            return reset(a_type);

         case datatype_t::boolean:
         {
            const bool prev = operator bool();
            reset(a_type);
            my_i = prev;
            return;
         }

         case datatype_t::integer:
         {
            const int64_t prev = operator int64_t();
            reset(a_type);
            my_i = prev;
            return;
         }

         case datatype_t::real:
         {
            const double prev = operator double();
            reset(a_type);
            my_r = prev;
            return;
         }
      }
   }

   bool element_t::verify(datatype_t a_type)
   {
      if (is_compatible(a_type))
         return true;

      if (my_type == datatype_t::unknown)
      {
         reset(a_type);
         return true;
      }

      return false;
   }


   //////////////////////////////////////////////////////////////////////////
   //
   // Constructors.

   element_t::element_t()
   : my_i(0), my_type(datatype_t::unknown)
   {
   }

   element_t::element_t(const element_t & anOther)
   : my_i(0), my_type(datatype_t::unknown)
   {
      *this = anOther;
   }

   element_t::element_t(const text_t & t)
   : my_i(0), my_type(datatype_t::unknown)
   {
      *this = t;
   }

   element_t::element_t(wchar_t c)
   : my_i(c), my_type(datatype_t::integer)
   {
   }

   element_t::element_t(char c)
   : my_i(c), my_type(datatype_t::integer)
   {
   }
   
   element_t::element_t(str_ptr_t s)
   : my_i(0), my_type(datatype_t::unknown)
   {
      *this = s;
   }

   element_t::element_t(bool b)
   : my_i(b), my_type(datatype_t::boolean)
   {
   }

   element_t::element_t(int16_t i)
   : my_i(i), my_type(datatype_t::integer)
   {
   }

   element_t::element_t(int32_t i)
   : my_i(i), my_type(datatype_t::integer)
   {
   }

   element_t::element_t(int64_t i)
   : my_i(i), my_type(datatype_t::integer)
   {
   }

   element_t::element_t(uint16_t i)
   : my_i(i), my_type(datatype_t::integer)
   {
   }

   element_t::element_t(uint32_t i)
   : my_i(i), my_type(datatype_t::integer)
   {
   }

   element_t::element_t(uint64_t i)
   : my_i(i), my_type(datatype_t::integer)
   {
   }

   element_t::element_t(float f)
   : my_r(f), my_type(datatype_t::real)
   {
   }

   element_t::element_t(double d)
   : my_r(d), my_type(datatype_t::real)
   {
   }

   element_t::element_t(const array_t & a)
   : my_i(0), my_type(datatype_t::unknown)
   {
      *this = a;
   }

   element_t::element_t(const dict_t &d)
   : my_i(0), my_type(datatype_t::unknown)
   {
      *this = d;
   }

   element_t::element_t(const name_t & n)
   : my_i(0), my_type(datatype_t::unknown)
   {
      *this = n;
   }

   element_t::element_t(const valid_ref_t<object_t>& o)
      : my_i(0), my_type(datatype_t::unknown)
   {
      *this = o;
   }

   element_t::element_t(const weak_ref_t<object_t>& o)
   : my_i(0), my_type(datatype_t::unknown)
   {
      *this = o;
   }

   element_t::element_t(const any_t& d)
      : my_i(0), my_type(datatype_t::unknown)
   {
      *this = d;
   }

   element_t::~element_t()
   {
      reset();
   }


   //////////////////////////////////////////////////////////////////////////
   //
   // Assignments.

   element_t& element_t::operator =(const element_t & anOther)
   {
      switch(anOther.my_type)
      {
         default:
         case datatype_t::unknown: reset(); break;
         case datatype_t::boolean: *this = bool(anOther.my_i); break;
         case datatype_t::integer: *this =  anOther.my_i; break;
         case datatype_t::ref:     *this =  valid_ref_t<object_t>(anOther.my_o); break;
         case datatype_t::weak_ref:*this =  weak_ref_t<object_t>(anOther.my_o); break;
         case datatype_t::name:    *this =  name_t(ref_t<name_stuff_t>(anOther.my_n)); break;
         case datatype_t::real:    *this =  anOther.my_r; break;
         case datatype_t::array:   *this = *anOther.my_a; break;
         case datatype_t::dict:    *this = *anOther.my_d; break;
         case datatype_t::data:    *this = *anOther.my_y; break;
         case datatype_t::text:    *this = *anOther.my_t; break;
      }

      return *this;
   }

   element_t& element_t::operator =(const text_t & sometext)
   {
      return element_t::operator =(sometext.c_str());
   }

   element_t& element_t::operator =(char a_value)
   {
      return element_t::operator =((int64_t) a_value);
   }

   element_t& element_t::operator =(wchar_t a_value)
   {
      return element_t::operator =((int64_t) a_value);
   }

   element_t& element_t::operator =(str_ptr_t sometext)
   {
      reset(datatype_t::text);
      *my_t = sometext ? sometext : L"";

      return *this;
   }

   element_t& element_t::operator =(bool a_value)
   {
      reset(datatype_t::boolean);
      my_i = a_value;

      return *this;
   }

   element_t& element_t::operator =(int16_t a_value)
   {
      return element_t::operator =((int64_t) a_value);
   }

   element_t& element_t::operator =(int32_t a_value)
   {
      return element_t::operator =((int64_t) a_value);
   }

   element_t& element_t::operator =(int64_t a_value)
   {
      reset(datatype_t::integer);
      my_i = a_value;

      return *this;
   }

   element_t& element_t::operator =(uint16_t a_value)
   {
      return element_t::operator =((int64_t) a_value);
   }

   element_t& element_t::operator =(uint32_t a_value)
   {
      return element_t::operator =((int64_t) a_value);
   }

   element_t& element_t::operator =(uint64_t a_value)
   {
	   return element_t::operator =((int64_t)a_value);
   }

   element_t& element_t::operator =(float a_value)
   {
      return element_t::operator =((double) a_value);
   }

   element_t& element_t::operator =(double a_value)
   {
      reset(datatype_t::real);
      my_r = a_value;

      return *this;
   }

   element_t& element_t::operator =(const array_t & an_array)
   {
      reset(datatype_t::array);
      *my_a = an_array;

      return *this;
   }

   element_t& element_t::operator =(const dict_t & a_dict)
   {
      reset(datatype_t::dict);
      *my_d = a_dict;

      return *this;
   }

   element_t& element_t::operator =(const any_t& some_data)
   {
      reset(datatype_t::data);
      *my_y = some_data;

      return *this;
   }

   element_t& element_t::operator =(const name_t& a_name)
   {
      reset(datatype_t::name);
      if (a_name.is_valid()) {
         my_n = a_name.my_stuff;
         my_n->add_ref();
      }

      return *this;
   }

   element_t& element_t::operator =(const valid_ref_t<object_t>& o)
   {
      reset(datatype_t::ref);
      my_o = o;
      if (my_o)
         my_o->add_ref();

      return *this;
   }

   element_t& element_t::operator =(const weak_ref_t<object_t>& o)
   {
      reset(datatype_t::weak_ref);
      my_o = static_cast<const object_t *>(o.my_object);
      if (my_o)
         my_o->add_weak();

      return *this;
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Explicit conversions.

   bool element_t::as_boolean() const
   {
      switch (my_type)
      {
         default:
         case datatype_t::unknown: return false;
         case datatype_t::boolean:
         case datatype_t::integer:  return my_i != 0;
         case datatype_t::name:     return my_n != 0;
         case datatype_t::real:     return my_r != 0;
         case datatype_t::weak_ref:
         case datatype_t::ref:      return my_o != nullptr;
         case datatype_t::array:
         case datatype_t::dict:
         case datatype_t::text:     return size() > 0;
         case datatype_t::data:     return my_y->has_value();
      }
   }

   int64_t element_t::as_integer() const
   {
      if (is_compatible(datatype_t::integer))
         return (int64_t)my_i;

      if (is_compatible(datatype_t::real))
         return (int64_t)my_r;

      return 0;
   }

   valid_ref_t<object_t> element_t::as_ref() const
   {
      if (is_compatible(datatype_t::ref))
         return valid_ref_t<object_t>(my_o);

      static auto empty = object_t::make();
      return empty;
   }

   weak_ref_t<object_t> element_t::as_weak_ref() const
   {
      if (is_compatible(datatype_t::weak_ref))
         return weak_ref_t<object_t>(my_o);

      return weak_ref_t<object_t>();
   }

   name_t element_t::as_name() const
   {
      if (is_compatible(datatype_t::name))
         return name_t(ref_t<name_stuff_t>(my_n));

      return name_t();
   }

   double element_t::as_real() const
   {
      if (is_compatible(datatype_t::real))
         return my_r;

      if (is_compatible(datatype_t::integer))
         return (double)my_i;

      return 0;
   }

   const array_t& element_t::as_array() const
   {
      if (is_compatible(datatype_t::array))
         return *my_a;

      return array_t::empty;
   }

   const dict_t& element_t::as_dict() const
   {
      if (is_compatible(datatype_t::dict))
         return *my_d;

      return dict_t::empty;
   }

   text_t element_t::as_text() const
   {
      if (is_compatible(datatype_t::text))
         return *my_t;

      return L"";
   }

   const any_t& element_t::as_data() const
   {
      if (is_compatible(datatype_t::data))
         return *my_y;

      static any_t empty;
      return empty;
   }


   //////////////////////////////////////////////////////////////////////////
   //
   // Conversion operators.

   element_t::operator char() const
   {
      return (char)as_integer();
   }

   element_t::operator wchar_t() const
   {
      return (wchar_t)as_integer();
   }

   element_t::operator text_t() const
   {
      return as_text();
   }

   element_t::operator str_ptr_t() const
   {
      if (is_compatible(datatype_t::text))
         return my_t->c_str();

      return L"";
   }

   element_t::operator uint16_t() const
   {
      return (uint16_t)as_integer();
   }

   element_t::operator uint32_t() const
   {
      return (uint32_t)as_integer();
   }

   element_t::operator bool() const
   {
      return as_boolean();
   }

   element_t::operator int16_t() const
   {
      return (int16_t)as_integer();
   }

   element_t::operator int32_t() const
   {
      return (int32_t)as_integer();
   }

   element_t::operator uint64_t() const
   {
      return (uint64_t)as_integer();
   }

   element_t::operator int64_t() const
   {
      return as_integer();
   }

   element_t::operator float() const
   {
      return (float)as_real();
   }

   element_t::operator double() const
   {
      return as_real();
   }

   element_t::operator const array_t &() const
   {
      return as_array();
   }

   element_t::operator const any_t& () const
   {
      return as_data();
   }

   element_t::operator const dict_t &() const
   {
      return as_dict();
   }

   element_t::operator name_t() const
   {
      return as_name();
   }

   element_t::operator valid_ref_t<object_t>() const
   {
      return as_ref();
   }

   element_t::operator weak_ref_t<object_t>() const
   {
      return as_weak_ref();
   }


   //////////////////////////////////////////////////////////////////////////
   //
   // Modifiable data access. Change the type if needed.

   element_t::operator text_t& ()
   {
      ensure(datatype_t::text);
      return *my_t;
   }

   element_t::operator array_t& ()
   {
      ensure(datatype_t::array);
      return *my_a;
   }

   element_t::operator dict_t& ()
   {
      ensure(datatype_t::dict);
      return *my_d;
   }


   //////////////////////////////////////////////////////////////////////////
   //
   // Array conversion + immediate array op.

   element_t & element_t::operator [](index_t anIndex)
   {
      ensure(datatype_t::array);
      return (*my_a)[anIndex];
   }

   const element_t & element_t::operator [](index_t anIndex) const
   {
      if (!is_compatible(datatype_t::array))
         return empty;

      return ((const array_t &)*my_a)[anIndex];
   }

   bool element_t::erase(index_t anIndex)
   {
      ensure(datatype_t::array);
      return my_a->erase(anIndex);
   }

   void element_t::append(const array_t & a)
   {
      ensure(datatype_t::array);
      return my_a->append(a);
   }

   element_t & element_t::insert(index_t anIndex)
   {
      ensure(datatype_t::array);
      return my_a->insert(anIndex);
   }

   element_t & element_t::grow()
   {
      ensure(datatype_t::array);
      return my_a->grow();
   }


   //////////////////////////////////////////////////////////////////////////
   //
   // Dict conversion + immediate dict op.

   void element_t::append(const dict_t & d)
   {
      ensure(datatype_t::dict);
      my_d->append(d);
   }

   bool element_t::erase(const name_t& n)
   {
      ensure(datatype_t::dict);
      return my_d->erase(n);
   }

   bool element_t::contains(const name_t& n) const
   {
      if (!is_compatible(datatype_t::dict))
         return false;

      return my_d->contains(n);
   }

   element_t & element_t::operator [](const name_t& n)
   {
      ensure(datatype_t::dict);
      return (*my_d)[n];
   }

   const element_t & element_t::operator [](const name_t& n) const
   {
      if (!is_compatible(datatype_t::dict))
         return empty;

      return ((const dict_t &)*my_d)[n];
   }


   //////////////////////////////////////////////////////////////////////////
   //
   // Size and data.

   index_t element_t::size() const
   {
      switch(my_type)
      {
         default:
         case datatype_t::unknown:
         case datatype_t::boolean:
         case datatype_t::integer:
         case datatype_t::real:
         case datatype_t::name:  return 0;
         case datatype_t::weak_ref:
         case datatype_t::ref:   return my_o ? my_o->size() : 0;
         case datatype_t::array: return my_a->size();
         case datatype_t::dict:  return my_d->size();
         case datatype_t::text:  return my_t->length();
         case datatype_t::data:  return any_op::size(*my_y);
      }
   }

   datatype_t element_t::get_type() const
   {
      return my_type;
   }


   //////////////////////////////////////////////////////////////////////////
   //
   // Comparison operators.

   bool element_t::operator == (const element_t& e) const
   {
      if (my_type != e.my_type)
         return false;

      switch (my_type)
      {
         default:                return false;
         case datatype_t::unknown: return true;
         case datatype_t::boolean: 
         case datatype_t::integer: return my_i == e.my_i;
         case datatype_t::real:    return my_r == e.my_r;
         case datatype_t::weak_ref:return my_o == e.my_o;
         case datatype_t::ref:     return my_o == e.my_o;
         case datatype_t::name:    return my_n == e.my_n;
         case datatype_t::array:   return *my_a == *e.my_a;
         case datatype_t::dict:    return *my_d == *e.my_d;
         case datatype_t::data:    return *my_y == *e.my_y;
         case datatype_t::text:    return *my_t == *e.my_t;
      }
   }

   bool element_t::operator != (const element_t& e) const
   {
      return !((*this) == e);
   }
}

