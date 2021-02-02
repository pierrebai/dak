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
            dominant_op_t::make<int8_t>::op<int8_t, bool   >([](bool arg_b) -> int8_t { return static_cast<int8_t>(arg_b); });
            dominant_op_t::make<int8_t>::op<int8_t, char   >([](char arg_b) -> int8_t { return static_cast<int8_t>(arg_b); });
            dominant_op_t::make<int8_t>::op<int8_t, wchar_t>([](wchar_t arg_b) -> int8_t { return static_cast<int8_t>(arg_b); });

            dominant_op_t::make<uint8_t>::op<uint8_t, bool   >([](bool arg_b) -> uint8_t { return static_cast<uint8_t>(arg_b); });
            dominant_op_t::make<uint8_t>::op<uint8_t, char   >([](char arg_b) -> uint8_t { return static_cast<uint8_t>(arg_b); });
            dominant_op_t::make<uint8_t>::op<uint8_t, wchar_t>([](wchar_t arg_b) -> uint8_t { return static_cast<uint8_t>(arg_b); });

            dominant_op_t::make<int16_t>::op<int16_t, bool   >([](bool arg_b) -> int16_t { return static_cast<int16_t>(arg_b); });
            dominant_op_t::make<int16_t>::op<int16_t, char   >([](char arg_b) -> int16_t { return static_cast<int16_t>(arg_b); });
            dominant_op_t::make<int16_t>::op<int16_t, wchar_t>([](wchar_t arg_b) -> int16_t { return static_cast<int16_t>(arg_b); });
            dominant_op_t::make<int16_t>::op<int16_t, int8_t >([](int8_t arg_b) -> int16_t { return static_cast<int16_t>(arg_b); });
            dominant_op_t::make<int16_t>::op<int16_t, uint8_t>([](uint8_t arg_b) -> int16_t { return static_cast<int16_t>(arg_b); });

            dominant_op_t::make< uint16_t>::op<uint16_t, bool   >([](bool arg_b) -> uint16_t { return static_cast<uint16_t>(arg_b); });
            dominant_op_t::make< uint16_t>::op<uint16_t, char   >([](char arg_b) -> uint16_t { return static_cast<uint16_t>(arg_b); });
            dominant_op_t::make< uint16_t>::op<uint16_t, wchar_t>([](wchar_t arg_b) -> uint16_t { return static_cast<uint16_t>(arg_b); });
            dominant_op_t::make< uint16_t>::op<uint16_t, int8_t >([](int8_t arg_b) -> uint16_t { return static_cast<uint16_t>(arg_b); });
            dominant_op_t::make< uint16_t>::op<uint16_t, uint8_t>([](uint8_t arg_b) -> uint16_t { return static_cast<uint16_t>(arg_b); });

            dominant_op_t::make<int32_t>::op<int32_t, bool    >([](bool arg_b) -> int32_t { return static_cast<int32_t>(arg_b); });
            dominant_op_t::make<int32_t>::op<int32_t, char    >([](char arg_b) -> int32_t { return static_cast<int32_t>(arg_b); });
            dominant_op_t::make<int32_t>::op<int32_t, wchar_t >([](wchar_t arg_b) -> int32_t { return static_cast<int32_t>(arg_b); });
            dominant_op_t::make<int32_t>::op<int32_t, int8_t  >([](int8_t arg_b) -> int32_t { return static_cast<int32_t>(arg_b); });
            dominant_op_t::make<int32_t>::op<int32_t, uint8_t >([](uint8_t arg_b) -> int32_t { return static_cast<int32_t>(arg_b); });
            dominant_op_t::make<int32_t>::op<int32_t, int16_t >([](int16_t arg_b) -> int32_t { return static_cast<int32_t>(arg_b); });
            dominant_op_t::make<int32_t>::op<int32_t, uint16_t>([](uint16_t arg_b) -> int32_t { return static_cast<int32_t>(arg_b); });

            dominant_op_t::make<uint32_t>::op<uint32_t, bool    >([](bool arg_b) -> uint32_t { return static_cast<uint32_t>(arg_b); });
            dominant_op_t::make<uint32_t>::op<uint32_t, char    >([](char arg_b) -> uint32_t { return static_cast<uint32_t>(arg_b); });
            dominant_op_t::make<uint32_t>::op<uint32_t, wchar_t >([](wchar_t arg_b) -> uint32_t { return static_cast<uint32_t>(arg_b); });
            dominant_op_t::make<uint32_t>::op<uint32_t, int8_t  >([](int8_t arg_b) -> uint32_t { return static_cast<uint32_t>(arg_b); });
            dominant_op_t::make<uint32_t>::op<uint32_t, uint8_t >([](uint8_t arg_b) -> uint32_t { return static_cast<uint32_t>(arg_b); });
            dominant_op_t::make<uint32_t>::op<uint32_t, int16_t >([](int16_t arg_b) -> uint32_t { return static_cast<uint32_t>(arg_b); });
            dominant_op_t::make<uint32_t>::op<uint32_t, uint16_t>([](uint16_t arg_b) -> uint32_t { return static_cast<uint32_t>(arg_b); });

            dominant_op_t::make<int64_t>::op<int64_t, bool    >([](bool arg_b) -> int64_t { return static_cast<int64_t>(arg_b); });
            dominant_op_t::make<int64_t>::op<int64_t, char    >([](char arg_b) -> int64_t { return static_cast<int64_t>(arg_b); });
            dominant_op_t::make<int64_t>::op<int64_t, wchar_t >([](wchar_t arg_b) -> int64_t { return static_cast<int64_t>(arg_b); });
            dominant_op_t::make<int64_t>::op<int64_t, int8_t  >([](int8_t arg_b) -> int64_t { return static_cast<int64_t>(arg_b); });
            dominant_op_t::make<int64_t>::op<int64_t, uint8_t >([](uint8_t arg_b) -> int64_t { return static_cast<int64_t>(arg_b); });
            dominant_op_t::make<int64_t>::op<int64_t, int16_t >([](int16_t arg_b) -> int64_t { return static_cast<int64_t>(arg_b); });
            dominant_op_t::make<int64_t>::op<int64_t, uint16_t>([](uint16_t arg_b) -> int64_t { return static_cast<int64_t>(arg_b); });
            dominant_op_t::make<int64_t>::op<int64_t, int32_t >([](int32_t arg_b) -> int64_t { return static_cast<int64_t>(arg_b); });
            dominant_op_t::make<int64_t>::op<int64_t, uint32_t>([](uint32_t arg_b) -> int64_t { return static_cast<int64_t>(arg_b); });

            dominant_op_t::make<uint64_t>::op<uint64_t, bool    >([](bool arg_b) -> uint64_t { return static_cast<uint64_t>(arg_b); });
            dominant_op_t::make<uint64_t>::op<uint64_t, char    >([](char arg_b) -> uint64_t { return static_cast<uint64_t>(arg_b); });
            dominant_op_t::make<uint64_t>::op<uint64_t, wchar_t >([](wchar_t arg_b) -> uint64_t { return static_cast<uint64_t>(arg_b); });
            dominant_op_t::make<uint64_t>::op<uint64_t, int8_t  >([](int8_t arg_b) -> uint64_t { return static_cast<uint64_t>(arg_b); });
            dominant_op_t::make<uint64_t>::op<uint64_t, uint8_t >([](uint8_t arg_b) -> uint64_t { return static_cast<uint64_t>(arg_b); });
            dominant_op_t::make<uint64_t>::op<uint64_t, int16_t >([](int16_t arg_b) -> uint64_t { return static_cast<uint64_t>(arg_b); });
            dominant_op_t::make<uint64_t>::op<uint64_t, uint16_t>([](uint16_t arg_b) -> uint64_t { return static_cast<uint64_t>(arg_b); });
            dominant_op_t::make<uint64_t>::op<uint64_t, int32_t >([](int32_t arg_b) -> uint64_t { return static_cast<uint64_t>(arg_b); });
            dominant_op_t::make<uint64_t>::op<uint64_t, uint32_t>([](uint32_t arg_b) -> uint64_t { return static_cast<uint64_t>(arg_b); });

            dominant_op_t::make<float>::op<float, bool    >([](bool arg_b) -> float { return static_cast<float>(arg_b); });
            dominant_op_t::make<float>::op<float, char    >([](char arg_b) -> float { return static_cast<float>(arg_b); });
            dominant_op_t::make<float>::op<float, wchar_t >([](wchar_t arg_b) -> float { return static_cast<float>(arg_b); });
            dominant_op_t::make<float>::op<float, int8_t  >([](int8_t arg_b) -> float { return static_cast<float>(arg_b); });
            dominant_op_t::make<float>::op<float, uint8_t >([](uint8_t arg_b) -> float { return static_cast<float>(arg_b); });
            dominant_op_t::make<float>::op<float, int16_t >([](int16_t arg_b) -> float { return static_cast<float>(arg_b); });
            dominant_op_t::make<float>::op<float, uint16_t>([](uint16_t arg_b) -> float { return static_cast<float>(arg_b); });
            dominant_op_t::make<float>::op<float, int32_t >([](int32_t arg_b) -> float { return static_cast<float>(arg_b); }); // Note: cheating a bit since float only have 23-bit mantissa...
            dominant_op_t::make<float>::op<float, uint32_t>([](uint32_t arg_b) -> float { return static_cast<float>(arg_b); }); // Note: cheating a bit since float only have 23-bit mantissa...
            dominant_op_t::make<float>::op<float, int64_t >([](int64_t arg_b) -> float { return static_cast<float>(arg_b); }); // Note: cheating a lot since float only have 23-bit mantissa...
            dominant_op_t::make<float>::op<float, uint64_t>([](uint64_t arg_b) -> float { return static_cast<float>(arg_b); }); // Note: cheating a lot since float only have 23-bit mantissa...

            dominant_op_t::make<double>::op<double, bool    >([](bool arg_b) -> double { return static_cast<double>(arg_b); });
            dominant_op_t::make<double>::op<double, char    >([](char arg_b) -> double { return static_cast<double>(arg_b); });
            dominant_op_t::make<double>::op<double, wchar_t >([](wchar_t arg_b) -> double { return static_cast<double>(arg_b); });
            dominant_op_t::make<double>::op<double, int8_t  >([](int8_t arg_b) -> double { return static_cast<double>(arg_b); });
            dominant_op_t::make<double>::op<double, uint8_t >([](uint8_t arg_b) -> double { return static_cast<double>(arg_b); });
            dominant_op_t::make<double>::op<double, int16_t >([](int16_t arg_b) -> double { return static_cast<double>(arg_b); });
            dominant_op_t::make<double>::op<double, uint16_t>([](uint16_t arg_b) -> double { return static_cast<double>(arg_b); });
            dominant_op_t::make<double>::op<double, int32_t >([](int32_t arg_b) -> double { return static_cast<double>(arg_b); });
            dominant_op_t::make<double>::op<double, uint32_t>([](uint32_t arg_b) -> double { return static_cast<double>(arg_b); });
            dominant_op_t::make<double>::op<double, int64_t >([](int64_t arg_b) -> double { return static_cast<double>(arg_b); }); // Note: cheating a bit since double only have 52-bit mantissa...
            dominant_op_t::make<double>::op<double, uint64_t>([](uint64_t arg_b) -> double { return static_cast<double>(arg_b); }); // Note: cheating a bit since double only have 52-bit mantissa...
            dominant_op_t::make<double>::op<double, float   >([](float arg_b) -> double { return static_cast<double>(arg_b); });
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
