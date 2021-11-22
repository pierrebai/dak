#include "dak/object/array.h"

namespace dak::object
{
   const array_t array_t::empty;

   array_t& array_t::operator +=(const array_t & a)
   {
      append(a);
      return *this;
   }

   index_t array_t::size() const
   {
      return my_elements.size();
   }

   void array_t::append(const array_t & a)
   {
      for (const element_t& e : a)
      {
         grow() = e;
      }
   }

   void array_t::append(const element_t& e)
   {
      grow() = e;
   }

   index_t array_t::make_fit(index_t index_t)
   {
      if (index_t < 0)
      {
         index_t = size() + index_t;
         if (index_t < 0)
         {
            // Note: index is negative, so subtracting adds.
            my_elements.resize(size() - index_t);
            index_t = 0;
         }
      }
      else if (index_t >= size())
      {
         my_elements.resize(index_t + 1);
      }

      return index_t;
   }

   index_t array_t::verify_fit(index_t index_t) const
   {
      if (index_t < 0)
      {
         return size() + index_t;
      }
      else if (index_t >= size())
      {
         return -1;
      }
      else
      {
         return index_t;
      }
   }

   bool array_t::erase(index_t index_t)
   {
      index_t = verify_fit(index_t);
      if (index_t < 0)
         return false;

      my_elements.erase(my_elements.begin() + index_t);
      return true;
   }

   element_t & array_t::insert(index_t index_t)
   {
      index_t = make_fit(index_t);
      return *my_elements.insert(my_elements.begin() + index_t, element_t());
   }

   element_t & array_t::operator [](index_t index_t)
   {
      index_t = make_fit(index_t);
      return my_elements [index_t];
   }

   const element_t & array_t::operator [](index_t index_t) const
   {
      index_t = verify_fit(index_t);

      if (index_t < 0)
         return element_t::empty;

      return my_elements [index_t];
   }

   element_t & array_t::grow()
   {
      return (*this) [ size() ];
   }

   array_t::iterator array_t::begin()
   {
      return my_elements.begin();
   }

   array_t::iterator array_t::end()
   {
      return my_elements.end();
   }

   array_t::const_iterator array_t::begin() const
   {
      return my_elements.begin();
   }

   array_t::const_iterator array_t::end() const
   {
      return my_elements.end();
   }
}
