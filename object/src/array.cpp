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
      return my_values.size();
   }

   void array_t::append(const array_t & a)
   {
      for (const value_t& e : a)
      {
         grow() = e;
      }
   }

   void array_t::append(const value_t& e)
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
            my_values.resize(size() - index_t);
            index_t = 0;
         }
      }
      else if (index_t >= size())
      {
         my_values.resize(index_t + 1);
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

      my_values.erase(my_values.begin() + index_t);
      return true;
   }

   value_t & array_t::insert(index_t index_t)
   {
      index_t = make_fit(index_t);
      return *my_values.insert(my_values.begin() + index_t, value_t());
   }

   value_t & array_t::operator [](index_t index_t)
   {
      index_t = make_fit(index_t);
      return my_values [index_t];
   }

   const value_t & array_t::operator [](index_t index_t) const
   {
      index_t = verify_fit(index_t);

      if (index_t < 0)
         return value_t::empty;

      return my_values [index_t];
   }

   value_t & array_t::grow()
   {
      return (*this) [ size() ];
   }

   array_t::iterator array_t::begin()
   {
      return my_values.begin();
   }

   array_t::iterator array_t::end()
   {
      return my_values.end();
   }

   array_t::const_iterator array_t::begin() const
   {
      return my_values.begin();
   }

   array_t::const_iterator array_t::end() const
   {
      return my_values.end();
   }
}
