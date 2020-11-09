#include <dak/any_op/dominant_op.h>

namespace dak::any_op
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Conversion from a type to another.

   namespace
   {
      struct dominant_op_init_t
      {
         dominant_op_init_t()
         {
            unary_op_t<dominant_op_t>::make_op<int8_t, bool,     int8_t>([](bool arg_b) -> int8_t { return static_cast<int8_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<int8_t, char,     int8_t>([](char arg_b) -> int8_t { return static_cast<int8_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<int8_t, wchar_t,  int8_t>([](wchar_t arg_b) -> int8_t { return static_cast<int8_t>(arg_b); });

            unary_op_t<dominant_op_t>::make_op<uint8_t, bool,     uint8_t>([](bool arg_b) -> uint8_t { return static_cast<uint8_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<uint8_t, char,     uint8_t>([](char arg_b) -> uint8_t { return static_cast<uint8_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<uint8_t, wchar_t,  uint8_t>([](wchar_t arg_b) -> uint8_t { return static_cast<uint8_t>(arg_b); });

            unary_op_t<dominant_op_t>::make_op<int16_t, bool,     int16_t>([](bool arg_b) -> int16_t { return static_cast<int16_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<int16_t, char,     int16_t>([](char arg_b) -> int16_t { return static_cast<int16_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<int16_t, wchar_t,  int16_t>([](wchar_t arg_b) -> int16_t { return static_cast<int16_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<int16_t, int8_t,   int16_t>([](int8_t arg_b) -> int16_t { return static_cast<int16_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<int16_t, uint8_t,  int16_t>([](uint8_t arg_b) -> int16_t { return static_cast<int16_t>(arg_b); });

            unary_op_t<dominant_op_t>::make_op<uint16_t, bool,     uint16_t>([](bool arg_b) -> uint16_t { return static_cast<uint16_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<uint16_t, char,     uint16_t>([](char arg_b) -> uint16_t { return static_cast<uint16_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<uint16_t, wchar_t,  uint16_t>([](wchar_t arg_b) -> uint16_t { return static_cast<uint16_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<uint16_t, int8_t,   uint16_t>([](int8_t arg_b) -> uint16_t { return static_cast<uint16_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<uint16_t, uint8_t,  uint16_t>([](uint8_t arg_b) -> uint16_t { return static_cast<uint16_t>(arg_b); });

            unary_op_t<dominant_op_t>::make_op<int32_t, bool,     int32_t>([](bool arg_b) -> int32_t { return static_cast<int32_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<int32_t, char,     int32_t>([](char arg_b) -> int32_t { return static_cast<int32_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<int32_t, wchar_t,  int32_t>([](wchar_t arg_b) -> int32_t { return static_cast<int32_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<int32_t, int8_t,   int32_t>([](int8_t arg_b) -> int32_t { return static_cast<int32_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<int32_t, uint8_t,  int32_t>([](uint8_t arg_b) -> int32_t { return static_cast<int32_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<int32_t, int16_t,  int32_t>([](int16_t arg_b) -> int32_t { return static_cast<int32_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<int32_t, uint16_t, int32_t>([](uint16_t arg_b) -> int32_t { return static_cast<int32_t>(arg_b); });

            unary_op_t<dominant_op_t>::make_op<uint32_t, bool,     uint32_t>([](bool arg_b) -> uint32_t { return static_cast<uint32_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<uint32_t, char,     uint32_t>([](char arg_b) -> uint32_t { return static_cast<uint32_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<uint32_t, wchar_t,  uint32_t>([](wchar_t arg_b) -> uint32_t { return static_cast<uint32_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<uint32_t, int8_t,   uint32_t>([](int8_t arg_b) -> uint32_t { return static_cast<uint32_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<uint32_t, uint8_t,  uint32_t>([](uint8_t arg_b) -> uint32_t { return static_cast<uint32_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<uint32_t, int16_t,  uint32_t>([](int16_t arg_b) -> uint32_t { return static_cast<uint32_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<uint32_t, uint16_t, uint32_t>([](uint16_t arg_b) -> uint32_t { return static_cast<uint32_t>(arg_b); });

            unary_op_t<dominant_op_t>::make_op<int64_t, bool,     int64_t>([](bool arg_b) -> int64_t { return static_cast<int64_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<int64_t, char,     int64_t>([](char arg_b) -> int64_t { return static_cast<int64_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<int64_t, wchar_t,  int64_t>([](wchar_t arg_b) -> int64_t { return static_cast<int64_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<int64_t, int8_t,   int64_t>([](int8_t arg_b) -> int64_t { return static_cast<int64_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<int64_t, uint8_t,  int64_t>([](uint8_t arg_b) -> int64_t { return static_cast<int64_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<int64_t, int16_t,  int64_t>([](int16_t arg_b) -> int64_t { return static_cast<int64_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<int64_t, uint16_t, int64_t>([](uint16_t arg_b) -> int64_t { return static_cast<int64_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<int64_t, int32_t,  int64_t>([](int32_t arg_b) -> int64_t { return static_cast<int64_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<int64_t, uint32_t, int64_t>([](uint32_t arg_b) -> int64_t { return static_cast<int64_t>(arg_b); });

            unary_op_t<dominant_op_t>::make_op<uint64_t, bool,     uint64_t>([](bool arg_b) -> uint64_t { return static_cast<uint64_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<uint64_t, char,     uint64_t>([](char arg_b) -> uint64_t { return static_cast<uint64_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<uint64_t, wchar_t,  uint64_t>([](wchar_t arg_b) -> uint64_t { return static_cast<uint64_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<uint64_t, int8_t,   uint64_t>([](int8_t arg_b) -> uint64_t { return static_cast<uint64_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<uint64_t, uint8_t,  uint64_t>([](uint8_t arg_b) -> uint64_t { return static_cast<uint64_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<uint64_t, int16_t,  uint64_t>([](int16_t arg_b) -> uint64_t { return static_cast<uint64_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<uint64_t, uint16_t, uint64_t>([](uint16_t arg_b) -> uint64_t { return static_cast<uint64_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<uint64_t, int32_t,  uint64_t>([](int32_t arg_b) -> uint64_t { return static_cast<uint64_t>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<uint64_t, uint32_t, uint64_t>([](uint32_t arg_b) -> uint64_t { return static_cast<uint64_t>(arg_b); });

            unary_op_t<dominant_op_t>::make_op<float, bool,      float>([](bool arg_b) -> float { return static_cast<float>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<float, char,      float>([](char arg_b) -> float { return static_cast<float>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<float, wchar_t,   float>([](wchar_t arg_b) -> float { return static_cast<float>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<float, int8_t,    float>([](int8_t arg_b) -> float { return static_cast<float>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<float, uint8_t,   float>([](uint8_t arg_b) -> float { return static_cast<float>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<float, int16_t,   float>([](int16_t arg_b) -> float { return static_cast<float>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<float, uint16_t,  float>([](uint16_t arg_b) -> float { return static_cast<float>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<float, int32_t,   float>([](int32_t arg_b) -> float { return static_cast<float>(arg_b); }); // Note: cheating a bit since float only have 23-bit mantissa...
            unary_op_t<dominant_op_t>::make_op<float, uint32_t,  float>([](uint32_t arg_b) -> float { return static_cast<float>(arg_b); }); // Note: cheating a bit since float only have 23-bit mantissa...
            unary_op_t<dominant_op_t>::make_op<float, int64_t,   float>([](int64_t arg_b) -> float { return static_cast<float>(arg_b); }); // Note: cheating a lot since float only have 23-bit mantissa...
            unary_op_t<dominant_op_t>::make_op<float, uint64_t,  float>([](uint64_t arg_b) -> float { return static_cast<float>(arg_b); }); // Note: cheating a lot since float only have 23-bit mantissa...

            unary_op_t<dominant_op_t>::make_op<double, bool,      double>([](bool arg_b) -> double { return static_cast<double>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<double, char,      double>([](char arg_b) -> double { return static_cast<double>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<double, wchar_t,   double>([](wchar_t arg_b) -> double { return static_cast<double>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<double, int8_t,    double>([](int8_t arg_b) -> double { return static_cast<double>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<double, uint8_t,   double>([](uint8_t arg_b) -> double { return static_cast<double>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<double, int16_t,   double>([](int16_t arg_b) -> double { return static_cast<double>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<double, uint16_t, double>([](uint16_t arg_b) -> double { return static_cast<double>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<double, int32_t,   double>([](int32_t arg_b) -> double { return static_cast<double>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<double, uint32_t, double>([](uint32_t arg_b) -> double { return static_cast<double>(arg_b); });
            unary_op_t<dominant_op_t>::make_op<double, int64_t,   double>([](int64_t arg_b) -> double { return static_cast<double>(arg_b); }); // Note: cheating a bit since double only have 52-bit mantissa...
            unary_op_t<dominant_op_t>::make_op<double, uint64_t,  double>([](uint64_t arg_b) -> double { return static_cast<double>(arg_b); }); // Note: cheating a bit since double only have 52-bit mantissa...
            unary_op_t<dominant_op_t>::make_op<double, float,     double>([](float arg_b) -> double { return static_cast<double>(arg_b); });
         }
      };

      dominant_op_init_t dominant_op_init;
   }

   void dominant_op_t::register_ops()
   {
      // Needed so that the global operations are initialized in the tests.
      // All that is needed is to enter this file to create the globals.
   }
}
