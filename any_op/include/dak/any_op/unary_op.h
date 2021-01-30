#pragma once

#ifndef DAK_ANY_OP_UNARY_OP_H
#define DAK_ANY_OP_UNARY_OP_H

#include <dak/any_op/op_selector.h>

#include <any>
#include <functional>
#include <map>

namespace dak::any_op
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Familiy of unary operations.
   //
   // To create a new unary operation family called foo:
   //
   //    Declare a class named foo deriving from unary_op_t. This class
   //    can be empty. It is only needed to identity the operation via
   //    its type. For our example:
   //
   //            struct foo : unary_op_t<foo> {};
   //
   // To implement the operation foo for type A returning RET:
   //
   //    Create an instance by calling unary_op_t<foo>::make_op<RET, A>
   //    passing a function taking an A and returning a RET.
   //
   // The class hierarchy will be:
   //
   //                     unary_op_t<foo>
   //                            |
   //                           foo
   //
   // The reasons there are two classes:
   //
   //    1. The base class necessary to have a common type for all
   //       implementations. It's also necessary to provide the
   //       functions make_op and call_op.
   //
   //    2. The sub class is necessary as it is what identifies your
   //       unique operation. It's your operation!
   //
   //    3. The make_op function wraps the specific implementation for
   //       specific types and registers the implementation.
   //       It is also a convenience to automatically extract
   //       the correct types from std::any and write code without
   //       std::any.
   //
   // The family of foo operations will be registered in the unary_op_t<foo>
   // class.
   //
   // To call an implementation corresponding to the value kept in a std::any,
   // call:
   //
   //        std::any arg = 2152671; // any value type!
   //        std::any result = unary_op_t<foo>::call(arg);
   //
   // The declaration of the operations support:
   //
   //    - Extra arguments passed to the operation. These are the EXTRA_ARGS
   //      variadic template argument on the operation. The extra arguments
   //      are passed as the first arguments of the operation when called.
   //
   //    - Extra selection types used to select the opration implementation.
   //      These are the EXTRA_SELECTORS variadic template arguments in the
   //      make_op and call_op functions. They are used to provide further
   //      selection of the implementation.

   template <class OP, class... EXTRA_ARGS>
   struct unary_op_t
   {
      friend OP;

      // The operation function signature.
      using op_func_t = std::function<std::any(EXTRA_ARGS ..., const std::any& arg_a)>;

      // The operation common base class.
      using op_base_t = unary_op_t<OP, EXTRA_ARGS...>;

      // Constructors.
      unary_op_t() = default;
      unary_op_t(const op_func_t& an_op) : my_op_func(an_op) {}

      // Creator of unary operation implementations with the optional extra args and extra selectors.
      template <class RET, class A, class... EXTRA_SELECTORS>
      static void make_op(std::function<RET(EXTRA_ARGS... args, const A& arg_a)> a_func)
      {
         op_base_t op([a_func](EXTRA_ARGS... args, const std::any& arg_a) -> std::any
         {
            return std::any(a_func(args..., *std::any_cast<A>(&arg_a)));
         });

         register_op<A, EXTRA_SELECTORS...>(op);
      }

      // Call a unary operation with the optional extra args and selected with the extra selectors.
      template <class... EXTRA_SELECTORS>
      static std::any call_op(EXTRA_ARGS... args, const std::any& arg_a)
      {
         using selector_t = typename unary_op_selector_t<EXTRA_SELECTORS...>::selector_t;
         const auto& ops = get_ops<selector_t>();
         const auto pos = ops.find(unary_op_selector_t<EXTRA_SELECTORS...>::make(arg_a));
         if (pos == ops.end())
            return std::any();
         return pos->second.my_op_func(args..., arg_a);
      }

      // Call a unary operation with the optional extra args and selected with the extra selectors
      // receiving the std::type_index of the extra selector explicitly. This is used when calling
      // with std::any value instead of compile-time types.
      template <class... EXTRA_SELECTORS>
      static std::any call_any_op(EXTRA_ARGS... args, const std::any& arg_a, EXTRA_SELECTORS... selectors)
      {
         using selector_t = typename unary_op_selector_t<EXTRA_SELECTORS...>::selector_t;
         const auto& ops = get_ops<selector_t>();
         const auto pos = ops.find(unary_op_selector_t<EXTRA_SELECTORS...>::make_any(arg_a, selectors...));
         if (pos == ops.end())
            return std::any();
         return pos->second.my_op_func(args..., arg_a);
      }

   private:
      // The null operation, used in the default constructor.
      static std::any no_op(EXTRA_ARGS..., const std::any&) { return {}; }

      op_func_t my_op_func = no_op;

      // Register an operation implementation. Called by make_op.
      template <class A, class... EXTRA_SELECTORS>
      static void register_op(const op_base_t& an_op)
      {
         using selector_t = typename unary_op_selector_t<EXTRA_SELECTORS...>::selector_t;
         auto& ops = get_ops<selector_t>();
         ops[unary_op_selector_t<EXTRA_SELECTORS...>::template make<A>()] = an_op;
      }

      // The container of registered implementations.
      template <class SELECTOR>
      static std::map<SELECTOR, op_base_t>& get_ops()
      {
         static std::map<SELECTOR, op_base_t> ops;
         return ops;
      }
   };

}

#endif /* DAK_ANY_OP_UNARY_OP_H */
