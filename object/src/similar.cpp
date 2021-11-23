#include <dak/object/array.h>
#include <dak/object/dict.h>
#include <dak/object/element.h>
#include <dak/object/object.h>
#include <dak/object/similar.h>

namespace dak::object
{
   bool are_similar(const dict_t& a, const dict_t& b, const visited_refs_t& visited)
   {
      if (a.size() != b.size())
         return false;

      for (const auto& [name, a_element] : a)
      {
         const element_t& b_element = b[name];
         if (!are_similar(a_element, b_element, visited))
            return false;
      }

      return true;
   }

   bool are_similar(const object_t& a, const object_t& b, const visited_refs_t& visited)
   {
      if (a.size() != b.size())
         return false;

      for (const auto& [name, a_element] : a)
      {
         const element_t& b_element = b[name];
         if (!are_similar(a_element, b_element, visited))
            return false;
      }

      return true;
   }

   bool are_similar(const array_t& a, const array_t& b, const visited_refs_t& visited)
   {
      const index_t count = a.size();

      if (count != b.size())
         return false;

      for (index_t i = 0; i < count; ++i)
      {
         const auto& a_element = a[i];
         const auto& b_element = b[i];
         if (!are_similar(a_element, b_element, visited))
            return false;
      }

      return true;
   }

   bool are_similar(const valid_ref_t<object_t>& a, const valid_ref_t<object_t>& b, const visited_refs_t& visited)
   {
      visited_refs_t::ref_pair_t ab_pair(a, b);
      if (visited.visited.contains(ab_pair))
         return true;
      visited.visited.insert(ab_pair);
      return are_similar(*a, *b, visited);
   }

   bool element_t::is_similar(const element_t& other, const visited_refs_t& visited) const
   {
      if (my_type != other.my_type)
         return false;

      switch (my_type)
      {
         default:                  return false;
         case datatype_t::unknown: return true;
         case datatype_t::boolean:
         case datatype_t::integer: return my_i == other.my_i;
         case datatype_t::real:    return my_r == other.my_r;
         case datatype_t::ref:     return are_similar(my_o, other.my_o, visited);
         case datatype_t::name:    return my_n == other.my_n;
         case datatype_t::array:   return are_similar(*my_a, *other.my_a, visited);
         case datatype_t::dict:    return are_similar(*my_d, *other.my_d, visited);
         case datatype_t::text:    return *my_t == *other.my_t;
      }
   }

   bool are_similar(const element_t& a, const element_t& b, const visited_refs_t& visited)
   {
      return a.is_similar(b, visited);
   }
}
