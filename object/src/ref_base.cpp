#include "dak/object/ref_base.h"
#include "dak/object/ref_counted.h"

namespace dak::object
{
   //////////////////////////////////////////////////////////////////////////
   //
   // strong_ref_base_t

   strong_ref_base_t::strong_ref_base_t(const ref_counted_t* an_object)
      : ref_base_t(an_object)
   {
      if (an_object)
         an_object->add_ref();
   }

   strong_ref_base_t::strong_ref_base_t(const strong_ref_base_t& other)
      : ref_base_t(other.my_object)
   {
      if (my_object)
         my_object->add_ref();
   }

   strong_ref_base_t& strong_ref_base_t::operator =(const ref_counted_t* an_object)
   {
      if (my_object != an_object)
      {
         clear();
         ref_base_t::operator=(an_object);
         if (an_object)
            an_object->add_ref();
      }
      return *this;
   }

   strong_ref_base_t& strong_ref_base_t::operator =(const strong_ref_base_t& other)
   {
      return operator =(other.my_object);
   }

   strong_ref_base_t::~strong_ref_base_t()
   {
      clear();
   }

   void strong_ref_base_t::clear()
   {
      if (!my_object)
         return;

      // Note: clears the pointer before unreferencing the object
      //       in case th eobject destructor ends-up accesing this
      //       reference. Can happens in object cycles.
      auto oldmy_object = my_object;
      my_object = nullptr;
      oldmy_object->sub_ref();
   }


   //////////////////////////////////////////////////////////////////////////
   //
   // weak_ref_base_t

   weak_ref_base_t::weak_ref_base_t(const ref_counted_t* an_object)
      : ref_base_t(an_object)
   {
      if (an_object)
         an_object->add_weak();
   }

   weak_ref_base_t::weak_ref_base_t(const weak_ref_base_t& other)
      : ref_base_t(other.my_object)
   {
      if (my_object)
         my_object->add_weak();
   }

   weak_ref_base_t& weak_ref_base_t::operator =(const ref_counted_t* an_object)
   {
      if (my_object != an_object)
      {
         clear();
         ref_base_t::operator=(an_object);
         if (an_object)
            an_object->add_weak();
      }
      return *this;
   }

   weak_ref_base_t& weak_ref_base_t::operator =(const weak_ref_base_t& other)
   {
      return operator =(other.my_object);
   }

   weak_ref_base_t::~weak_ref_base_t()
   {
      clear();
   }

   void weak_ref_base_t::clear()
   {
      if (!my_object)
         return;

      // Note: clears the pointer before unreferencing the object
      //       in case th eobject destructor ends-up accesing this
      //       reference. Can happens in object cycles.
      auto oldmy_object = my_object;
      my_object = nullptr;
      oldmy_object->sub_weak();
   }
}

