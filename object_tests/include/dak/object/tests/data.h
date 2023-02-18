#pragma once

#ifndef DAK_OBJECT_TESTS_DATA_H
#define DAK_OBJECT_TESTS_DATA_H

#include <dak/any_op/compare_op.h>
#include <dak/any_op/size_op.h>
#include <dak/any_op/construct_op.h>
#include <dak/any_op/convert_op.h>
#include <dak/any_op/is_compatible_op.h>

namespace dak::object::tests
{
   struct data_t
   {
      int i = 4;
      float f = 33.0f;

      auto operator<=>(const data_t&) const = default;
   };

   inline void register_data_ops()
   {
      using namespace dak::any_op;

      compare_op_t::make<>::op<comparison_t, data_t, data_t>([](const data_t& arg_a, const data_t& arg_b) -> comparison_t
         {
            if (arg_a.i < arg_b)
               return comparison_t::less;
            if (arg_a > arg_b)
               return comparison_t::more;
            return comparison_t::equal;
         });

      std::function<bool()> is_compatible([]() -> bool { return true; });

      size_op_t::make<>::op<index_t, data_t>([](const data_t& arg_a) -> index_t { return 77; });
      is_compatible_op_t::make<data_t, data_t>::op<bool>(is_compatible);
      construct_op_t::make<data_t>::op<data_t>((std::function<data_t()>)[]() -> data_t { return data_t(); });
      convert_op_t::make<bool>::op<bool, data_t>([](const data_t& arg_b) -> bool { return true; });
      convert_op_t::make<data_t>::op<data_t, data_t>([](const data_t& arg_b) -> data_t { return arg_b; });
   }
}


#endif /* DAK_OBJECT_TESTS_DATA_H */
