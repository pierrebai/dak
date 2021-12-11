#include "dak/object/name.h"
#include "dak/object/element.h"
#include "dak/object/array.h"
#include "dak/object/dict.h"
#include "dak/object/object.h"

#include <dak/any_op/compare_op.h>
#include <dak/any_op/size_op.h>
#include <dak/any_op/make_op.h>
#include <dak/any_op/convert_op.h>
#include <dak/any_op/is_compatible_op.h>

namespace dak::object
{
   namespace
   {
      using namespace any_op;

      struct object_ops_init_t
      {
         object_ops_init_t()
         {
            make_op_t::make<name_t         >::op<name_t         >((std::function<name_t()         >)[]() -> name_t          { return name_t(); });
            make_op_t::make<array_t        >::op<array_t        >((std::function<array_t()        >)[]() -> array_t         { return array_t(); });
            make_op_t::make<dict_t         >::op<dict_t         >((std::function<dict_t()         >)[]() -> dict_t          { return dict_t(); });
            make_op_t::make<element_t      >::op<element_t      >((std::function<element_t()      >)[]() -> element_t       { return element_t(); });
            make_op_t::make<ref_t<object_t>>::op<ref_t<object_t>>((std::function<ref_t<object_t>()>)[]() -> ref_t<object_t> { return ref_t<object_t>(); });
            make_op_t::make<weak_ref_t<object_t>>::op<weak_ref_t<object_t>>((std::function<weak_ref_t<object_t>()>)[]() -> weak_ref_t<object_t> { return weak_ref_t<object_t>(); });

            compare_op_t::make<>::op<comparison_t, name_t,          name_t         >([](const name_t&          arg_a, const name_t&          arg_b) -> comparison_t { if (arg_a < arg_b) return comparison_t::less; if (arg_a > arg_b) return comparison_t::more; return comparison_t::equal; });
            compare_op_t::make<>::op<comparison_t, array_t,         array_t        >([](const array_t&         arg_a, const array_t&         arg_b) -> comparison_t { if (arg_a < arg_b) return comparison_t::less; if (arg_a > arg_b) return comparison_t::more; return comparison_t::equal; });
            compare_op_t::make<>::op<comparison_t, dict_t,          dict_t         >([](const dict_t&          arg_a, const dict_t&          arg_b) -> comparison_t { if (arg_a < arg_b) return comparison_t::less; if (arg_a > arg_b) return comparison_t::more; return comparison_t::equal; });
            compare_op_t::make<>::op<comparison_t, element_t,       element_t      >([](const element_t&       arg_a, const element_t&       arg_b) -> comparison_t { if (arg_a < arg_b) return comparison_t::less; if (arg_a > arg_b) return comparison_t::more; return comparison_t::equal; });
            compare_op_t::make<>::op<comparison_t, ref_t<object_t>, ref_t<object_t>>([](const ref_t<object_t>& arg_a, const ref_t<object_t>& arg_b) -> comparison_t { if (arg_a < arg_b) return comparison_t::less; if (arg_a > arg_b) return comparison_t::more; return comparison_t::equal; });
            compare_op_t::make<>::op<comparison_t, weak_ref_t<object_t>, weak_ref_t<object_t>>([](const weak_ref_t<object_t>& arg_a, const weak_ref_t<object_t>& arg_b) -> comparison_t { if (arg_a < arg_b) return comparison_t::less; if (arg_a > arg_b) return comparison_t::more; return comparison_t::equal; });

            compare_op_t::make<>::op<comparison_t, ref_t<object_t>, weak_ref_t<object_t>>([](const ref_t<object_t>& arg_a, const weak_ref_t<object_t>& arg_b) -> comparison_t { if (arg_a < arg_b) return comparison_t::less; if (arg_a > arg_b) return comparison_t::more; return comparison_t::equal; });
            compare_op_t::make<>::op<comparison_t, weak_ref_t<object_t>, ref_t<object_t>>([](const weak_ref_t<object_t>& arg_a, const ref_t<object_t>& arg_b) -> comparison_t { if (arg_a < arg_b) return comparison_t::less; if (arg_a > arg_b) return comparison_t::more; return comparison_t::equal; });

            convert_op_t::make<name_t         >::op<name_t         , name_t         >([](const name_t         & arg_b) -> name_t          { return arg_b; });
            convert_op_t::make<array_t        >::op<array_t        , array_t        >([](const array_t        & arg_b) -> array_t         { return arg_b; });
            convert_op_t::make<dict_t         >::op<dict_t         , dict_t         >([](const dict_t         & arg_b) -> dict_t          { return arg_b; });
            convert_op_t::make<element_t      >::op<element_t      , element_t      >([](const element_t      & arg_b) -> element_t       { return arg_b; });
            convert_op_t::make<ref_t<object_t>>::op<ref_t<object_t>, ref_t<object_t>>([](const ref_t<object_t>& arg_b) -> ref_t<object_t> { return arg_b; });
            convert_op_t::make<weak_ref_t<object_t>>::op<weak_ref_t<object_t>, weak_ref_t<object_t>>([](const weak_ref_t<object_t>& arg_b) -> weak_ref_t<object_t> { return arg_b; });

            convert_op_t::make<bool>::op<bool, name_t         >([](const name_t         & arg_b) -> bool { return arg_b.is_valid(); });
            convert_op_t::make<bool>::op<bool, array_t        >([](const array_t        & arg_b) -> bool { return arg_b.size() > 0; });
            convert_op_t::make<bool>::op<bool, dict_t         >([](const dict_t         & arg_b) -> bool { return arg_b.size() > 0; });
            convert_op_t::make<bool>::op<bool, element_t      >([](const element_t      & arg_b) -> bool { return arg_b.is_valid(); });
            convert_op_t::make<bool>::op<bool, ref_t<object_t>>([](const ref_t<object_t>& arg_b) -> bool { return arg_b.is_valid(); });
            convert_op_t::make<bool>::op<bool, weak_ref_t<object_t>>([](const weak_ref_t<object_t>& arg_b) -> bool { return arg_b.is_valid(); });

            convert_op_t::make<ref_t<object_t>>::op<ref_t<object_t>, weak_ref_t<object_t>>([](const weak_ref_t<object_t>& arg_b) -> ref_t<object_t> { return ref_t<object_t>(arg_b); });
            convert_op_t::make<weak_ref_t<object_t>>::op<weak_ref_t<object_t>, ref_t<object_t>>([](const ref_t<object_t>& arg_b) -> weak_ref_t<object_t> { return arg_b; });

            std::function<bool()> is_compatible([]() -> bool { return true; });

            is_compatible_op_t::make<name_t         , name_t         >::op<bool>(is_compatible);
            is_compatible_op_t::make<array_t        , array_t        >::op<bool>(is_compatible);
            is_compatible_op_t::make<dict_t         , dict_t         >::op<bool>(is_compatible);
            is_compatible_op_t::make<element_t      , element_t      >::op<bool>(is_compatible);
            is_compatible_op_t::make<ref_t<object_t>, ref_t<object_t>>::op<bool>(is_compatible);
            is_compatible_op_t::make<weak_ref_t<object_t>, weak_ref_t<object_t>>::op<bool>(is_compatible);

            is_compatible_op_t::make<ref_t<object_t>, weak_ref_t<object_t>>::op<bool>(is_compatible);
            is_compatible_op_t::make<weak_ref_t<object_t>, ref_t<object_t>>::op<bool>(is_compatible);

            size_op_t::make<>::op<uint64_t, array_t        >([](const array_t        & arg_b) -> uint64_t { return uint64_t(arg_b.size()); });
            size_op_t::make<>::op<uint64_t, dict_t         >([](const dict_t         & arg_b) -> uint64_t { return uint64_t(arg_b.size()); });
            size_op_t::make<>::op<uint64_t, element_t      >([](const element_t      & arg_b) -> uint64_t { return uint64_t(arg_b.size()); });
            size_op_t::make<>::op<uint64_t, ref_t<object_t>>([](const ref_t<object_t>& arg_b) -> uint64_t { return arg_b.is_valid() ? uint64_t(valid_ref_t<object_t>(arg_b)->size()) : uint64_t(0); });
            size_op_t::make<>::op<uint64_t, weak_ref_t<object_t>>([](const weak_ref_t<object_t>& arg_b) -> uint64_t { return arg_b.is_valid() ? uint64_t(valid_ref_t<object_t>(arg_b)->size()) : uint64_t(0); });
         }
      };

      object_ops_init_t object_ops_init;
   }

   void register_object_ops()
   {
      // Needed so that the global operations are initialized in the tests.
      // All that is needed is to enter this file to create the globals.
   }
}
