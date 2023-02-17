#pragma once

#ifndef DAK_ANY_OP_SUPERS_OF_OP_H
#define DAK_ANY_OP_SUPERS_OF_OP_H

#include <dak/any_op/op.h>
#include <dak/any_op/as_op.h>

namespace dak::any_op
{
   //////////////////////////////////////////////////////////////////////////
   //
   // The supers_of operation returns the list of super-types of a type.

   struct supers_of_op_t : op_t<supers_of_op_t>
   {
      // Note: pre-defined operations implementation are automatically registered,
      //       but these static variables do not get initialized by the testing framework.
      //       Tests need to explicitly call a function to trigger initialization.
      static void register_ops();
   };


   //////////////////////////////////////////////////////////////////////////
   //
   // The list of super-types.
   using supers_t = std::vector<const std::type_info*>;


   //////////////////////////////////////////////////////////////////////////
   //
   // Helper function to make a function returning a list of types.
   // Used with the supers_of_op_t::make<T>::op<supers_t>() function.

   inline std::function<supers_t()> make_supers_of(std::function<supers_t()>&& f) { return f; }


   //////////////////////////////////////////////////////////////////////////
   //
   // Retrieve the list of super-types of a type.

   supers_t supers_of(const std::type_info& arg);

   inline auto super_of(const any_t& arg)
   {
      return supers_of(arg.type());
   }

   template<class T> inline auto supers_of()
   {
      return supers_of(typeid(T));
   }
}

#endif /* DAK_ANY_OP_SUPERS_OF_OP_H */
