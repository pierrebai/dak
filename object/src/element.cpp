#include "dak/object/element.h"
#include "dak/object/dict.h"
#include "dak/object/array.h"

#include <exception>
#include <wchar.h>

namespace dak::object
{
   const element_t element_t::empty;

   void element_t::reset(datatype_t a_type)
   {
      switch(my_type)
      {
         default:
         case datatype_t::unknown:
         case datatype_t::boolean:
         case datatype_t::integer:
         case datatype_t::real:
         case datatype_t::ref:   my_i = 0;              break;
         case datatype_t::name:  if (my_n) my_n->unref(); my_n = 0; break;
         case datatype_t::array: delete my_a; my_a = 0;   break;
         case datatype_t::dict:  delete my_d; my_d = 0;   break;
         case datatype_t::text:  delete my_t; my_t = 0; break;
      }

      my_type = a_type;

      switch(my_type)
      {
         default:
         case datatype_t::unknown:
         case datatype_t::boolean:
         case datatype_t::integer:
         case datatype_t::real:
         case datatype_t::ref:                     break;
         case datatype_t::name:  my_n = 0;         break;
         case datatype_t::text:  my_t = new text_t;  break;
         case datatype_t::array: my_a = new array_t; break;
         case datatype_t::dict:  my_d = new dict_t;  break;
      }
   }

   bool element_t::compatible(datatype_t a_type) const
   {
      switch(my_type)
      {
         default:
         case datatype_t::unknown:
         case datatype_t::real:
         case datatype_t::ref:
         case datatype_t::name:
         case datatype_t::array:
         case datatype_t::dict:
         case datatype_t::text:    return my_type == a_type;
         case datatype_t::boolean:
         case datatype_t::integer: return datatype_t::boolean == a_type
                                    ||  datatype_t::integer == a_type;
      }
   }

