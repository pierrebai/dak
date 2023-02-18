#include <dak/object_io/ref_ostream.h>

namespace dak::object
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Output stream wrapper data.

   namespace
   {
      bool is_valid(const ref_t<object_t>& object) { return object.is_valid(); }
      bool is_valid(const exact_name_t& name) { return name.is_valid(); }
      bool is_valid(const type_info_t* a_type) { return a_type && *a_type != typeid(void); }

      template <class T>
      int64_t get_thing_id(std::unordered_map<T, int64_t>& ids, const T& thing)
      {
         if (!is_valid(thing))
            return 0;

         const auto pos = ids.find(thing);
         if (pos != ids.end())
            return -pos->second;

         // Note: 0 is reserved for invalid things.
         const int64_t id = static_cast<int64_t>(ids.size()) + 1;
         ids[thing] = id;
         return id;
      }
   }

   int64_t ref_output_t::get_object_id(const ref_t<object_t>& object) const
   {
      return get_thing_id<ref_t<object_t>>(my_object_ids, object);
   }

   int64_t ref_output_t::get_name_id(const exact_name_t& name) const
   {
      return get_thing_id<exact_name_t>(my_name_ids, name);
   }

   int64_t ref_output_t::get_type_id(const type_info_t& a_type) const
   {
      return get_thing_id<const type_info_t*>(my_type_ids, &a_type);
   }

   void ref_output_t::clear()
   {
      my_object_ids.clear();
      my_name_ids.clear();
      my_type_ids.clear();
   }
}

