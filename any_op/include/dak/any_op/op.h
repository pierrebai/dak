#pragma once

#ifndef DAK_ANY_OP_N_ARY_OP_H
#define DAK_ANY_OP_N_ARY_OP_H

#include <dak/any_op/op_selector.h>

#include <any>
#include <functional>
#include <map>

namespace dak::any_op
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Familiy of operations.
   //
   // To create a new operation family called foo:
   //
   //    Declare a class named foo_op_t deriving from op_t. This class can
   //    be empty. It is only needed to identity the operation via its type.
   //    For our example:
   //
   //            class foo_op_t : public op_t<foo_op_t> {};
   //
   //    Right after the class, declare the function foo(). It will call
   //    the call<>::op<> on the foo_op_t. This is the fnction that the
   //    users of your operation will call.
   //
   // To implement the overload foo for type A returning RET:
   //
   //    Register an overload by calling foo_op_t<foo>::make<>::op<RET, A>
   //    passing a function taking an A and returning a RET.
   //
   // The class hierarchy will be:
   //
   //                       opt_t<foo_op_t>
   //                             |
   //                          foo_op_t
   //
   // The reasons there are two classes are:
   //
   //    1. The base class necessary to provide the functions make::op
   //       and call::op.
   //
   //    2. The sub class is necessary as it is what identifies your
   //       unique operation. It's your operation!
   //
   //    3. The make::op function wraps the specific implementation for
   //       specific types then registers the implementation.
   //       The call::op is a  convenience to automatically extract
   //       the correct types from std::any and write code without
   //       std::any.
   //
   // The family of foo operations will be registered in the op_t<foo_op_t>
   // class.
   //
   // To call an implementation corresponding to the value kept in a std::any,
   // call:
   //
   //        std::any arg_a = 2152671; // any value type!
   //        std::any result = foo(arg_a);
   //
   // The declaration of the operations support:
   //
   //    - Extra arguments passed to the operation. These are the EXTRA_ARGS
   //      variadic template argument of the op_t template. The extra arguments
   //      are passed as the first arguments of the operation when called.
   //
   //    - Extra selection types used to select the operation overload.
   //      These are the EXTRA_SELECTORS variadic template arguments in the
   //      make and call intermediary templates. They are used to provide
   //      further selection of the implementation, in addition to the types
   //      ar the arguments of the function itself.

   template <class OP, class... EXTRA_ARGS>
   struct op_t
   {
      // Creator of n-ary operation implementations with the optional extra args and extra selectors.
      template <class... EXTRA_SELECTORS>
      struct make
      {
         template <class RET, class... N_ARY>
         static void op(std::function<RET(EXTRA_ARGS... extra_args, N_ARY... args)> a_func)
         {
            using op_sel_t = typename op_selector_t<EXTRA_SELECTORS...>::template n_ary_t<N_ARY...>;
            using selector_t = typename op_sel_t::selector_t;
            using op_func_t = std::function<std::any(EXTRA_ARGS ..., typename type_converter_t<N_ARY>::any...)>;

            op_func_t op([a_func](EXTRA_ARGS... extra_args, const typename type_converter_t<N_ARY>::any&... args) -> std::any
            {
               return std::any(a_func(extra_args..., *std::any_cast<N_ARY>(&args)...));
            });

            auto& ops = get_ops<selector_t, op_func_t>();
            ops[op_sel_t::make()] = op;
         }
      };

      // Call a n-ary operation with the optional extra args and selected with the extra selectors.
      template <class... EXTRA_SELECTORS>
      struct call
      {
         template <class... N_ARY>
         static std::any op(EXTRA_ARGS... extra_args, N_ARY... args)
         {
            using op_sel_t = typename op_selector_t<EXTRA_SELECTORS...>::template n_ary_t<N_ARY...>;
            using selector_t = typename op_sel_t::selector_t;
            using op_func_t = std::function<std::any(EXTRA_ARGS ..., typename type_converter_t<N_ARY>::any...)>;

            const auto& ops = get_ops<selector_t, op_func_t>();
            const auto pos = ops.find(op_sel_t::make());
            if (pos == ops.end())
               return std::any();
            return pos->second(extra_args..., args...);
         }
      };

      // Call a n-ary operation with the optional extra args and selected with the extra selectors.
      template <class... EXTRA_SELECTORS>
      struct call_any
      {
         template <class... N_ARY>
         static std::any op(EXTRA_ARGS... extra_args, N_ARY... args)
         {
            using op_sel_t = typename op_selector_t<EXTRA_SELECTORS...>::template n_ary_t<N_ARY...>;
            using selector_t = typename op_sel_t::selector_t;
            using op_func_t = std::function<std::any(EXTRA_ARGS ..., typename type_converter_t<N_ARY>::any...)>;

            const auto& ops = get_ops<selector_t, op_func_t>();
            const auto pos = ops.find(op_sel_t::make_any(args...));
            if (pos == ops.end())
               return std::any();
            return pos->second(extra_args..., args...);
         }
      };

      // Call a n-ary operation with the optional extra args and selected with the extra selectors
      // receiving the std::type_index of the extra selector explicitly. This is used when there
      // are extra selectors but the function has std::any values instead of compile-time types.
      template <class... EXTRA_SELECTORS>
      struct call_extra_any
      {
         template <class... N_ARY>
         static std::any op(EXTRA_ARGS... extra_args, N_ARY... args, const typename type_converter_t<EXTRA_SELECTORS>::type_index... selectors)
         {
            using op_sel_t = typename op_selector_t<EXTRA_SELECTORS...>::template n_ary_t<N_ARY...>;
            using selector_t = typename op_sel_t::selector_t;
            using op_func_t = std::function<std::any(EXTRA_ARGS ..., typename type_converter_t<N_ARY>::any...)>;

            const auto& ops = get_ops<selector_t, op_func_t>();
            const auto pos = ops.find(op_sel_t::make_extra_any(selectors..., args...));
            if (pos == ops.end())
               return std::any();
            return pos->second(extra_args..., args...);
         }
      };

   private:
      // The container of registered implementations.
      template <class SELECTOR, class OP_FUNC>
      static std::map<SELECTOR, OP_FUNC>& get_ops()
      {
         static std::map<SELECTOR, OP_FUNC> ops;
         return ops;
      }
   };
}

#endif /* DAK_ANY_OP_N_ARY_OP_H */