   void element_t::ensure(datatype_t a_type)
   {
      if (compatible(a_type))
         return;

      // Try to preserve as much of the existing value as possible.
      switch (a_type)
      {
         default:
         case datatype_t::unknown:
         case datatype_t::ref:
         case datatype_t::name:
         case datatype_t::text:
         case datatype_t::array:
         case datatype_t::dict:
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
      if (compatible(a_type))
         return true;

      if (my_type == datatype_t::unknown)
      {
         reset(a_type);
         return true;
      }

      return false;
   }

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

   element_t::~element_t()
   {
      reset();
   }

   element_t& element_t::operator =(const element_t & anOther)
   {
      switch(anOther.my_type)
      {
         default:
         case datatype_t::unknown: reset(); break;
         case datatype_t::boolean:
         case datatype_t::integer: *this =  anOther.my_i; break;
         case datatype_t::name:    *this =  name_t(anOther.my_n); break;
         case datatype_t::real:    *this =  anOther.my_r; break;
         case datatype_t::array:   *this = *anOther.my_a; break;
         case datatype_t::dict:    *this = *anOther.my_d; break;
         case datatype_t::text:    *this = *anOther.my_t; break;
      }

      return *this;
   }

   element_t& element_t::operator =(const text_t & sometext)
   {
      return element_t::operator =(sometext.c_str());
   }

   element_t& element_t::operator =(char aValue)
   {
      return element_t::operator =((int64_t) aValue);
   }

   element_t& element_t::operator =(wchar_t aValue)
   {
      return element_t::operator =((int64_t) aValue);
   }

   element_t& element_t::operator =(str_ptr_t sometext)
   {
      reset(datatype_t::text);
      *my_t = sometext ? sometext : L"";

      return *this;
   }

   element_t& element_t::operator =(bool aValue)
   {
      reset(datatype_t::boolean);
      my_i = aValue;

      return *this;
   }

   element_t& element_t::operator =(int16_t aValue)
   {
      return element_t::operator =((int64_t) aValue);
   }

   element_t& element_t::operator =(int32_t aValue)
   {
      return element_t::operator =((int64_t) aValue);
   }

   element_t& element_t::operator =(int64_t aValue)
   {
      reset(datatype_t::integer);
      my_i = aValue;

      return *this;
   }

   element_t& element_t::operator =(uint16_t aValue)
   {
      return element_t::operator =((int64_t) aValue);
   }

   element_t& element_t::operator =(uint32_t aValue)
   {
      return element_t::operator =((int64_t) aValue);
   }

   element_t& element_t::operator =(uint64_t aValue)
   {
	   return element_t::operator =((int64_t)aValue);
   }

   element_t& element_t::operator =(float aValue)
   {
      return element_t::operator =((double) aValue);
   }

   element_t& element_t::operator =(double aValue)
   {
      reset(datatype_t::real);
      my_r = aValue;

      return *this;
   }

   element_t& element_t::operator =(const array_t & anarray)
   {
      reset(datatype_t::array);
      *my_a = anarray;

      return *this;
   }

   element_t& element_t::operator =(const dict_t & aDict)
   {
      reset(datatype_t::dict);
      *my_d = aDict;

      return *this;
   }

   element_t& element_t::operator =(const name_t& aValue)
   {
      reset(datatype_t::name);
      {
         const name_t::rc_sub_names_t* d = aValue.my_sub_names;
         my_n = const_cast<name_t::rc_sub_names_t*>(d);
         if (my_n)
            my_n->addref();
      }

      return *this;
   }

   element_t::operator char() const
   {
      if (compatible(datatype_t::integer))
         return (char)my_i;

      if (compatible(datatype_t::real))
         return (char)my_r;

      return 0;
   }

   element_t::operator wchar_t() const
   {
      if (compatible(datatype_t::integer))
         return (wchar_t)my_i;

      if (compatible(datatype_t::real))
         return (wchar_t)my_r;

      return 0;
   }

   element_t::operator text_t() const
   {
      if (compatible(datatype_t::text))
         return *my_t;

      return L"";
   }

   element_t::operator str_ptr_t() const
   {
      if (compatible(datatype_t::text))
         return my_t->c_str();

      return L"";
   }

   element_t::operator uint16_t() const
   {
      if (compatible(datatype_t::integer))
         return (uint16_t)my_i;

      if (compatible(datatype_t::real))
         return (uint16_t)my_r;

      return 0;
   }

   element_t::operator uint32_t() const
   {
      if (compatible(datatype_t::integer))
         return (uint32_t)my_i;

      if (compatible(datatype_t::real))
         return (uint32_t)my_r;

      return 0;
   }

   element_t::operator bool() const
   {
      switch (my_type)
      {
         default:
         case datatype_t::unknown: return false;
         case datatype_t::boolean:
         case datatype_t::integer:  return my_i != 0;
         case datatype_t::name:     return my_n != 0;
         case datatype_t::real:     return my_r != 0;
         case datatype_t::array:
         case datatype_t::dict:
         case datatype_t::text:     return size() > 0;
      }
   }

   element_t::operator int16_t() const
   {
      if (compatible(datatype_t::integer))
         return (int16_t)my_i;

      if (compatible(datatype_t::real))
         return (int16_t)my_r;

      return 0;
   }

   element_t::operator int32_t() const
   {
      if (compatible(datatype_t::integer))
         return (int32_t)my_i;

      if (compatible(datatype_t::real))
         return (int32_t)my_r;

      return 0;
   }

   element_t::operator uint64_t() const
   {
      if (compatible(datatype_t::integer))
         return (uint64_t)my_i;

      if (compatible(datatype_t::real))
         return (uint64_t)my_r;

      return 0;
   }

   element_t::operator int64_t() const
   {
      if (compatible(datatype_t::integer))
         return (int64_t)my_i;

      if (compatible(datatype_t::real))
         return (int64_t)my_r;

      return 0;
   }

   element_t::operator float() const
   {
      if (compatible(datatype_t::real))
         return (float)my_r;

      if (compatible(datatype_t::integer))
         return (float)my_i;

      return 0;
   }

   element_t::operator double() const
   {
      if (compatible(datatype_t::real))
         return my_r;

      if (compatible(datatype_t::integer))
         return (double)my_i;

      return 0;
   }

   element_t::operator const array_t &() const
   {
      if (compatible(datatype_t::array))
         return *my_a;

      return array_t::empty;
   }

   element_t::operator const dict_t &() const
   {
      if (compatible(datatype_t::dict))
         return *my_d;

      return dict_t::empty;
   }

   element_t::operator name_t() const
   {
      if (compatible(datatype_t::name))
         return name_t(my_n);

      return name_t(nullptr);
   }

   // Array conversion + immediate array op.
   element_t & element_t::operator [](index_t anIndex)
   {
      ensure(datatype_t::array);
      return (*my_a)[anIndex];
   }

   const element_t & element_t::operator [](index_t anIndex) const
   {
      if (!compatible(datatype_t::array))
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
      if (!compatible(datatype_t::dict))
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
      if (!compatible(datatype_t::dict))
         return empty;

      return ((const dict_t &)*my_d)[n];
   }

   index_t element_t::size() const
   {
      switch(my_type)
      {
         default:
         case datatype_t::unknown:
         case datatype_t::boolean:
         case datatype_t::integer:
         case datatype_t::real:
         case datatype_t::ref:
         case datatype_t::name:  return 0;
         case datatype_t::array: return my_a->size();
         case datatype_t::dict:  return my_d->size();
         case datatype_t::text:  return my_t->length();
      }
   }

   datatype_t element_t::type() const
   {
      return my_type;
   }

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
         case datatype_t::ref:     return false;
         case datatype_t::name:    return my_n == e.my_n;
         case datatype_t::array:   return *my_a == *e.my_a;
         case datatype_t::dict:    return *my_d == *e.my_d;
         case datatype_t::text:    return *my_t == *e.my_t;
      }
   }

   bool element_t::operator != (const element_t& e) const
   {
      return !((*this) == e);
   }
}

