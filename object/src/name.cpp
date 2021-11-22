#include "dak/object/name.h"

#include <unordered_set>
#include <mutex>

namespace dak::object
{
   namespace
   {
      str_ptr_t intern(const text_t& a_label)
      {
         static std::unordered_set<text_t> known_names;
         static std::mutex mutex;

         std::lock_guard lock(mutex);
         const auto iter = known_names.find(a_label);
         if (iter != known_names.end())
            return iter->c_str();

         auto iter_and_result = known_names.insert(a_label);
         return iter_and_result.first->c_str();
      }
   }

   name_t::name_t(const text_t& a_label)
      : my_name(intern(a_label))
   {
   }
}
