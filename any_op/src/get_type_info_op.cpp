#include <dak/any_op/get_type_info_op.h>

#include <unordered_map>

namespace dak::any_op
{
   namespace
   {
      std::unordered_map<text_t, const std::type_info *>& get_known_type_infos()
      {
         static std::unordered_map<text_t, const std::type_info*> known;
         return known;
      }
   }

   const std::type_info& get_type_info(const text_t& a_type_name)
   {
      const auto& known = get_known_type_infos();
      const auto pos = known.find(a_type_name);
      if (pos == known.end())
         return typeid(void);
      return *pos->second;
   }

   void add_type_info(const text_t& a_type_name, const std::type_info& a_type_info)
   {
      get_known_type_infos()[a_type_name] = &a_type_info;
   }

   void remove_type_info(const text_t& a_type_name)
   {
      get_known_type_infos().erase(a_type_name);
   }
}
