#include <dak/object/object.h>
#include <dak/object/transaction.h>

namespace dak::object
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Data access.

   bool object_t::contains(const name_t& n) const
   {
      return 0 != my_values.count(n);
   }

   index_t object_t::size() const
   {
      return my_values.size();
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Modifications.

   object_t& object_t::operator +=(const object_t & an_obj)
   {
      append(an_obj);
      return *this;
   }

   void object_t::append(const object_t & an_obj)
   {
      for (const auto& [n, e] : an_obj.my_values)
         (*this)[n] = e;
   }

   bool object_t::erase(const name_t& n)
   {
      iterator pos = my_values.find(n);
      if (pos == my_values.end())
         return false;

      my_values.erase(pos);
      return true;
   }

   void object_t::clear()
   {
      my_values.clear();
   }

   void object_t::swap(object_t& an_other)
   {
      my_values.swap(an_other.my_values);
   }


   //////////////////////////////////////////////////////////////////////////
   //
   // Data access.

   const value_t& object_t::operator [](const name_t& n) const
   {
      const_iterator pos = my_values.find(n);
      if (my_values.end() == pos)
         return value_t::empty;
      else
         return pos->second;
   }

   value_t & object_t::operator [](const name_t& n)
   {
      return my_values[n];
   }

   object_t::const_iterator object_t::begin() const
   {
      return my_values.begin();
   }

   object_t::const_iterator object_t::end() const
   {
      return my_values.end();
   }

   object_t::iterator object_t::begin()
   {
      return my_values.begin();
   }

   object_t::iterator object_t::end()
   {
      return my_values.end();
   }


   //////////////////////////////////////////////////////////////////////////
   //
   // Modification in a transaction.

   edit_ref_t<object_t> object_t::modify(transaction_t& a_trans) const
   {
      edit_ref_t<object_t> edit_this(const_cast<object_t*>(this));
      a_trans.add(edit_this);
      return edit_this;
   }
}
