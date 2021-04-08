#include "dak/object/object.h"
#include "dak/object/transaction.h"

namespace dak::object
{
   const object_t object_t::empty;

   ref_t<object_t> object_t::make()
   {
      return ref_t<object_t>(new object_t);
   }

   ref_t<object_t> object_t::make(const object_t & d)
   {
      return ref_t<object_t>(new object_t(d));
   }

   modifiable_object_t& modifiable_object_t::operator +=(const modifiable_object_t & d)
   {
      append(d);
      return *this;
   }

   void modifiable_object_t::append(const modifiable_object_t & d)
   {
      for (const auto& [n, e] : d.my_elements)
         (*this)[n] = e;
   }

   bool modifiable_object_t::erase(const name_t& n)
   {
      iterator pos = my_elements.find(n);
      if (pos == my_elements.end())
         return false;

      my_elements.erase(pos);
      return true;
   }

   void modifiable_object_t::swap(modifiable_object_t& an_other)
   {
      my_elements.swap(an_other.my_elements);
   }

   bool modifiable_object_t::contains(const name_t& n) const
   {
      return 0 != my_elements.count(n);
   }

   index_t modifiable_object_t::size() const
   {
      return my_elements.size();
   }

   element_t & modifiable_object_t::operator [](const name_t& n)
   {
      return my_elements[n];
   }

   const element_t & modifiable_object_t::operator [](const name_t& n) const
   {
      const_iterator pos = my_elements.find(n);
      if(my_elements.end() == pos)
         return element_t::empty;
      else
         return pos->second;
   }

   modifiable_object_t::iterator modifiable_object_t::begin()
   {
      return my_elements.begin();
   }

   modifiable_object_t::iterator modifiable_object_t::end()
   {
      return my_elements.end();
   }

   modifiable_object_t::const_iterator modifiable_object_t::begin() const
   {
      return my_elements.begin();
   }

   modifiable_object_t::const_iterator modifiable_object_t::end() const
   {
      return my_elements.end();
   }
}
