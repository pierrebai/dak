#include <dak/any_op/supers_of_op.h>

namespace dak::any_op
{
   std::function<supers_t()> no_supers = []() { return supers_t(); };

   namespace
   {

      struct supers_of_op_init_t
      {
         supers_of_op_init_t()
         {
            supers_of_op_t::make<bool>::op<supers_t>(no_supers);
         }
      };

      supers_of_op_init_t supers_of_op_init;
   }

   void supers_of_op_t::register_ops()
   {
      // Needed so that the global operations are initialized in the tests.
      // All that is needed is to enter this file to create the globals.
   }

   supers_t supers_of(const type_info_t& some_type)
   {
      any_t result = supers_of_op_t::call_any_with_types<void>::op(some_type);
      if (result.has_value())
         return std::any_cast<supers_t>(result);
      else
         return {};
   }

}
