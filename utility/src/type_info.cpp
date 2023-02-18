#include <dak/utility/type_info.h>

#include <unordered_map>

namespace dak::utility
{
   namespace
   {
      std::unordered_map<text_t, const type_info_t*>& get_known_type_infos()
      {
         static std::unordered_map<text_t, const type_info_t*> known;
         return known;
      }

      std::unordered_map<const type_info_t*, text_t>& get_known_type_names()
      {
         static std::unordered_map<const type_info_t*, text_t> known;
         return known;
      }

      struct get_type_name_init_t
      {
         get_type_name_init_t()
         {
            add_type_info(L"bool",                 utility::type_info_of<bool>());
            add_type_info(L"char",                 utility::type_info_of<char>());
            add_type_info(L"wchar_t",              utility::type_info_of<wchar_t>());
            add_type_info(L"int8_t",               utility::type_info_of<int8_t>());
            add_type_info(L"uint8_t",              utility::type_info_of<uint8_t>());
            add_type_info(L"int16_t",              utility::type_info_of<int16_t>());
            add_type_info(L"uint16_t",             utility::type_info_of<uint16_t>());
            add_type_info(L"int32_t",              utility::type_info_of<int32_t>());
            add_type_info(L"uint32_t",             utility::type_info_of<uint32_t>());
            add_type_info(L"int64_t",              utility::type_info_of<int64_t>());
            add_type_info(L"uint64_t",             utility::type_info_of<uint64_t>());
            add_type_info(L"float",                utility::type_info_of<float>());
            add_type_info(L"double",               utility::type_info_of<double>());
            add_type_info(L"dak::utility::text_t", utility::type_info_of<text_t>());
         }
      };

      get_type_name_init_t get_type_name_init;
   }

   const type_info_t& get_type_info(const text_t& a_type_name)
   {
      const auto& known_info = get_known_type_infos();
      const auto pos = known_info.find(a_type_name);
      if (pos == known_info.end())
         return utility::type_info_of<void>();
      return *pos->second;
   }

   text_t get_type_name(const type_info_t& type_info)
   {
      const auto& known = get_known_type_names();
      const auto pos = known.find(&type_info);
      if (pos == known.end())
         return text_t();
      return pos->second;
   }

   void add_type_info(const text_t& a_type_name, const type_info_t& a_type_info)
   {
      get_known_type_infos()[a_type_name] = &a_type_info;
      get_known_type_names()[&a_type_info] = a_type_name;
   }

   void remove_type_info(const text_t& a_type_name)
   {
      auto& known_info = get_known_type_infos();
      const auto pos = known_info.find(a_type_name);
      if (pos == known_info.end())
         return;

      const auto type_info = pos->second;
      known_info.erase(a_type_name);
      get_known_type_names().erase(type_info);
   }
}

// vim: sw=3 : sts=3 : et : sta : 
