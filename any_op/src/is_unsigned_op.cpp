#include <dak/any_op/is_unsigned_op.h>

namespace dak::any_op
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Define which types we consider unsigned.

   namespace
   {
      // Note: for some reason, Visual-Studio 2019 in C++ 2020 mode cannot
      //       deduce the N_ARY variadic template argument in the calls
      //       to ::op below when we pass the lambda directly,
      //
      //       It also fails if we replace the lambda with a real function
      //       taking no argument and returning a bool.
      //
      //       It only works when we pass an explicit std::function.
      //       The problem only manistfest itself for the nullary
      //       is_unsigned_op_t. It seems the complete absence of type
      //       in a nullary function fails to be automatically deduced
      //       as an empty N_ARY variadic template...
      std::function<bool()> is_unsigned([]() -> bool { return true; });

      struct is_unsigned_op_init_t
      {
         is_unsigned_op_init_t()
         {
            is_unsigned_op_t::make<uint8_t >::op<bool>(is_unsigned);
            is_unsigned_op_t::make<uint16_t>::op<bool>(is_unsigned);
            is_unsigned_op_t::make<uint32_t>::op<bool>(is_unsigned);
            is_unsigned_op_t::make<uint64_t>::op<bool>(is_unsigned);
         }
      };

      is_unsigned_op_init_t is_unsigned_op_init;
   }

   void is_unsigned_op_t::register_ops()
   {
      // Needed so that the global operations are initialized in the tests.
      // All that is needed is to enter this file to create the globals.
   }

   bool is_unsigned(const std::type_info& arg_a)
   {
      any_t result = is_unsigned_op_t::call_extra_any<void>::op(arg_a);
      return as<bool>(result);
   }
}
