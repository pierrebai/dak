#include <dak/any_op/all.h>

namespace dak::any_op
{
   void register_ops()
   {
      // Needed so that the global operations are initialized in the tests.
      compare_op_t::register_ops();
      convert_op_t::register_ops();
      dominant_op_t::register_ops();
      is_compatible_op_t::register_ops();
      make_op_t::register_ops();
      size_op_t::register_ops();
      ostream_op_t::register_ops();
      to_text_op_t::register_ops();
      is_integer_op_t::register_ops();
      is_unsigned_op_t::register_ops();
      is_real_op_t::register_ops();
   }
}
