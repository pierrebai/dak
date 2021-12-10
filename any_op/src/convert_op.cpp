#include <dak/any_op/convert_op.h>

namespace dak::any_op
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Conversion from a type to another.

   namespace
   {
      struct convert_op_init_t
      {
         convert_op_init_t()
         {
            convert_op_t::make<char>::op<char, bool    >([](bool arg_b) -> char { return static_cast<char>(arg_b); });
            convert_op_t::make<char>::op<char, char    >([](char arg_b) -> char { return static_cast<char>(arg_b); });
            convert_op_t::make<char>::op<char, wchar_t >([](wchar_t arg_b) -> char { return static_cast<char>(arg_b); });
            convert_op_t::make<char>::op<char, int8_t  >([](char arg_b) -> char { return static_cast<char>(arg_b); });
            convert_op_t::make<char>::op<char, int16_t >([](int16_t arg_b) -> char { return static_cast<char>(arg_b); });
            convert_op_t::make<char>::op<char, int32_t >([](int32_t arg_b) -> char { return static_cast<char>(arg_b); });
            convert_op_t::make<char>::op<char, int64_t >([](int64_t arg_b) -> char { return static_cast<char>(arg_b); });
            convert_op_t::make<char>::op<char, uint8_t >([](uint8_t arg_b) -> char { return static_cast<char>(arg_b); });
            convert_op_t::make<char>::op<char, uint16_t>([](uint16_t arg_b) -> char { return static_cast<char>(arg_b); });
            convert_op_t::make<char>::op<char, uint32_t>([](uint32_t arg_b) -> char { return static_cast<char>(arg_b); });
            convert_op_t::make<char>::op<char, uint64_t>([](uint64_t arg_b) -> char { return static_cast<char>(arg_b); });
            convert_op_t::make<char>::op<char, float   >([](float arg_b) -> char { return static_cast<char>(arg_b); });
            convert_op_t::make<char>::op<char, double  >([](double arg_b) -> char { return static_cast<char>(arg_b); });

            convert_op_t::make<wchar_t>::op<wchar_t, bool    >([](bool arg_b) -> wchar_t { return static_cast<wchar_t>(arg_b); });
            convert_op_t::make<wchar_t>::op<wchar_t, char    >([](char arg_b) -> wchar_t { return static_cast<wchar_t>(arg_b); });
            convert_op_t::make<wchar_t>::op<wchar_t, wchar_t >([](wchar_t arg_b) -> wchar_t { return static_cast<wchar_t>(arg_b); });
            convert_op_t::make<wchar_t>::op<wchar_t, int8_t  >([](int8_t arg_b) -> wchar_t { return static_cast<wchar_t>(arg_b); });
            convert_op_t::make<wchar_t>::op<wchar_t, int16_t >([](int16_t arg_b) -> wchar_t { return static_cast<wchar_t>(arg_b); });
            convert_op_t::make<wchar_t>::op<wchar_t, int32_t >([](int32_t arg_b) -> wchar_t { return static_cast<wchar_t>(arg_b); });
            convert_op_t::make<wchar_t>::op<wchar_t, int64_t >([](int64_t arg_b) -> wchar_t { return static_cast<wchar_t>(arg_b); });
            convert_op_t::make<wchar_t>::op<wchar_t, uint8_t >([](uint8_t arg_b) -> wchar_t { return static_cast<wchar_t>(arg_b); });
            convert_op_t::make<wchar_t>::op<wchar_t, uint16_t>([](uint16_t arg_b) -> wchar_t { return static_cast<wchar_t>(arg_b); });
            convert_op_t::make<wchar_t>::op<wchar_t, uint32_t>([](uint32_t arg_b) -> wchar_t { return static_cast<wchar_t>(arg_b); });
            convert_op_t::make<wchar_t>::op<wchar_t, uint64_t>([](uint64_t arg_b) -> wchar_t { return static_cast<wchar_t>(arg_b); });
            convert_op_t::make<wchar_t>::op<wchar_t, float   >([](float arg_b) -> wchar_t { return static_cast<wchar_t>(arg_b); });
            convert_op_t::make<wchar_t>::op<wchar_t, double  >([](double arg_b) -> wchar_t { return static_cast<wchar_t>(arg_b); });

            convert_op_t::make<int8_t>::op<int8_t, bool    >([](bool arg_b) -> int8_t { return static_cast<int8_t>(arg_b); });
            convert_op_t::make<int8_t>::op<int8_t, char    >([](char arg_b) -> int8_t { return static_cast<int8_t>(arg_b); });
            convert_op_t::make<int8_t>::op<int8_t, wchar_t >([](wchar_t arg_b) -> int8_t { return static_cast<int8_t>(arg_b); });
            convert_op_t::make<int8_t>::op<int8_t, int8_t  >([](int8_t arg_b) -> int8_t { return static_cast<int8_t>(arg_b); });
            convert_op_t::make<int8_t>::op<int8_t, int16_t >([](int16_t arg_b) -> int8_t { return static_cast<int8_t>(arg_b); });
            convert_op_t::make<int8_t>::op<int8_t, int32_t >([](int32_t arg_b) -> int8_t { return static_cast<int8_t>(arg_b); });
            convert_op_t::make<int8_t>::op<int8_t, int64_t >([](int64_t arg_b) -> int8_t { return static_cast<int8_t>(arg_b); });
            convert_op_t::make<int8_t>::op<int8_t, uint8_t >([](uint8_t arg_b) -> int8_t { return static_cast<int8_t>(arg_b); });
            convert_op_t::make<int8_t>::op<int8_t, uint16_t>([](uint16_t arg_b) -> int8_t { return static_cast<int8_t>(arg_b); });
            convert_op_t::make<int8_t>::op<int8_t, uint32_t>([](uint32_t arg_b) -> int8_t { return static_cast<int8_t>(arg_b); });
            convert_op_t::make<int8_t>::op<int8_t, uint64_t>([](uint64_t arg_b) -> int8_t { return static_cast<int8_t>(arg_b); });
            convert_op_t::make<int8_t>::op<int8_t, float   >([](float arg_b) -> int8_t { return static_cast<int8_t>(arg_b); });
            convert_op_t::make<int8_t>::op<int8_t, double  >([](double arg_b) -> int8_t { return static_cast<int8_t>(arg_b); });

            convert_op_t::make<uint8_t>::op<uint8_t, bool    >([](bool arg_b) -> uint8_t { return static_cast<uint8_t>(arg_b); });
            convert_op_t::make<uint8_t>::op<uint8_t, char    >([](char arg_b) -> uint8_t { return static_cast<uint8_t>(arg_b); });
            convert_op_t::make<uint8_t>::op<uint8_t, wchar_t >([](wchar_t arg_b) -> uint8_t { return static_cast<uint8_t>(arg_b); });
            convert_op_t::make<uint8_t>::op<uint8_t, int8_t  >([](int8_t arg_b) -> uint8_t { return static_cast<uint8_t>(arg_b); });
            convert_op_t::make<uint8_t>::op<uint8_t, int16_t >([](int16_t arg_b) -> uint8_t { return static_cast<uint8_t>(arg_b); });
            convert_op_t::make<uint8_t>::op<uint8_t, int32_t >([](int32_t arg_b) -> uint8_t { return static_cast<uint8_t>(arg_b); });
            convert_op_t::make<uint8_t>::op<uint8_t, int64_t >([](int64_t arg_b) -> uint8_t { return static_cast<uint8_t>(arg_b); });
            convert_op_t::make<uint8_t>::op<uint8_t, uint8_t >([](uint8_t arg_b) -> uint8_t { return static_cast<uint8_t>(arg_b); });
            convert_op_t::make<uint8_t>::op<uint8_t, uint16_t>([](uint16_t arg_b) -> uint8_t { return static_cast<uint8_t>(arg_b); });
            convert_op_t::make<uint8_t>::op<uint8_t, uint32_t>([](uint32_t arg_b) -> uint8_t { return static_cast<uint8_t>(arg_b); });
            convert_op_t::make<uint8_t>::op<uint8_t, uint64_t>([](uint64_t arg_b) -> uint8_t { return static_cast<uint8_t>(arg_b); });
            convert_op_t::make<uint8_t>::op<uint8_t, float   >([](float arg_b) -> uint8_t { return static_cast<uint8_t>(arg_b); });
            convert_op_t::make<uint8_t>::op<uint8_t, double  >([](double arg_b) -> uint8_t { return static_cast<uint8_t>(arg_b); });

            convert_op_t::make<int16_t>::op<int16_t, bool    >([](bool arg_b) -> int16_t { return static_cast<int16_t>(arg_b); });
            convert_op_t::make<int16_t>::op<int16_t, char    >([](char arg_b) -> int16_t { return static_cast<int16_t>(arg_b); });
            convert_op_t::make<int16_t>::op<int16_t, wchar_t >([](wchar_t arg_b) -> int16_t { return static_cast<int16_t>(arg_b); });
            convert_op_t::make<int16_t>::op<int16_t, int8_t  >([](int8_t arg_b) -> int16_t { return static_cast<int16_t>(arg_b); });
            convert_op_t::make<int16_t>::op<int16_t, int16_t >([](int16_t arg_b) -> int16_t { return static_cast<int16_t>(arg_b); });
            convert_op_t::make<int16_t>::op<int16_t, int32_t >([](int32_t arg_b) -> int16_t { return static_cast<int16_t>(arg_b); });
            convert_op_t::make<int16_t>::op<int16_t, int64_t >([](int64_t arg_b) -> int16_t { return static_cast<int16_t>(arg_b); });
            convert_op_t::make<int16_t>::op<int16_t, uint8_t >([](uint8_t arg_b) -> int16_t { return static_cast<int16_t>(arg_b); });
            convert_op_t::make<int16_t>::op<int16_t, uint16_t>([](uint16_t arg_b) -> int16_t { return static_cast<int16_t>(arg_b); });
            convert_op_t::make<int16_t>::op<int16_t, uint32_t>([](uint32_t arg_b) -> int16_t { return static_cast<int16_t>(arg_b); });
            convert_op_t::make<int16_t>::op<int16_t, uint64_t>([](uint64_t arg_b) -> int16_t { return static_cast<int16_t>(arg_b); });
            convert_op_t::make<int16_t>::op<int16_t, float   >([](float arg_b) -> int16_t { return static_cast<int16_t>(arg_b); });
            convert_op_t::make<int16_t>::op<int16_t, double  >([](double arg_b) -> int16_t { return static_cast<int16_t>(arg_b); });

            convert_op_t::make<uint16_t>::op<uint16_t, bool    >([](bool arg_b) -> uint16_t { return static_cast<uint16_t>(arg_b); });
            convert_op_t::make<uint16_t>::op<uint16_t, char    >([](char arg_b) -> uint16_t { return static_cast<uint16_t>(arg_b); });
            convert_op_t::make<uint16_t>::op<uint16_t, wchar_t >([](wchar_t arg_b) -> uint16_t { return static_cast<uint16_t>(arg_b); });
            convert_op_t::make<uint16_t>::op<uint16_t, int8_t  >([](int8_t arg_b) -> uint16_t { return static_cast<uint16_t>(arg_b); });
            convert_op_t::make<uint16_t>::op<uint16_t, int16_t >([](int16_t arg_b) -> uint16_t { return static_cast<uint16_t>(arg_b); });
            convert_op_t::make<uint16_t>::op<uint16_t, int32_t >([](int32_t arg_b) -> uint16_t { return static_cast<uint16_t>(arg_b); });
            convert_op_t::make<uint16_t>::op<uint16_t, int64_t >([](int64_t arg_b) -> uint16_t { return static_cast<uint16_t>(arg_b); });
            convert_op_t::make<uint16_t>::op<uint16_t, uint8_t >([](uint8_t arg_b) -> uint16_t { return static_cast<uint16_t>(arg_b); });
            convert_op_t::make<uint16_t>::op<uint16_t, uint16_t>([](uint16_t arg_b) -> uint16_t { return static_cast<uint16_t>(arg_b); });
            convert_op_t::make<uint16_t>::op<uint16_t, uint32_t>([](uint32_t arg_b) -> uint16_t { return static_cast<uint16_t>(arg_b); });
            convert_op_t::make<uint16_t>::op<uint16_t, uint64_t>([](uint64_t arg_b) -> uint16_t { return static_cast<uint16_t>(arg_b); });
            convert_op_t::make<uint16_t>::op<uint16_t, float   >([](float arg_b) -> uint16_t { return static_cast<uint16_t>(arg_b); });
            convert_op_t::make<uint16_t>::op<uint16_t, double  >([](double arg_b) -> uint16_t { return static_cast<uint16_t>(arg_b); });

            convert_op_t::make<int32_t>::op<int32_t, bool    >([](bool arg_b) -> int32_t { return static_cast<int32_t>(arg_b); });
            convert_op_t::make<int32_t>::op<int32_t, char     >([](char arg_b) -> int32_t { return static_cast<int32_t>(arg_b); });
            convert_op_t::make<int32_t>::op<int32_t, wchar_t >([](wchar_t arg_b) -> int32_t { return static_cast<int32_t>(arg_b); });
            convert_op_t::make<int32_t>::op<int32_t, int8_t  >([](int8_t arg_b) -> int32_t { return static_cast<int32_t>(arg_b); });
            convert_op_t::make<int32_t>::op<int32_t, int16_t >([](int16_t arg_b) -> int32_t { return static_cast<int32_t>(arg_b); });
            convert_op_t::make<int32_t>::op<int32_t, int32_t >([](int32_t arg_b) -> int32_t { return static_cast<int32_t>(arg_b); });
            convert_op_t::make<int32_t>::op<int32_t, int64_t >([](int64_t arg_b) -> int32_t { return static_cast<int32_t>(arg_b); });
            convert_op_t::make<int32_t>::op<int32_t, uint8_t >([](uint8_t arg_b) -> int32_t { return static_cast<int32_t>(arg_b); });
            convert_op_t::make<int32_t>::op<int32_t, uint16_t>([](uint16_t arg_b) -> int32_t { return static_cast<int32_t>(arg_b); });
            convert_op_t::make<int32_t>::op<int32_t, uint32_t>([](uint32_t arg_b) -> int32_t { return static_cast<int32_t>(arg_b); });
            convert_op_t::make<int32_t>::op<int32_t, uint64_t>([](uint64_t arg_b) -> int32_t { return static_cast<int32_t>(arg_b); });
            convert_op_t::make<int32_t>::op<int32_t, float   >([](float arg_b) -> int32_t { return static_cast<int32_t>(arg_b); });
            convert_op_t::make<int32_t>::op<int32_t, double  >([](double arg_b) -> int32_t { return static_cast<int32_t>(arg_b); });

            convert_op_t::make<uint32_t>::op<uint32_t, bool    >([](bool arg_b) -> uint32_t { return static_cast<uint32_t>(arg_b); });
            convert_op_t::make<uint32_t>::op<uint32_t, char    >([](char arg_b) -> uint32_t { return static_cast<uint32_t>(arg_b); });
            convert_op_t::make<uint32_t>::op<uint32_t, wchar_t >([](wchar_t arg_b) -> uint32_t { return static_cast<uint32_t>(arg_b); });
            convert_op_t::make<uint32_t>::op<uint32_t, int8_t  >([](int8_t arg_b) -> uint32_t { return static_cast<uint32_t>(arg_b); });
            convert_op_t::make<uint32_t>::op<uint32_t, int16_t >([](int16_t arg_b) -> uint32_t { return static_cast<uint32_t>(arg_b); });
            convert_op_t::make<uint32_t>::op<uint32_t, int32_t >([](int32_t arg_b) -> uint32_t { return static_cast<uint32_t>(arg_b); });
            convert_op_t::make<uint32_t>::op<uint32_t, int64_t >([](int64_t arg_b) -> uint32_t { return static_cast<uint32_t>(arg_b); });
            convert_op_t::make<uint32_t>::op<uint32_t, uint8_t >([](uint8_t arg_b) -> uint32_t { return static_cast<uint32_t>(arg_b); });
            convert_op_t::make<uint32_t>::op<uint32_t, uint16_t>([](uint16_t arg_b) -> uint32_t { return static_cast<uint32_t>(arg_b); });
            convert_op_t::make<uint32_t>::op<uint32_t, uint32_t>([](uint32_t arg_b) -> uint32_t { return static_cast<uint32_t>(arg_b); });
            convert_op_t::make<uint32_t>::op<uint32_t, uint64_t>([](uint64_t arg_b) -> uint32_t { return static_cast<uint32_t>(arg_b); });
            convert_op_t::make<uint32_t>::op<uint32_t, float   >([](float arg_b) -> uint32_t { return static_cast<uint32_t>(arg_b); });
            convert_op_t::make<uint32_t>::op<uint32_t, double  >([](double arg_b) -> uint32_t { return static_cast<uint32_t>(arg_b); });

            convert_op_t::make<int64_t>::op<int64_t, bool    >([](bool arg_b) -> int64_t { return static_cast<int64_t>(arg_b); });
            convert_op_t::make<int64_t>::op<int64_t, char    >([](char arg_b) -> int64_t { return static_cast<int64_t>(arg_b); });
            convert_op_t::make<int64_t>::op<int64_t, wchar_t >([](wchar_t arg_b) -> int64_t { return static_cast<int64_t>(arg_b); });
            convert_op_t::make<int64_t>::op<int64_t, int8_t  >([](int8_t arg_b) -> int64_t { return static_cast<int64_t>(arg_b); });
            convert_op_t::make<int64_t>::op<int64_t, int16_t >([](int16_t arg_b) -> int64_t { return static_cast<int64_t>(arg_b); });
            convert_op_t::make<int64_t>::op<int64_t, int32_t >([](int32_t arg_b) -> int64_t { return static_cast<int64_t>(arg_b); });
            convert_op_t::make<int64_t>::op<int64_t, int64_t >([](int64_t arg_b) -> int64_t { return static_cast<int64_t>(arg_b); });
            convert_op_t::make<int64_t>::op<int64_t, uint8_t >([](uint8_t arg_b) -> int64_t { return static_cast<int64_t>(arg_b); });
            convert_op_t::make<int64_t>::op<int64_t, uint16_t>([](uint16_t arg_b) -> int64_t { return static_cast<int64_t>(arg_b); });
            convert_op_t::make<int64_t>::op<int64_t, uint32_t>([](uint32_t arg_b) -> int64_t { return static_cast<int64_t>(arg_b); });
            convert_op_t::make<int64_t>::op<int64_t, uint64_t>([](uint64_t arg_b) -> int64_t { return static_cast<int64_t>(arg_b); });
            convert_op_t::make<int64_t>::op<int64_t, float   >([](float arg_b) -> int64_t { return static_cast<int64_t>(arg_b); });
            convert_op_t::make<int64_t>::op<int64_t, double  >([](double arg_b) -> int64_t { return static_cast<int64_t>(arg_b); });

            convert_op_t::make<uint64_t>::op<uint64_t, bool    >([](bool arg_b) -> uint64_t { return static_cast<uint64_t>(arg_b); });
            convert_op_t::make<uint64_t>::op<uint64_t, char    >([](char arg_b) -> uint64_t { return static_cast<uint64_t>(arg_b); });
            convert_op_t::make<uint64_t>::op<uint64_t, wchar_t >([](wchar_t arg_b) -> uint64_t { return static_cast<uint64_t>(arg_b); });
            convert_op_t::make<uint64_t>::op<uint64_t, int8_t  >([](int8_t arg_b) -> uint64_t { return static_cast<uint64_t>(arg_b); });
            convert_op_t::make<uint64_t>::op<uint64_t, int16_t >([](int16_t arg_b) -> uint64_t { return static_cast<uint64_t>(arg_b); });
            convert_op_t::make<uint64_t>::op<uint64_t, int32_t >([](int32_t arg_b) -> uint64_t { return static_cast<uint64_t>(arg_b); });
            convert_op_t::make<uint64_t>::op<uint64_t, int64_t >([](int64_t arg_b) -> uint64_t { return static_cast<uint64_t>(arg_b); });
            convert_op_t::make<uint64_t>::op<uint64_t, uint8_t >([](uint8_t arg_b) -> uint64_t { return static_cast<uint64_t>(arg_b); });
            convert_op_t::make<uint64_t>::op<uint64_t, uint16_t>([](uint16_t arg_b) -> uint64_t { return static_cast<uint64_t>(arg_b); });
            convert_op_t::make<uint64_t>::op<uint64_t, uint32_t>([](uint32_t arg_b) -> uint64_t { return static_cast<uint64_t>(arg_b); });
            convert_op_t::make<uint64_t>::op<uint64_t, uint64_t>([](uint64_t arg_b) -> uint64_t { return static_cast<uint64_t>(arg_b); });
            convert_op_t::make<uint64_t>::op<uint64_t, float   >([](float arg_b) -> uint64_t { return static_cast<uint64_t>(arg_b); });
            convert_op_t::make<uint64_t>::op<uint64_t, double  >([](double arg_b) -> uint64_t { return static_cast<uint64_t>(arg_b); });

            convert_op_t::make<bool>::op<bool, bool    >([](bool arg_b) -> bool { return static_cast<bool>(arg_b); });
            convert_op_t::make<bool>::op<bool, char    >([](char arg_b) -> bool { return static_cast<bool>(arg_b); });
            convert_op_t::make<bool>::op<bool, wchar_t >([](wchar_t arg_b) -> bool { return static_cast<bool>(arg_b); });
            convert_op_t::make<bool>::op<bool, int8_t  >([](int8_t arg_b) -> bool { return static_cast<bool>(arg_b); });
            convert_op_t::make<bool>::op<bool, int16_t >([](int16_t arg_b) -> bool { return static_cast<bool>(arg_b); });
            convert_op_t::make<bool>::op<bool, int32_t >([](int32_t arg_b) -> bool { return static_cast<bool>(arg_b); });
            convert_op_t::make<bool>::op<bool, int64_t >([](int64_t arg_b) -> bool { return static_cast<bool>(arg_b); });
            convert_op_t::make<bool>::op<bool, uint8_t >([](uint8_t arg_b) -> bool { return static_cast<bool>(arg_b); });
            convert_op_t::make<bool>::op<bool, uint16_t>([](uint16_t arg_b) -> bool { return static_cast<bool>(arg_b); });
            convert_op_t::make<bool>::op<bool, uint32_t>([](uint32_t arg_b) -> bool { return static_cast<bool>(arg_b); });
            convert_op_t::make<bool>::op<bool, uint64_t>([](uint64_t arg_b) -> bool { return static_cast<bool>(arg_b); });
            convert_op_t::make<bool>::op<bool, float   >([](float arg_b) -> bool { return static_cast<bool>(arg_b); });
            convert_op_t::make<bool>::op<bool, double  >([](double arg_b) -> bool { return static_cast<bool>(arg_b); });
            convert_op_t::make<bool>::op<bool, text_t  >([](const text_t& arg_b) -> bool { return static_cast<bool>(arg_b.size()); });

            convert_op_t::make<float>::op<float, bool    >([](bool arg_b) -> float { return static_cast<float>(arg_b); });
            convert_op_t::make<float>::op<float, char    >([](char arg_b) -> float { return static_cast<float>(arg_b); });
            convert_op_t::make<float>::op<float, wchar_t >([](wchar_t arg_b) -> float { return static_cast<float>(arg_b); });
            convert_op_t::make<float>::op<float, int8_t  >([](int8_t arg_b) -> float { return static_cast<float>(arg_b); });
            convert_op_t::make<float>::op<float, int16_t >([](int16_t arg_b) -> float { return static_cast<float>(arg_b); });
            convert_op_t::make<float>::op<float, int32_t >([](int32_t arg_b) -> float { return static_cast<float>(arg_b); }); // Note: cheating a bit since float only have 23-bit mantissa...
            convert_op_t::make<float>::op<float, int64_t >([](int64_t arg_b) -> float { return static_cast<float>(arg_b); }); // Note: cheating a lot since float only have 23-bit mantissa...
            convert_op_t::make<float>::op<float, uint8_t >([](uint8_t arg_b) -> float { return static_cast<float>(arg_b); });
            convert_op_t::make<float>::op<float, uint16_t>([](uint16_t arg_b) -> float { return static_cast<float>(arg_b); });
            convert_op_t::make<float>::op<float, uint32_t>([](uint32_t arg_b) -> float { return static_cast<float>(arg_b); }); // Note: cheating a bit since float only have 23-bit mantissa...
            convert_op_t::make<float>::op<float, uint64_t>([](uint64_t arg_b) -> float { return static_cast<float>(arg_b); }); // Note: cheating a lot since float only have 23-bit mantissa...
            convert_op_t::make<float>::op<float, float   >([](float arg_b) -> float { return static_cast<float>(arg_b); });
            convert_op_t::make<float>::op<float, double  >([](double arg_b) -> float { return static_cast<float>(arg_b); });

            convert_op_t::make<double>::op<double, bool    >([](bool arg_b) -> double { return static_cast<double>(arg_b); });
            convert_op_t::make<double>::op<double, char    >([](char arg_b) -> double { return static_cast<double>(arg_b); });
            convert_op_t::make<double>::op<double, wchar_t >([](wchar_t arg_b) -> double { return static_cast<double>(arg_b); });
            convert_op_t::make<double>::op<double, int8_t  >([](int8_t arg_b) -> double { return static_cast<double>(arg_b); });
            convert_op_t::make<double>::op<double, int16_t >([](int16_t arg_b) -> double { return static_cast<double>(arg_b); });
            convert_op_t::make<double>::op<double, int32_t >([](int32_t arg_b) -> double { return static_cast<double>(arg_b); });
            convert_op_t::make<double>::op<double, int64_t >([](int64_t arg_b) -> double { return static_cast<double>(arg_b); }); // Note: cheating a bit since double only have 52-bit mantissa...
            convert_op_t::make<double>::op<double, uint8_t >([](uint8_t arg_b) -> double { return static_cast<double>(arg_b); });
            convert_op_t::make<double>::op<double, uint16_t>([](uint16_t arg_b) -> double { return static_cast<double>(arg_b); });
            convert_op_t::make<double>::op<double, uint32_t>([](uint32_t arg_b) -> double { return static_cast<double>(arg_b); });
            convert_op_t::make<double>::op<double, uint64_t>([](uint64_t arg_b) -> double { return static_cast<double>(arg_b); }); // Note: cheating a bit since double only have 52-bit mantissa...
            convert_op_t::make<double>::op<double, float   >([](float arg_b) -> double { return static_cast<double>(arg_b); });
            convert_op_t::make<double>::op<double, double  >([](double arg_b) -> double { return static_cast<double>(arg_b); });

            convert_op_t::make<text_t>::op<text_t, text_t   >([](const text_t& arg_b) -> text_t { return arg_b; });
            convert_op_t::make<text_t>::op<text_t, str_ptr_t>([](str_ptr_t arg_b) -> text_t { return text_t(arg_b ? arg_b : L""); });
         }
      };

      convert_op_init_t convert_op_init;
   }

   void convert_op_t::register_ops()
   {
      // Needed so that the global operations are initialized in the tests.
      // All that is needed is to enter this file to create the globals.
   }
}
