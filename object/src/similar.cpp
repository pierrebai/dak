#include <dak/object/array.h>
#include <dak/object/dict.h>
#include <dak/object/value.h>
#include <dak/object/object.h>
#include <dak/object/similar.h>

#include <dak/any_op/compare_op.h>

namespace dak::object
{
   bool are_similar(const dict_t& a, const dict_t& b, const visited_refs_t& visited)
   {
      if (a.size() != b.size())
         return false;

      for (const auto& [name, a_value] : a)
      {
         const value_t& b_value = b[name];
         if (!are_similar(a_value, b_value, visited))
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

      for (const auto& [name, a_value] : a)
      {
         const value_t& b_value = b[name];
         if (!are_similar(a_value, b_value, visited))
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
         const auto& a_value = a[i];
         const auto& b_value = b[i];
         if (!are_similar(a_value, b_value, visited))
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

   bool value_t::is_similar(const value_t& other, const visited_refs_t& visited) const
   {
      const datatype_t t = get_type();
      if (t != other.get_type())
         return false;

      if (t == typeid(ref_t<object_t>))
         return are_similar(valid_ref_t<object_t>(as_ref()), valid_ref_t<object_t>(other.as_ref()), visited);

      if (t == typeid(weak_ref_t<object_t>))
         return are_similar(as_weak_ref(), other.as_weak_ref(), visited);

      if (is_compatible(typeid(array_t)))
         return are_similar(as_array(), other.as_array(), visited);

      if (is_compatible(typeid(dict_t)))
         return are_similar(as_dict(), other.as_dict(), visited);

      return any_op::is(any_op::compare(my_data, other.my_data), any_op::comparison_t::equal);
   }

   bool are_similar(const value_t& a, const value_t& b, const visited_refs_t& visited)
   {
      return a.is_similar(b, visited);
   }
}
