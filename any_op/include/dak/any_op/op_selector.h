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
   struct type_converter_t
   {
      // This is how the type A is converted to std::type_index.
      using type_index = std::type_index;

      // This is how the type A is converted to any_t.
      using any = any_t;
   };

   //////////////////////////////////////////////////////////////////////////
   //
   // Selectors for n-ary operations. This is the key encoding all the
   // types used to select the correct overload.
   //
   // It is used when registering an overload, so that it can be found later
   // during calls.
   // 
   // It is used in calls, so that the call can find the overload
   // corresponding to its arguments.

   template <class... EXTRA_SELECTORS>
   struct op_selector_t
   {
      template <class... N_ARY>
      struct n_ary_t
      {
         // The selector_t type is a tuple of type index.
         using selector_t = std::tuple<typename type_converter_t<EXTRA_SELECTORS>::type_index..., typename type_converter_t<N_ARY>::type_index...>;

         // Make a selector using the compile-time types of the extra selectors
         // template parameters plus those of some concrete types.
         static selector_t make()
         {
            return selector_t(std::type_index(typeid(EXTRA_SELECTORS))..., std::type_index(typeid(N_ARY))...);
         }

         // Make a selector the compile-time types of the extra selectors
         // template parameters plus those of the given any_t.
         //
         // This is used to create a selector from any_t in op_t::call_any::op.
         static selector_t make_any(const typename type_converter_t<N_ARY>::any&... args)
         {
            return selector_t(std::type_index(typeid(EXTRA_SELECTORS))..., std::type_index(args.type())...);
         }

         // Make a selector using the provided type index of the extra selectors
         // plus those of the given any_t
         // 
         // This is used to create a selector from type index and any_t in op_t::call_any_with_types::op.
         static selector_t make_any_with_types(
            const typename type_converter_t<EXTRA_SELECTORS>::type_index&... selectors,
            const typename type_converter_t<N_ARY>::any&... args)
         {
            return selector_t(selectors..., std::type_index(args.type())...);
         }
      };
   };

   // Needed so that the global operations are initialized in the tests.
   void register_ops();
}

#endif /* DAK_ANY_OP_OP_SELECTOR_H */
