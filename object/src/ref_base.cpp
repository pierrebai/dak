#include "dak/object/name.h"
#include "dak/object/ref.h"
#include "dak/object/ref_counted.h"

namespace dak::object
{
   ref_base_t::ref_base_t(ref_counted_t* an_object)
   : my_object(an_object)
   {
      if (an_object)
         an_object->addref();
   }

   ref_base_t::ref_base_t(const ref_base_t& other)
   : my_object(other.my_object)
   {
      if (my_object)
         my_object->addref();
   }

   ref_base_t& ref_base_t::operator =(ref_counted_t* an_object)
   {
      if (my_object != an_object)
      {
         clear();
         my_object = an_object;
         if (an_object)
            an_object->addref();
      }
      return *this;
   }

   ref_base_t& ref_base_t::operator =(const ref_base_t& other)
   {
      return operator =(other.my_object);
   }

   ref_base_t::~ref_base_t()
   {
      clear();
   }

   void ref_base_t::clear()
   {
      if (!my_object)
         return;

      auto oldmy_object = my_object;
      my_object = nullptr;
      oldmy_object->unref();
   }

   bool ref_base_t::is_valid() const
   {
      return my_object != 0;
   }

   bool ref_base_t::is_null() const
   {
      return my_object == 0;
   }
}

