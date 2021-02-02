#include <dak/any_op/compare_op.h>

#include <cwchar>

namespace dak::any_op
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Compare two values.

   namespace
   {
      struct compare_op_init_t
      {
         compare_op_init_t()
         {
            compare_op_t::make<>::op<comparison_t,  bool,      bool     >([](bool      arg_a, bool      arg_b) -> comparison_t { if (arg_a < arg_b) return comparison_t::less; if (arg_a > arg_b) return comparison_t::more; return comparison_t::equal; });
            compare_op_t::make<>::op<comparison_t,  char,      char     >([](char      arg_a, char      arg_b) -> comparison_t { if (arg_a < arg_b) return comparison_t::less; if (arg_a > arg_b) return comparison_t::more; return comparison_t::equal; });
            compare_op_t::make<>::op<comparison_t,  wchar_t,   wchar_t  >([](wchar_t   arg_a, wchar_t   arg_b) -> comparison_t { if (arg_a < arg_b) return comparison_t::less; if (arg_a > arg_b) return comparison_t::more; return comparison_t::equal; });
            compare_op_t::make<>::op<comparison_t,  int8_t,    int8_t   >([](int8_t    arg_a, int8_t    arg_b) -> comparison_t { if (arg_a < arg_b) return comparison_t::less; if (arg_a > arg_b) return comparison_t::more; return comparison_t::equal; });
            compare_op_t::make<>::op<comparison_t,  int16_t,   int16_t  >([](int16_t   arg_a, int16_t   arg_b) -> comparison_t { if (arg_a < arg_b) return comparison_t::less; if (arg_a > arg_b) return comparison_t::more; return comparison_t::equal; });
            compare_op_t::make<>::op<comparison_t,  int32_t,   int32_t  >([](int32_t   arg_a, int32_t   arg_b) -> comparison_t { if (arg_a < arg_b) return comparison_t::less; if (arg_a > arg_b) return comparison_t::more; return comparison_t::equal; });
            compare_op_t::make<>::op<comparison_t,  int64_t,   int64_t  >([](int64_t   arg_a, int64_t   arg_b) -> comparison_t { if (arg_a < arg_b) return comparison_t::less; if (arg_a > arg_b) return comparison_t::more; return comparison_t::equal; });
            compare_op_t::make<>::op<comparison_t,  uint8_t,   uint8_t  >([](uint8_t   arg_a, uint8_t   arg_b) -> comparison_t { if (arg_a < arg_b) return comparison_t::less; if (arg_a > arg_b) return comparison_t::more; return comparison_t::equal; });
            compare_op_t::make<>::op<comparison_t,  uint16_t,  uint16_t >([](uint16_t  arg_a, uint16_t  arg_b) -> comparison_t { if (arg_a < arg_b) return comparison_t::less; if (arg_a > arg_b) return comparison_t::more; return comparison_t::equal; });
            compare_op_t::make<>::op<comparison_t,  uint32_t,  uint32_t >([](uint32_t  arg_a, uint32_t  arg_b) -> comparison_t { if (arg_a < arg_b) return comparison_t::less; if (arg_a > arg_b) return comparison_t::more; return comparison_t::equal; });
            compare_op_t::make<>::op<comparison_t,  uint64_t,  uint64_t >([](uint64_t  arg_a, uint64_t  arg_b) -> comparison_t { if (arg_a < arg_b) return comparison_t::less; if (arg_a > arg_b) return comparison_t::more; return comparison_t::equal; });
            compare_op_t::make<>::op<comparison_t,  float,     float    >([](float     arg_a, float     arg_b) -> comparison_t { if (arg_a < arg_b) return comparison_t::less; if (arg_a > arg_b) return comparison_t::more; return comparison_t::equal; });
            compare_op_t::make<>::op<comparison_t,  double,    double   >([](double    arg_a, double    arg_b) -> comparison_t { if (arg_a < arg_b) return comparison_t::less; if (arg_a > arg_b) return comparison_t::more; return comparison_t::equal; });
            compare_op_t::make<>::op<comparison_t,  text_t,    text_t   >([](const text_t& arg_a, const text_t& arg_b) -> comparison_t { if (arg_a < arg_b) return comparison_t::less; if (arg_a > arg_b) return comparison_t::more; return comparison_t::equal; });
            compare_op_t::make<>::op<comparison_t,  str_ptr_t, str_ptr_t>([](str_ptr_t arg_a, str_ptr_t arg_b) -> comparison_t { const int result = std::wcscmp(arg_a ? arg_a : L"", arg_b ? arg_b : L""); if (result < 0) return comparison_t::less; if (result > 0) return comparison_t::more; return comparison_t::equal; });
            compare_op_t::make<>::op<comparison_t,  str_ptr_t, text_t   >([](str_ptr_t arg_a, const text_t& arg_b) -> comparison_t { const text_t t_a(arg_a ? arg_a : L""); if (t_a < arg_b) return comparison_t::less; if (t_a > arg_b) return comparison_t::more; return comparison_t::equal; });
            compare_op_t::make<>::op<comparison_t,  text_t,    str_ptr_t>([](const text_t& arg_a, str_ptr_t arg_b) -> comparison_t { const text_t t_b(arg_b ? arg_b : L""); if (arg_a < t_b) return comparison_t::less; if (arg_a > t_b) return comparison_t::more; return comparison_t::equal; });
         }
      };

      compare_op_init_t compare_op_init;
   }

   void compare_op_t::register_ops()
   {
      // Needed so that the global operations are initialized in the tests.
      // All that is needed is to enter this file to create the globals.
   }
}
