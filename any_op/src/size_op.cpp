#include <dak/any_op/size_op.h>

namespace dak::any_op
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Size of containers.

   namespace
   {
      struct size_op_init_t
      {
         size_op_init_t()
         {
            unary_op_t<size_op_t>::make_op<uint64_t, text_t   >([](const text_t& arg_a  ) -> uint64_t { return arg_a.size(); });
            unary_op_t<size_op_t>::make_op<uint64_t, str_ptr_t>([](str_ptr_t arg_a      ) -> uint64_t { return arg_a ? wcslen(arg_a) : 0; });
         }
      };

      size_op_init_t size_op_init;
   }

   void size_op_t::register_ops()
   {
      // Needed so that the global operations are initialized in the tests.
      // All that is needed is to enter this file to create the globals.
   }
}
