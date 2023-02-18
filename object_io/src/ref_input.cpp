#include <dak/object_io/ref_input.h>

namespace dak::object
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Constructors.

   ref_input_t::ref_input_t(const valid_ref_t<namespace_t>& into_ns, transaction_t& transaction)
      : my_transaction(transaction)
      , my_target_namespace(into_ns)
   {
   }


   //////////////////////////////////////////////////////////////////////////
   //
   // Tracked objects, types and names.

      void ref_input_t::add_object_with_id(const edit_ref_t<object_t>& obj, int64_t id) const
   {
      my_object_with_ids.insert(std::pair(id, obj));
   }

   const edit_ref_t<object_t>& ref_input_t::get_object_with_id(int64_t id) const
   {
      const auto pos = my_object_with_ids.find(std::abs(id));
      if (pos != my_object_with_ids.end())
         return pos->second;

      if (abort_on_unknown())
         abort();

      static const edit_ref_t<object_t> empty = object_t::make();
      return empty;
   }

   void ref_input_t::add_name_with_id(const exact_name_t& name, int64_t id) const
   {
      my_name_with_ids[std::abs(id)] = name;
   }

   const exact_name_t& ref_input_t::get_name_with_id(int64_t id) const
   {
      const auto pos = my_name_with_ids.find(std::abs(id));
      if (pos != my_name_with_ids.end())
         return pos->second;

      if (abort_on_unknown())
         abort();

      static const exact_name_t empty;
      return empty;
   }

   void ref_input_t::add_type_with_id(const type_info_t& type, int64_t id) const
   {
      my_type_with_ids[std::abs(id)] = &type;
   }

   const type_info_t& ref_input_t::get_type_with_id(int64_t id) const
   {
      const auto pos = my_type_with_ids.find(std::abs(id));
      if (pos != my_type_with_ids.end())
         return *pos->second;

      if (abort_on_unknown())
         abort();

      return typeid(void);
   }

   void ref_input_t::clear()
   {
      my_object_with_ids.clear();
      my_name_with_ids.clear();
      my_type_with_ids.clear();
   }
}

