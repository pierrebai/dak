#include <dak/object/make_op.h>
#include <dak/object/name.h>
#include <dak/object/value.h>
#include <dak/object/array.h>
#include <dak/object/dict.h>
#include <dak/object/object.h>
#include <dak/object/namespace.h>
#include <dak/object/name_stuff.h>

#include <dak/any_op/compare_op.h>
#include <dak/any_op/size_op.h>
#include <dak/any_op/supers_of_op.h>
#include <dak/any_op/construct_op.h>
#include <dak/any_op/convert_op.h>
#include <dak/any_op/is_compatible_op.h>
#include <dak/any_op/get_type_name_op.h>
#include <dak/any_op/get_type_info_op.h>

namespace dak::object
{
   namespace
   {
      using namespace any_op;

      struct object_ops_init_t
      {
         object_ops_init_t()
         {
            supers_of_op_t::make<weak_ref_base_t      >::op<supers_t>(make_supers_of([]() -> supers_t { return { &typeid(ref_base_t)            }; }));
            supers_of_op_t::make<weak_ref_t<object_t> >::op<supers_t>(make_supers_of([]() -> supers_t { return { &typeid(weak_ref_base_t)       }; }));

            supers_of_op_t::make<strong_ref_base_t    >::op<supers_t>(make_supers_of([]() -> supers_t { return { &typeid(ref_base_t)            }; }));
            supers_of_op_t::make<ref_t<object_t>      >::op<supers_t>(make_supers_of([]() -> supers_t { return { &typeid(strong_ref_base_t)     }; }));
            supers_of_op_t::make<valid_ref_t<object_t>>::op<supers_t>(make_supers_of([]() -> supers_t { return { &typeid(ref_t<object_t>)       }; }));
            supers_of_op_t::make<edit_ref_t<object_t> >::op<supers_t>(make_supers_of([]() -> supers_t { return { &typeid(valid_ref_t<object_t>) }; }));

            supers_of_op_t::make<object_t             >::op<supers_t>(make_supers_of([]() -> supers_t { return { &typeid(constant_t)            }; }));

            construct_op_t::make<name_t         >::op<name_t         >((std::function<name_t()         >)[]() -> name_t          { return name_t(); });
            construct_op_t::make<array_t        >::op<array_t        >((std::function<array_t()        >)[]() -> array_t         { return array_t(); });
            construct_op_t::make<dict_t         >::op<dict_t         >((std::function<dict_t()         >)[]() -> dict_t          { return dict_t(); });
            construct_op_t::make<value_t        >::op<value_t        >((std::function<value_t()        >)[]() -> value_t         { return value_t(); });
            construct_op_t::make<ref_t<object_t>>::op<ref_t<object_t>>((std::function<ref_t<object_t>()>)[]() -> ref_t<object_t> { return ref_t<object_t>(); });
            construct_op_t::make<weak_ref_t<object_t>>::op<weak_ref_t<object_t>>((std::function<weak_ref_t<object_t>()>)[]() -> weak_ref_t<object_t> { return weak_ref_t<object_t>(); });

            make_op_t::make<object_t    >::op<ref_t<object_t>    >((std::function<ref_t<object_t>()    >)[]() -> ref_t<object_t>     { return object_t::make(); });
            make_op_t::make<namespace_t >::op<ref_t<namespace_t> >((std::function<ref_t<namespace_t>() >)[]() -> ref_t<namespace_t>  { return namespace_t::make(); });

            compare_op_t::make<>::op<comparison_t, name_t,          name_t         >([](const name_t&          arg_a, const name_t&          arg_b) -> comparison_t { if (arg_a < arg_b) return comparison_t::less; if (arg_a > arg_b) return comparison_t::more; return comparison_t::equal; });
            compare_op_t::make<>::op<comparison_t, array_t,         array_t        >([](const array_t&         arg_a, const array_t&         arg_b) -> comparison_t { if (arg_a < arg_b) return comparison_t::less; if (arg_a > arg_b) return comparison_t::more; return comparison_t::equal; });
            compare_op_t::make<>::op<comparison_t, dict_t,          dict_t         >([](const dict_t&          arg_a, const dict_t&          arg_b) -> comparison_t { if (arg_a < arg_b) return comparison_t::less; if (arg_a > arg_b) return comparison_t::more; return comparison_t::equal; });
            compare_op_t::make<>::op<comparison_t, value_t,         value_t        >([](const value_t&         arg_a, const value_t&         arg_b) -> comparison_t { if (arg_a < arg_b) return comparison_t::less; if (arg_a > arg_b) return comparison_t::more; return comparison_t::equal; });
            compare_op_t::make<>::op<comparison_t, ref_t<object_t>, ref_t<object_t>>([](const ref_t<object_t>& arg_a, const ref_t<object_t>& arg_b) -> comparison_t { if (arg_a < arg_b) return comparison_t::less; if (arg_a > arg_b) return comparison_t::more; return comparison_t::equal; });
            compare_op_t::make<>::op<comparison_t, weak_ref_t<object_t>, weak_ref_t<object_t>>([](const weak_ref_t<object_t>& arg_a, const weak_ref_t<object_t>& arg_b) -> comparison_t { if (arg_a < arg_b) return comparison_t::less; if (arg_a > arg_b) return comparison_t::more; return comparison_t::equal; });

            compare_op_t::make<>::op<comparison_t, ref_t<object_t>, weak_ref_t<object_t>>([](const ref_t<object_t>& arg_a, const weak_ref_t<object_t>& arg_b) -> comparison_t { if (arg_a < arg_b) return comparison_t::less; if (arg_a > arg_b) return comparison_t::more; return comparison_t::equal; });
            compare_op_t::make<>::op<comparison_t, weak_ref_t<object_t>, ref_t<object_t>>([](const weak_ref_t<object_t>& arg_a, const ref_t<object_t>& arg_b) -> comparison_t { if (arg_a < arg_b) return comparison_t::less; if (arg_a > arg_b) return comparison_t::more; return comparison_t::equal; });

            convert_op_t::make<name_t         >::op<name_t         , name_t         >([](const name_t         & arg_b) -> name_t          { return arg_b; });
            convert_op_t::make<array_t        >::op<array_t        , array_t        >([](const array_t        & arg_b) -> array_t         { return arg_b; });
            convert_op_t::make<dict_t         >::op<dict_t         , dict_t         >([](const dict_t         & arg_b) -> dict_t          { return arg_b; });
            convert_op_t::make<value_t        >::op<value_t        , value_t        >([](const value_t        & arg_b) -> value_t         { return arg_b; });
            convert_op_t::make<ref_t<object_t>>::op<ref_t<object_t>, ref_t<object_t>>([](const ref_t<object_t>& arg_b) -> ref_t<object_t> { return arg_b; });
            convert_op_t::make<weak_ref_t<object_t>>::op<weak_ref_t<object_t>, weak_ref_t<object_t>>([](const weak_ref_t<object_t>& arg_b) -> weak_ref_t<object_t> { return arg_b; });

            convert_op_t::make<bool>::op<bool, name_t         >([](const name_t         & arg_b) -> bool { return arg_b.is_valid(); });
            convert_op_t::make<bool>::op<bool, array_t        >([](const array_t        & arg_b) -> bool { return arg_b.size() > 0; });
            convert_op_t::make<bool>::op<bool, dict_t         >([](const dict_t         & arg_b) -> bool { return arg_b.size() > 0; });
            convert_op_t::make<bool>::op<bool, value_t        >([](const value_t        & arg_b) -> bool { return arg_b.is_valid(); });
            convert_op_t::make<bool>::op<bool, ref_t<object_t>>([](const ref_t<object_t>& arg_b) -> bool { return arg_b.is_valid(); });
            convert_op_t::make<bool>::op<bool, weak_ref_t<object_t>>([](const weak_ref_t<object_t>& arg_b) -> bool { return arg_b.is_valid(); });

            convert_op_t::make<ref_t<object_t>>::op<ref_t<object_t>, weak_ref_t<object_t>>([](const weak_ref_t<object_t>& arg_b) -> ref_t<object_t> { return ref_t<object_t>(arg_b); });
            convert_op_t::make<ref_t<object_t>>::op<ref_t<object_t>, valid_ref_t<object_t>>([](const valid_ref_t<object_t>& arg_b) -> ref_t<object_t> { return ref_t<object_t>(arg_b); });
            convert_op_t::make<ref_t<object_t>>::op<ref_t<object_t>, edit_ref_t<object_t>>([](const edit_ref_t<object_t>& arg_b) -> ref_t<object_t> { return ref_t<object_t>(arg_b); });

            convert_op_t::make<valid_ref_t<object_t>>::op<valid_ref_t<object_t>, edit_ref_t<object_t>>([](const edit_ref_t<object_t>& arg_b) -> valid_ref_t<object_t> { return valid_ref_t<object_t>(arg_b); });

            convert_op_t::make<weak_ref_t<object_t>>::op<weak_ref_t<object_t>, ref_t<object_t>>([](const ref_t<object_t>& arg_b) -> weak_ref_t<object_t> { return arg_b; });
            convert_op_t::make<weak_ref_t<object_t>>::op<weak_ref_t<object_t>, valid_ref_t<object_t>>([](const valid_ref_t<object_t>& arg_b) -> weak_ref_t<object_t> { return arg_b; });
            convert_op_t::make<weak_ref_t<object_t>>::op<weak_ref_t<object_t>, edit_ref_t<object_t>>([](const edit_ref_t<object_t>& arg_b) -> weak_ref_t<object_t> { return arg_b; });

            std::function<bool()> is_compatible([]() -> bool { return true; });

            is_compatible_op_t::make<name_t         , name_t         >::op<bool>(is_compatible);
            is_compatible_op_t::make<array_t        , array_t        >::op<bool>(is_compatible);
            is_compatible_op_t::make<dict_t         , dict_t         >::op<bool>(is_compatible);
            is_compatible_op_t::make<value_t        , value_t        >::op<bool>(is_compatible);
            is_compatible_op_t::make<ref_t<object_t>, ref_t<object_t>>::op<bool>(is_compatible);
            is_compatible_op_t::make<weak_ref_t<object_t>, weak_ref_t<object_t>>::op<bool>(is_compatible);

            is_compatible_op_t::make<ref_t<object_t>, weak_ref_t<object_t>>::op<bool>(is_compatible);
            is_compatible_op_t::make<ref_t<object_t>, edit_ref_t<object_t>>::op<bool>(is_compatible);
            is_compatible_op_t::make<ref_t<object_t>, valid_ref_t<object_t>>::op<bool>(is_compatible);

            is_compatible_op_t::make<valid_ref_t<object_t>, edit_ref_t<object_t>>::op<bool>(is_compatible);

            is_compatible_op_t::make<weak_ref_t<object_t>, ref_t<object_t>>::op<bool>(is_compatible);
            is_compatible_op_t::make<weak_ref_t<object_t>, edit_ref_t<object_t>>::op<bool>(is_compatible);
            is_compatible_op_t::make<weak_ref_t<object_t>, valid_ref_t<object_t>>::op<bool>(is_compatible);

            size_op_t::make<>::op<index_t, array_t        >([](const array_t        & arg_b) -> index_t { return arg_b.size(); });
            size_op_t::make<>::op<index_t, dict_t         >([](const dict_t         & arg_b) -> index_t { return arg_b.size(); });
            size_op_t::make<>::op<index_t, value_t        >([](const value_t        & arg_b) -> index_t { return arg_b.size(); });
            size_op_t::make<>::op<index_t, object_t>([](const object_t& arg_b) -> index_t { return index_t(arg_b.size()); });
            size_op_t::make<>::op<index_t, ref_t<object_t>>([](const ref_t<object_t>& arg_b) -> index_t { return arg_b.is_valid() ? valid_ref_t<object_t>(arg_b)->size() : index_t(0); });
            size_op_t::make<>::op<index_t, weak_ref_t<object_t>>([](const weak_ref_t<object_t>& arg_b) -> index_t { return arg_b.is_valid() ? valid_ref_t<object_t>(arg_b)->size() : index_t(0); });
            size_op_t::make<>::op<index_t, edit_ref_t<object_t>>([](const edit_ref_t<object_t>& arg_b) -> index_t { return arg_b.is_valid() ? arg_b->size() : index_t(0); });
            size_op_t::make<>::op<index_t, valid_ref_t<object_t>>([](const valid_ref_t<object_t>& arg_b) -> index_t { return arg_b.is_valid() ? arg_b->size() : index_t(0); });

            get_type_name_op_t::make<name_t               >::op<text_t>((std::function<text_t()>)[]() -> text_t { return L"dak::object::name_t"; });
            get_type_name_op_t::make<array_t              >::op<text_t>((std::function<text_t()>)[]() -> text_t { return L"dak::object::array_t"; });
            get_type_name_op_t::make<dict_t               >::op<text_t>((std::function<text_t()>)[]() -> text_t { return L"dak::object::dict_t"; });
            get_type_name_op_t::make<value_t              >::op<text_t>((std::function<text_t()>)[]() -> text_t { return L"dak::object::value_t"; });
            get_type_name_op_t::make<ref_t<object_t>      >::op<text_t>((std::function<text_t()>)[]() -> text_t { return L"dak::object::ref_t<object_t>"; });
            get_type_name_op_t::make<valid_ref_t<object_t>>::op<text_t>((std::function<text_t()>)[]() -> text_t { return L"dak::object::valid_ref_t<object_t>"; });
            get_type_name_op_t::make<edit_ref_t<object_t> >::op<text_t>((std::function<text_t()>)[]() -> text_t { return L"dak::object::edit_ref_t<object_t>"; });
            get_type_name_op_t::make<weak_ref_t<object_t> >::op<text_t>((std::function<text_t()>)[]() -> text_t { return L"dak::object::weak_ref_t<object_t>"; });

            add_type_info(L"dak::object::name_t", typeid(name_t));
            add_type_info(L"dak::object::array_t", typeid(array_t));
            add_type_info(L"dak::object::dict_t", typeid(dict_t));
            add_type_info(L"dak::object::value_t", typeid(value_t));
            add_type_info(L"dak::object::ref_t<object_t>", typeid(ref_t<object_t>));
            add_type_info(L"dak::object::valid_ref_t<object_t>", typeid(valid_ref_t<object_t>));
            add_type_info(L"dak::object::edit_ref_t<object_t>", typeid(edit_ref_t<object_t>));
            add_type_info(L"dak::object::weak_ref_t<object_t>", typeid(weak_ref_t<object_t>));
         }
      };

      object_ops_init_t object_ops_init;
   }

   void register_object_ops()
   {
      // Needed so that the global operations are initialized in the tests.
      // All that is needed is to enter this file to create the globals.
   }

   void make_op_t::register_ops()
   {
      // Needed so that the global operations are initialized in the tests.
      // All that is needed is to enter this file to create the globals.
   }
}
