#include <dak/any_op/stream_op.h>

namespace dak::any_op
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Write to an output text stream.

   namespace
   {
      struct ostream_op_init_t
      {
         ostream_op_init_t()
         {
            ostream_op_t::make<>::op<bool, bool      >([](std::wostream& a_stream, bool arg_b           ) -> bool { a_stream << arg_b; return true; });
            ostream_op_t::make<>::op<bool, char      >([](std::wostream& a_stream, char arg_b           ) -> bool { a_stream << arg_b; return true; });
            ostream_op_t::make<>::op<bool, wchar_t   >([](std::wostream& a_stream, wchar_t arg_b        ) -> bool { a_stream << arg_b; return true; });
            ostream_op_t::make<>::op<bool, int8_t    >([](std::wostream& a_stream, int8_t arg_b         ) -> bool { a_stream << arg_b; return true; });
            ostream_op_t::make<>::op<bool, int16_t   >([](std::wostream& a_stream, int16_t arg_b        ) -> bool { a_stream << arg_b; return true; });
            ostream_op_t::make<>::op<bool, int32_t   >([](std::wostream& a_stream, int32_t arg_b        ) -> bool { a_stream << arg_b; return true; });
            ostream_op_t::make<>::op<bool, int64_t   >([](std::wostream& a_stream, int64_t arg_b        ) -> bool { a_stream << arg_b; return true; });
            ostream_op_t::make<>::op<bool, uint8_t   >([](std::wostream& a_stream, uint8_t arg_b        ) -> bool { a_stream << arg_b; return true; });
            ostream_op_t::make<>::op<bool, uint16_t  >([](std::wostream& a_stream, uint16_t arg_b       ) -> bool { a_stream << arg_b; return true; });
            ostream_op_t::make<>::op<bool, uint32_t  >([](std::wostream& a_stream, uint32_t arg_b       ) -> bool { a_stream << arg_b; return true; });
            ostream_op_t::make<>::op<bool, uint64_t  >([](std::wostream& a_stream, uint64_t arg_b       ) -> bool { a_stream << arg_b; return true; });
            ostream_op_t::make<>::op<bool, float     >([](std::wostream& a_stream, float arg_b          ) -> bool { a_stream << arg_b; return true; });
            ostream_op_t::make<>::op<bool, double    >([](std::wostream& a_stream, double arg_b         ) -> bool { a_stream << arg_b; return true; });
            ostream_op_t::make<>::op<bool, text_t    >([](std::wostream& a_stream, const text_t& arg_b  ) -> bool { a_stream << arg_b; return true; });
            ostream_op_t::make<>::op<bool, str_ptr_t >([](std::wostream& a_stream, str_ptr_t arg_b      ) -> bool { a_stream << (arg_b ? arg_b : L""); return true; });
         }
      };

      ostream_op_init_t ostream_op_init;
   }

   std::wostream& operator<<(std::wostream& a_stream, const any_t& a_value)
   {
      return stream(a_stream, a_value);
   }

   void ostream_op_t::register_ops()
   {
      // Needed so that the global operations are initialized in the tests.
      // All that is needed is to enter this file to create the globals.
   }
}
