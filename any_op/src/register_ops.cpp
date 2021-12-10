#include <dak/any_op/compare_op.h>
#include <dak/any_op/convert_op.h>
#include <dak/any_op/dominant_op.h>
#include <dak/any_op/is_compatible_op.h>
#include <dak/any_op/is_integer_op.h>
#include <dak/any_op/is_unsigned_op.h>
#include <dak/any_op/is_real_op.h>
#include <dak/any_op/make_op.h>
#include <dak/any_op/size_op.h>
#include <dak/any_op/stream_op.h>
#include <dak/any_op/to_text_op.h>

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
