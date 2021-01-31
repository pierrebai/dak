#pragma once

#ifndef DAK_ANY_OP_OP_SELECTOR_H
#define DAK_ANY_OP_OP_SELECTOR_H

#include <dak/utility/types.h>

#include <any>
#include <typeinfo>
#include <typeindex>
#include <utility>

namespace dak::any_op
{
   USING_DAK_UTILITY_TYPES;
   
   //////////////////////////////////////////////////////////////////////////
   //
   // Selectors for the operations.
   //
   // These templates convert any type into the type std::type_index.
   // It is used so that we can build a tuple containing a type index
   // for each selection type.

   template <class A>
   struct op_selector_converter_t
   {
      // This is how the type A is converted to std::type_index.
      using type_index = std::type_index;
   };

   template <class... SELECTORS>
   struct op_selector_t
   {
      // The selector_t type is a tuple of type index.
      using selector_t = std::tuple<typename op_selector_converter_t<SELECTORS>::type_index...>;
   };

   //////////////////////////////////////////////////////////////////////////
   //
   // Selectors for the nullary operations.

   template <class... EXTRA_SELECTORS>
   struct nullary_op_selector_t : op_selector_t<EXTRA_SELECTORS...>
   {
      using selector_t = typename op_selector_t<EXTRA_SELECTORS...>::selector_t;

      // Make a selector using the compile-time type index of the extra selectors.
      static selector_t make()
      {
         return selector_t(std::type_index(typeid(EXTRA_SELECTORS))...);
      }

      // Make a selector using the provided type index of the extra selectors.
      // This is used to create a selector from std::any in nullary_op_t::call_any_op.
      static selector_t make_any(EXTRA_SELECTORS... selectors)
      {
         return selector_t(selectors...);
      }
   };

   //////////////////////////////////////////////////////////////////////////
   //
   // Selectors for the unary operations.

   template <class... EXTRA_SELECTORS>
   struct unary_op_selector_t : op_selector_t<std::any, EXTRA_SELECTORS...>
   {
      using selector_t = typename op_selector_t<std::any, EXTRA_SELECTORS...>::selector_t;

      // Make a selector using the compile-time type index of the unary type plus the extra selectors.
      template <class A>
      static selector_t make()
      {
         return selector_t(std::type_index(typeid(A)), std::type_index(typeid(EXTRA_SELECTORS))...);
      }

      // Make a selector using the provided type index of the unary argument.
      // This is used to create a selector from std::any in unary_op_t::call_op.
      static selector_t make(const std::any& arg_a)
      {
         return selector_t(std::type_index(arg_a.type()), std::type_index(typeid(EXTRA_SELECTORS))...);
      }

      // Make a selector using the provided type index of the unary argument plus of the extra selectors.
      // This is used to create a selector from std::any in unary_op_t::call_any_op.
      static selector_t make_any(const std::any& arg_a, EXTRA_SELECTORS... selectors)
      {
         return selector_t(std::type_index(arg_a.type()), selectors...);
      }
   };

   //////////////////////////////////////////////////////////////////////////
   //
   // Selectors for the binary operations.

   template <class... EXTRA_SELECTORS>
   struct binary_op_selector_t : op_selector_t<std::any, std::any, EXTRA_SELECTORS...>
   {
      using selector_t = typename op_selector_t<std::any, std::any, EXTRA_SELECTORS...>::selector_t;

      // Make a selector using the compile-time type index of the binary types plus the extra selectors.
      template <class A, class B>
      static selector_t make()
      {
         return selector_t(std::type_index(typeid(A)), std::type_index(typeid(B)), std::type_index(typeid(EXTRA_SELECTORS))...);
      }

      // Make a selector using the provided type index of the binary arguments.
      // This is used to create a selector from std::any in binary_op_t::call_op.
      static selector_t make(const std::any& arg_a, const std::any& arg_b)
      {
         return selector_t(std::type_index(arg_a.type()), std::type_index(arg_b.type()), std::type_index(typeid(EXTRA_SELECTORS))...);
      }

      // Make a selector using the provided type index of the binary arguments plus of the extra selectors.
      // This is used to create a selector from std::any in binary_op_t::call_any_op.
      static selector_t make_any(const std::any& arg_a, const std::any& arg_b, EXTRA_SELECTORS... selectors)
      {
         return selector_t(std::type_index(arg_a.type()), std::type_index(arg_b.type()), selectors...);
      }
   };

   // Needed so that the global operations are initialized in the tests.
   // TODO: move elsewhere?
   void register_ops();
}

#endif /* DAK_ANY_OP_OP_SELECTOR_H */
