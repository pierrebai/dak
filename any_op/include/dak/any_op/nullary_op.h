#pragma once

#ifndef DAK_ANY_OP_NULLARY_OP_H
#define DAK_ANY_OP_NULLARY_OP_H

#include <dak/any_op/op_selector.h>

#include <any>
#include <functional>
#include <map>

namespace dak::any_op
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Familiy of nullary operations.
   //
   // To create a new nullary operation family called foo:
   //
   //    Declare a class named foo deriving from nullary_op_t. This class
   //    can be empty. It is only needed to identity the operation via
   //    its type. For our example:
   //
   //            struct foo : nullary_op_t<foo> {};
   //
   // To implement the operation foo for type A returning RET:
   //
   //    Create an instance by calling nullary_op_t<foo>::make_op<RET, A>
   //    passing a function returning a RET for type A.
   //
   // The class hierarchy will be:
   //
   //                     nullary_op_t<foo>
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
   // The family of foo operations will be registered in the nullary_op_t<foo>
   // class.
   //
   // To call an implementation corresponding to the type A:
   //
   //        std::any result = nullary_op_t<foo>::call<A>();
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
   //
   //      In the case of the nullary_op_t, the extra selectors are quite
   //      necessary since they are the only way to select different operations!
   //      Otherwise, since this is a nullary operation, there would only be
   //      a single implementation possible.
   //
   //      An example of a unary operation is for example is-compatible:
   //      it checks if two types are compatible. It receives no value,
   //      but it has two extra selector types: the types between which
   //      we want to verify the compatibility.

   template <class OP, class... EXTRA_ARGS>
   struct nullary_op_t
   {
      friend OP;

      // The operation function signature.
      using op_func_t = std::function<std::any(EXTRA_ARGS ...)>;

      // The operation common base class.
      using op_base_t = nullary_op_t<OP, EXTRA_ARGS...>;

      // Constructors.
      nullary_op_t() = default;
      nullary_op_t(const op_func_t& an_op) : my_op_func(an_op) {}

      // Creator of nullary operation implementations with the optional extra args and extra selectors.
      template <class RET, class... EXTRA_SELECTORS>
      static void make_op(std::function<RET(EXTRA_ARGS... args)> a_func)
      {
         op_base_t op([a_func](EXTRA_ARGS... args) -> std::any
         {
            return std::any(a_func(args...));
         });

         register_op<EXTRA_SELECTORS...>(op);
      }

   private:
      // The null operation, used in the default constructor.
      static std::any no_op(EXTRA_ARGS...) { return {}; }

      op_func_t my_op_func = no_op;

      // Call a nullary operation with the optional extra args and selected with the extra selectors.
      template <class... EXTRA_SELECTORS>
      static std::any call_op(EXTRA_ARGS... args)
      {
         using selector_t = typename nullary_op_selector_t<EXTRA_SELECTORS...>::selector_t;
         const auto& ops = get_ops<selector_t>();
         const auto pos = ops.find(nullary_op_selector_t<EXTRA_SELECTORS...>::make());
         if (pos == ops.end())
            return std::any();
         return pos->second.my_op_func(args...);
      }

      // Call a nullary operation with the optional extra args and selected with the extra selectors
      // receiving the std::type_index of the extra selector explicitly. This is used when calling
      // with std::any value instead of compile-time types.
      template <class... EXTRA_SELECTORS>
      static std::any call_any_op(EXTRA_ARGS... args, EXTRA_SELECTORS... selectors)
      {
         using selector_t = typename nullary_op_selector_t<EXTRA_SELECTORS...>::selector_t;
         const auto& ops = get_ops<selector_t>();
         const auto pos = ops.find(nullary_op_selector_t<EXTRA_SELECTORS...>::make_any(selectors...));
         if (pos == ops.end())
            return std::any();
         return pos->second.my_op_func(args...);
      }

      // Register an operation implementation. Called by make_op.
      template <class... EXTRA_SELECTORS>
      static void register_op(const op_base_t& an_op)
      {
         using selector_t = typename nullary_op_selector_t<EXTRA_SELECTORS...>::selector_t;
         auto& ops = get_ops<selector_t>();
         ops[nullary_op_selector_t<EXTRA_SELECTORS...>::make()] = an_op;
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

#endif /* DAK_ANY_OP_NULLARY_OP_H */
