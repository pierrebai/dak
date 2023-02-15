#include <dak/command/command.h>
#include <dak/command/command_tree.h>

#include <dak/object/dict.h>
#include <dak/object/make_op.h>

#include <dak/any_op/compare_op.h>
#include <dak/any_op/size_op.h>
#include <dak/any_op/construct_op.h>
#include <dak/any_op/convert_op.h>
#include <dak/any_op/is_compatible_op.h>
#include <dak/any_op/get_type_name_op.h>
#include <dak/any_op/get_type_info_op.h>

namespace dak::command
{
   namespace
   {
      using namespace any_op;
      using action_t = command_t::action_t;

      struct command_ops_init_t
      {
         command_ops_init_t()
         {
            any_op::construct_op_t::make<command_t     >::op<command_t     >((std::function<command_t()     >)[]() -> command_t      { return command_t(); });
            any_op::construct_op_t::make<command_tree_t>::op<command_tree_t>((std::function<command_tree_t()>)[]() -> command_tree_t { return command_tree_t(); });
            any_op::construct_op_t::make<action_t      >::op<action_t      >((std::function<action_t()      >)[]() -> action_t       { return action_t(); });

            object::make_op_t::make<command_t      >::op<ref_t<command_t>      >((std::function<ref_t<command_t>()      >)[]() -> ref_t<command_t>      { return command_t::make(); });
            object::make_op_t::make<command_tree_t >::op<ref_t<command_tree_t> >((std::function<ref_t<command_tree_t>() >)[]() -> ref_t<command_tree_t> { return command_tree_t::make(); });

            compare_op_t::make<>::op<comparison_t, command_t,      command_t     >([](const command_t&      arg_a, const command_t&      arg_b) -> comparison_t { if (arg_a < arg_b) return comparison_t::less; if (arg_a > arg_b) return comparison_t::more; return comparison_t::equal; });
            compare_op_t::make<>::op<comparison_t, command_tree_t, command_tree_t>([](const command_tree_t& arg_a, const command_tree_t& arg_b) -> comparison_t { if (arg_a < arg_b) return comparison_t::less; if (arg_a > arg_b) return comparison_t::more; return comparison_t::equal; });
            compare_op_t::make<>::op<comparison_t, action_t,          action_t   >([](const action_t&       arg_a, const action_t&       arg_b) -> comparison_t { if (arg_a < arg_b) return comparison_t::less; if (arg_a > arg_b) return comparison_t::more; return comparison_t::equal; });

            convert_op_t::make<command_t     >::op<command_t     , command_t     >([](const command_t     & arg_b) -> command_t      { return arg_b; });
            convert_op_t::make<command_t     >::op<command_t     , command_tree_t>([](const command_tree_t& arg_b) -> command_t      { return arg_b; });
            convert_op_t::make<command_tree_t>::op<command_tree_t, command_tree_t>([](const command_tree_t& arg_b) -> command_tree_t { return arg_b; });
            convert_op_t::make<action_t      >::op<action_t      , action_t      >([](const action_t      & arg_b) -> action_t       { return arg_b; });

            convert_op_t::make<bool>::op<bool, command_t     >([](const command_t&      arg_b) -> bool { return bool(arg_b.get_action()); });
            convert_op_t::make<bool>::op<bool, command_tree_t>([](const command_tree_t& arg_b) -> bool { return bool(arg_b.get_action()); });
            convert_op_t::make<bool>::op<bool, action_t      >([](const action_t&       arg_b) -> bool { return bool(arg_b); });

            convert_op_t::make<ref_t<command_t>>::op<ref_t<command_t>, weak_ref_t<command_t>>([](const weak_ref_t<command_t>& arg_b) -> ref_t<command_t> { return ref_t<command_t>(arg_b); });
            convert_op_t::make<ref_t<command_t>>::op<ref_t<command_t>, valid_ref_t<command_t>>([](const valid_ref_t<command_t>& arg_b) -> ref_t<command_t> { return ref_t<command_t>(arg_b); });
            convert_op_t::make<ref_t<command_t>>::op<ref_t<command_t>, edit_ref_t<command_t>>([](const edit_ref_t<command_t>& arg_b) -> ref_t<command_t> { return ref_t<command_t>(arg_b); });

            convert_op_t::make<valid_ref_t<command_t>>::op<valid_ref_t<command_t>, edit_ref_t<command_t>>([](const edit_ref_t<command_t>& arg_b) -> valid_ref_t<command_t> { return valid_ref_t<command_t>(arg_b); });

            convert_op_t::make<weak_ref_t<command_t>>::op<weak_ref_t<command_t>, ref_t<command_t>>([](const ref_t<command_t>& arg_b) -> weak_ref_t<command_t> { return arg_b; });
            convert_op_t::make<weak_ref_t<command_t>>::op<weak_ref_t<command_t>, valid_ref_t<command_t>>([](const valid_ref_t<command_t>& arg_b) -> weak_ref_t<command_t> { return arg_b; });
            convert_op_t::make<weak_ref_t<command_t>>::op<weak_ref_t<command_t>, edit_ref_t<command_t>>([](const edit_ref_t<command_t>& arg_b) -> weak_ref_t<command_t> { return arg_b; });

            convert_op_t::make<ref_t<command_tree_t>>::op<ref_t<command_tree_t>, weak_ref_t<command_tree_t>>([](const weak_ref_t<command_tree_t>& arg_b) -> ref_t<command_tree_t> { return ref_t<command_tree_t>(arg_b); });
            convert_op_t::make<ref_t<command_tree_t>>::op<ref_t<command_tree_t>, valid_ref_t<command_tree_t>>([](const valid_ref_t<command_tree_t>& arg_b) -> ref_t<command_tree_t> { return ref_t<command_tree_t>(arg_b); });
            convert_op_t::make<ref_t<command_tree_t>>::op<ref_t<command_tree_t>, edit_ref_t<command_tree_t>>([](const edit_ref_t<command_tree_t>& arg_b) -> ref_t<command_tree_t> { return ref_t<command_tree_t>(arg_b); });

            convert_op_t::make<valid_ref_t<command_tree_t>>::op<valid_ref_t<command_tree_t>, edit_ref_t<command_tree_t>>([](const edit_ref_t<command_tree_t>& arg_b) -> valid_ref_t<command_tree_t> { return valid_ref_t<command_tree_t>(arg_b); });

            convert_op_t::make<weak_ref_t<command_tree_t>>::op<weak_ref_t<command_tree_t>, ref_t<command_tree_t>>([](const ref_t<command_tree_t>& arg_b) -> weak_ref_t<command_tree_t> { return arg_b; });
            convert_op_t::make<weak_ref_t<command_tree_t>>::op<weak_ref_t<command_tree_t>, valid_ref_t<command_tree_t>>([](const valid_ref_t<command_tree_t>& arg_b) -> weak_ref_t<command_tree_t> { return arg_b; });
            convert_op_t::make<weak_ref_t<command_tree_t>>::op<weak_ref_t<command_tree_t>, edit_ref_t<command_tree_t>>([](const edit_ref_t<command_tree_t>& arg_b) -> weak_ref_t<command_tree_t> { return arg_b; });

            std::function<bool()> is_compatible([]() -> bool { return true; });

            is_compatible_op_t::make<command_t     , command_t     >::op<bool>(is_compatible);
            is_compatible_op_t::make<command_tree_t, command_tree_t>::op<bool>(is_compatible);
            is_compatible_op_t::make<action_t      , action_t      >::op<bool>(is_compatible);

            is_compatible_op_t::make<ref_t<command_t>, weak_ref_t<command_t>>::op<bool>(is_compatible);
            is_compatible_op_t::make<ref_t<command_t>, edit_ref_t<command_t>>::op<bool>(is_compatible);
            is_compatible_op_t::make<ref_t<command_t>, valid_ref_t<command_t>>::op<bool>(is_compatible);

            is_compatible_op_t::make<valid_ref_t<command_t>, edit_ref_t<command_t>>::op<bool>(is_compatible);

            is_compatible_op_t::make<weak_ref_t<command_t>, ref_t<command_t>>::op<bool>(is_compatible);
            is_compatible_op_t::make<weak_ref_t<command_t>, edit_ref_t<command_t>>::op<bool>(is_compatible);
            is_compatible_op_t::make<weak_ref_t<command_t>, valid_ref_t<command_t>>::op<bool>(is_compatible);

            is_compatible_op_t::make<ref_t<command_tree_t>, weak_ref_t<command_tree_t>>::op<bool>(is_compatible);
            is_compatible_op_t::make<ref_t<command_tree_t>, edit_ref_t<command_tree_t>>::op<bool>(is_compatible);
            is_compatible_op_t::make<ref_t<command_tree_t>, valid_ref_t<command_tree_t>>::op<bool>(is_compatible);

            is_compatible_op_t::make<valid_ref_t<command_tree_t>, edit_ref_t<command_tree_t>>::op<bool>(is_compatible);

            is_compatible_op_t::make<weak_ref_t<command_tree_t>, ref_t<command_tree_t>>::op<bool>(is_compatible);
            is_compatible_op_t::make<weak_ref_t<command_tree_t>, edit_ref_t<command_tree_t>>::op<bool>(is_compatible);
            is_compatible_op_t::make<weak_ref_t<command_tree_t>, valid_ref_t<command_tree_t>>::op<bool>(is_compatible);

            size_op_t::make<>::op<uint64_t, command_tree_t>([](const command_tree_t& arg_b) -> uint64_t { return uint64_t(arg_b.get_commands().size()); });

            get_type_name_op_t::make<command_t     >::op<text_t>((std::function<text_t()>)[]() -> text_t { return L"dak::object::command_t"; });
            get_type_name_op_t::make<command_tree_t>::op<text_t>((std::function<text_t()>)[]() -> text_t { return L"dak::object::command_tree_t"; });
            get_type_name_op_t::make<action_t      >::op<text_t>((std::function<text_t()>)[]() -> text_t { return L"dak::object::action_t"; });

            get_type_name_op_t::make<ref_t<command_t>      >::op<text_t>((std::function<text_t()>)[]() -> text_t { return L"dak::object::ref_t<command_t>"; });
            get_type_name_op_t::make<valid_ref_t<command_t>>::op<text_t>((std::function<text_t()>)[]() -> text_t { return L"dak::object::valid_ref_t<command_t>"; });
            get_type_name_op_t::make<edit_ref_t<command_t> >::op<text_t>((std::function<text_t()>)[]() -> text_t { return L"dak::object::edit_ref_t<command_t>"; });
            get_type_name_op_t::make<weak_ref_t<command_t> >::op<text_t>((std::function<text_t()>)[]() -> text_t { return L"dak::object::weak_ref_t<command_t>"; });

            get_type_name_op_t::make<ref_t<command_tree_t>      >::op<text_t>((std::function<text_t()>)[]() -> text_t { return L"dak::object::ref_t<command_tree_t>"; });
            get_type_name_op_t::make<valid_ref_t<command_tree_t>>::op<text_t>((std::function<text_t()>)[]() -> text_t { return L"dak::object::valid_ref_t<command_tree_t>"; });
            get_type_name_op_t::make<edit_ref_t<command_tree_t> >::op<text_t>((std::function<text_t()>)[]() -> text_t { return L"dak::object::edit_ref_t<command_tree_t>"; });
            get_type_name_op_t::make<weak_ref_t<command_tree_t> >::op<text_t>((std::function<text_t()>)[]() -> text_t { return L"dak::object::weak_ref_t<command_tree_t>"; });

            add_type_info(L"dak::object::command_t", typeid(command_t));
            add_type_info(L"dak::object::command_tree_t", typeid(command_tree_t));
            add_type_info(L"dak::object::action_t", typeid(action_t));

            add_type_info(L"dak::object::ref_t<command_t>", typeid(ref_t<command_t>));
            add_type_info(L"dak::object::valid_ref_t<command_t>", typeid(valid_ref_t<command_t>));
            add_type_info(L"dak::object::edit_ref_t<command_t>", typeid(edit_ref_t<command_t>));
            add_type_info(L"dak::object::weak_ref_t<command_t>", typeid(weak_ref_t<command_t>));

            add_type_info(L"dak::object::ref_t<command_tree_t>", typeid(ref_t<command_tree_t>));
            add_type_info(L"dak::object::valid_ref_t<command_tree_t>", typeid(valid_ref_t<command_tree_t>));
            add_type_info(L"dak::object::edit_ref_t<command_tree_t>", typeid(edit_ref_t<command_tree_t>));
            add_type_info(L"dak::object::weak_ref_t<command_tree_t>", typeid(weak_ref_t<command_tree_t>));
         }
      };

      command_ops_init_t command_ops_init;
   }

   void register_command_ops()
   {
      // Needed so that the global operations are initialized in the tests.
      // All that is needed is to enter this file to create the globals.
   }
}
