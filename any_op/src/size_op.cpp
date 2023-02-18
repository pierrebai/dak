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
            size_op_t::make<>::op<index_t, text_t   >([](const text_t& arg_a  ) -> index_t { return index_t(arg_a.size()); });
            size_op_t::make<>::op<index_t, str_ptr_t>([](str_ptr_t arg_a      ) -> index_t { return index_t(arg_a ? wcslen(arg_a) : 0); });
         }
      };

      size_op_init_t size_op_init;
   }

   void size_op_t::register_ops()
   {
      // Needed so that the global operations are initialized in the tests.
      // All that is needed is to enter this file to create the globals.
   }

   index_t size(const any_t& arg_a)
   {
      any_t result = size_op_t::call_any<>::op(arg_a);
      return as<index_t>(result);
   }

}
