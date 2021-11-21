#include "dak/object/dict.h"

namespace dak::object
{
   const dict_t dict_t::empty;

   dict_t& dict_t::operator +=(const dict_t & d)
   {
      append(d);
      return *this;
   }

   void dict_t::append(const dict_t & d)
   {
      for (const auto& [n, e] : d.my_elements)
         (*this)[n] = e;
   }

   bool dict_t::erase(const name_t& n)
   {
      iterator pos = my_elements.find(n);
      if (pos == my_elements.end())
         return false;

      my_elements.erase(pos);
      return true;
   }

   bool dict_t::contains(const name_t& n) const
   {
      return 0 != my_elements.count(n);
   }

   index_t dict_t::size() const
   {
      return my_elements.size();
   }

   element_t & dict_t::operator [](const name_t& n)
   {
      return my_elements[n];
   }

   const element_t & dict_t::operator [](const name_t& n) const
   {
      const_iterator pos = my_elements.find(n);
      if(my_elements.end() == pos)
         return element_t::empty;
      else
         return pos->second;
   }

   dict_t::iterator dict_t::begin()
   {
      return my_elements.begin();
   }

   dict_t::iterator dict_t::end()
   {
      return my_elements.end();
   }

   dict_t::const_iterator dict_t::begin() const
   {
      return my_elements.begin();
   }

   dict_t::const_iterator dict_t::end() const
   {
      return my_elements.end();
   }
}
