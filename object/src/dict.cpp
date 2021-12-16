#include <dak/object/dict.h>

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
      for (const auto& [n, e] : d.my_values)
         (*this)[n] = e;
   }

   bool dict_t::erase(const name_t& n)
   {
      iterator pos = my_values.find(n);
      if (pos == my_values.end())
         return false;

      my_values.erase(pos);
      return true;
   }

   bool dict_t::contains(const name_t& n) const
   {
      return 0 != my_values.count(n);
   }

   index_t dict_t::size() const
   {
      return my_values.size();
   }

   value_t & dict_t::operator [](const name_t& n)
   {
      return my_values[n];
   }

   const value_t & dict_t::operator [](const name_t& n) const
   {
      const_iterator pos = my_values.find(n);
      if(my_values.end() == pos)
         return value_t::empty;
      else
         return pos->second;
   }

   dict_t::iterator dict_t::begin()
   {
      return my_values.begin();
   }

   dict_t::iterator dict_t::end()
   {
      return my_values.end();
   }

   dict_t::const_iterator dict_t::begin() const
   {
      return my_values.begin();
   }

   dict_t::const_iterator dict_t::end() const
   {
      return my_values.end();
   }
}
