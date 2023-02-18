#include <dak/any_op/is_integer_op.h>

namespace dak::any_op
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Define which types we consider integer.

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
      //       is_integer_op_t. It seems the complete absence of type
      //       in a nullary function fails to be automatically deduced
      //       as an empty N_ARY variadic template...
      std::function<bool()> is_integer([]() -> bool { return true; });

      struct is_integer_op_init_t
      {
         is_integer_op_init_t()
         {
            is_integer_op_t::make<int8_t >::op<bool>(is_integer);
            is_integer_op_t::make<int16_t>::op<bool>(is_integer);
            is_integer_op_t::make<int32_t>::op<bool>(is_integer);
            is_integer_op_t::make<int64_t>::op<bool>(is_integer);
         }
      };

      is_integer_op_init_t is_integer_op_init;
   }

   void is_integer_op_t::register_ops()
   {
      // Needed so that the global operations are initialized in the tests.
      // All that is needed is to enter this file to create the globals.
   }

   bool is_integer(const type_info_t& some_type)
   {
      any_t result = is_integer_op_t::call_any_with_types<void>::op(some_type);
      return as<bool>(result);
   }
}
