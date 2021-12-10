#include <dak/object/array.h>
#include <dak/object/dict.h>
#include <dak/object/element.h>
#include <dak/object/object.h>
#include <dak/object/similar.h>

#include <dak/any_op/compare_op.h>

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

   bool are_similar(const any_t& a, const any_t& b, const visited_refs_t& visited)
   {
      return any_op::is(any_op::compare(a, b), any_op::comparison_t::equal);
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

   bool are_similar(const weak_ref_t<object_t>& a, const weak_ref_t<object_t>& b, const visited_refs_t& visited)
   {
      if (a.is_null())
         return b.is_null();

      if (b.is_null())
         return false;

      return are_similar(
         valid_ref_t(a),
         valid_ref_t(b),
         visited);
   }

   bool element_t::is_similar(const element_t& other, const visited_refs_t& visited) const
   {
      if (get_type() != other.get_type())
         return false;

      if (is_compatible(typeid(ref_t<object_t>)))
         return are_similar(valid_ref_t<object_t>(as_ref()), valid_ref_t<object_t>(other.as_ref()), visited);

      if (is_compatible(typeid(weak_ref_t<object_t>)))
         return are_similar(as_weak_ref(), other.as_weak_ref(), visited);

      if (is_compatible(typeid(any_t)))
         return are_similar(as_data(), other.as_data(), visited);

      if (is_compatible(typeid(array_t)))
         return are_similar(as_array(), other.as_array(), visited);

      if (is_compatible(typeid(dict_t)))
         return are_similar(as_dict(), other.as_dict(), visited);

      return any_op::is(any_op::compare(my_data, other.my_data), any_op::comparison_t::equal);
   }

   bool are_similar(const element_t& a, const element_t& b, const visited_refs_t& visited)
   {
      return a.is_similar(b, visited);
   }
}
