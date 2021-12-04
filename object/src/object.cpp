#include "dak/object/object.h"
#include "dak/object/transaction.h"

namespace dak::object
{
   object_t& object_t::operator +=(const object_t & an_obj)
   {
      append(an_obj);
      return *this;
   }

   void object_t::append(const object_t & an_obj)
   {
      for (const auto& [n, e] : an_obj.my_elements)
         (*this)[n] = e;
   }

   bool object_t::erase(const name_t& n)
   {
      iterator pos = my_elements.find(n);
      if (pos == my_elements.end())
         return false;

      my_elements.erase(pos);
      return true;
   }

   // Reset the object.
   void object_t::clear()
   {
      my_elements.clear();
   }

   void object_t::swap(object_t& an_other)
   {
      my_elements.swap(an_other.my_elements);
   }

   bool object_t::contains(const name_t& n) const
   {
      return 0 != my_elements.count(n);
   }

   index_t object_t::size() const
   {
      return my_elements.size();
   }

   element_t & object_t::operator [](const name_t& n)
   {
      return my_elements[n];
   }

   const element_t & object_t::operator [](const name_t& n) const
   {
      const_iterator pos = my_elements.find(n);
      if(my_elements.end() == pos)
         return element_t::empty;
      else
         return pos->second;
   }

   object_t::iterator object_t::begin()
   {
      return my_elements.begin();
   }

   object_t::iterator object_t::end()
   {
      return my_elements.end();
   }

   object_t::const_iterator object_t::begin() const
   {
      return my_elements.begin();
   }

   object_t::const_iterator object_t::end() const
   {
      return my_elements.end();
   }

   object_t& object_t::modify(transaction_t& a_trans) const
   {
      a_trans.add(edit_ref_t<object_t>(const_cast<object_t*>(this)));
      return const_cast<object_t&>(*this);
   }
}
