#include <dak/any_op/is_compatible_op.h>

namespace dak::any_op
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Define which types we consider compatible.

   namespace
   {
      // Note: for some reason, Visual-Studio 2019 in C++ 2020 mode cannot
      //       deduce the N_ARY variadic template argument in the calls
      //       to ::op below when we pass the lambda directly,
      //
      //       It also fails if we replace the lambda with a real function
      //       taking no argument and returning a bool.
      //
      //       It only works when we pass an explicit std::function.
      //       The problem only manistfest itself for the nullary
      //       is_compatible_op_t. It seems the complete absence of type
      //       in a nullary function fails to be automatically deduced
      //       as an empty N_ARY variadic template...
      std::function<bool()> is_compatible([]() -> bool { return true; });

      struct is_compatible_op_init_t
      {
         is_compatible_op_init_t()
         {
            is_compatible_op_t::make<char, bool    >::op<bool>(is_compatible);
            is_compatible_op_t::make<char, char    >::op<bool>(is_compatible);
            is_compatible_op_t::make<char, wchar_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<char, int8_t  >::op<bool>(is_compatible);
            is_compatible_op_t::make<char, int16_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<char, int32_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<char, int64_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<char, uint8_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<char, uint16_t>::op<bool>(is_compatible);
            is_compatible_op_t::make<char, uint32_t>::op<bool>(is_compatible);
            is_compatible_op_t::make<char, uint64_t>::op<bool>(is_compatible);
            is_compatible_op_t::make<char, float   >::op<bool>(is_compatible);
            is_compatible_op_t::make<char, double  >::op<bool>(is_compatible);

            is_compatible_op_t::make<wchar_t, bool    >::op<bool>(is_compatible);
            is_compatible_op_t::make<wchar_t, char    >::op<bool>(is_compatible);
            is_compatible_op_t::make<wchar_t, wchar_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<wchar_t, int8_t  >::op<bool>(is_compatible);
            is_compatible_op_t::make<wchar_t, int16_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<wchar_t, int32_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<wchar_t, int64_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<wchar_t, uint8_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<wchar_t, uint16_t>::op<bool>(is_compatible);
            is_compatible_op_t::make<wchar_t, uint32_t>::op<bool>(is_compatible);
            is_compatible_op_t::make<wchar_t, uint64_t>::op<bool>(is_compatible);
            is_compatible_op_t::make<wchar_t, float   >::op<bool>(is_compatible);
            is_compatible_op_t::make<wchar_t, double  >::op<bool>(is_compatible);

            is_compatible_op_t::make<int8_t, bool    >::op<bool>(is_compatible);
            is_compatible_op_t::make<int8_t, char    >::op<bool>(is_compatible);
            is_compatible_op_t::make<int8_t, wchar_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<int8_t, int8_t  >::op<bool>(is_compatible);
            is_compatible_op_t::make<int8_t, int16_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<int8_t, int32_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<int8_t, int64_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<int8_t, uint8_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<int8_t, uint16_t>::op<bool>(is_compatible);
            is_compatible_op_t::make<int8_t, uint32_t>::op<bool>(is_compatible);
            is_compatible_op_t::make<int8_t, uint64_t>::op<bool>(is_compatible);
            is_compatible_op_t::make<int8_t, float   >::op<bool>(is_compatible);
            is_compatible_op_t::make<int8_t, double  >::op<bool>(is_compatible);

            is_compatible_op_t::make<uint8_t, bool    >::op<bool>(is_compatible);
            is_compatible_op_t::make<uint8_t, char    >::op<bool>(is_compatible);
            is_compatible_op_t::make<uint8_t, wchar_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<uint8_t, int8_t  >::op<bool>(is_compatible);
            is_compatible_op_t::make<uint8_t, int16_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<uint8_t, int32_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<uint8_t, int64_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<uint8_t, uint8_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<uint8_t, uint16_t>::op<bool>(is_compatible);
            is_compatible_op_t::make<uint8_t, uint32_t>::op<bool>(is_compatible);
            is_compatible_op_t::make<uint8_t, uint64_t>::op<bool>(is_compatible);
            is_compatible_op_t::make<uint8_t, float   >::op<bool>(is_compatible);
            is_compatible_op_t::make<uint8_t, double  >::op<bool>(is_compatible);

            is_compatible_op_t::make<int16_t, bool    >::op<bool>(is_compatible);
            is_compatible_op_t::make<int16_t, char    >::op<bool>(is_compatible);
            is_compatible_op_t::make<int16_t, wchar_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<int16_t, int8_t  >::op<bool>(is_compatible);
            is_compatible_op_t::make<int16_t, int16_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<int16_t, int32_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<int16_t, int64_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<int16_t, uint8_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<int16_t, uint16_t>::op<bool>(is_compatible);
            is_compatible_op_t::make<int16_t, uint32_t>::op<bool>(is_compatible);
            is_compatible_op_t::make<int16_t, uint64_t>::op<bool>(is_compatible);
            is_compatible_op_t::make<int16_t, float   >::op<bool>(is_compatible);
            is_compatible_op_t::make<int16_t, double  >::op<bool>(is_compatible);

            is_compatible_op_t::make<uint16_t, bool    >::op<bool>(is_compatible);
            is_compatible_op_t::make<uint16_t, char    >::op<bool>(is_compatible);
            is_compatible_op_t::make<uint16_t, wchar_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<uint16_t, int8_t  >::op<bool>(is_compatible);
            is_compatible_op_t::make<uint16_t, int16_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<uint16_t, int32_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<uint16_t, int64_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<uint16_t, uint8_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<uint16_t, uint16_t>::op<bool>(is_compatible);
            is_compatible_op_t::make<uint16_t, uint32_t>::op<bool>(is_compatible);
            is_compatible_op_t::make<uint16_t, uint64_t>::op<bool>(is_compatible);
            is_compatible_op_t::make<uint16_t, float   >::op<bool>(is_compatible);
            is_compatible_op_t::make<uint16_t, double  >::op<bool>(is_compatible);

            is_compatible_op_t::make<int32_t, bool    >::op<bool>(is_compatible);
            is_compatible_op_t::make<int32_t, char    >::op<bool>(is_compatible);
            is_compatible_op_t::make<int32_t, wchar_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<int32_t, int8_t  >::op<bool>(is_compatible);
            is_compatible_op_t::make<int32_t, int16_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<int32_t, int32_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<int32_t, int64_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<int32_t, uint8_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<int32_t, uint16_t>::op<bool>(is_compatible);
            is_compatible_op_t::make<int32_t, uint32_t>::op<bool>(is_compatible);
            is_compatible_op_t::make<int32_t, uint64_t>::op<bool>(is_compatible);
            is_compatible_op_t::make<int32_t, float   >::op<bool>(is_compatible);
            is_compatible_op_t::make<int32_t, double  >::op<bool>(is_compatible);

            is_compatible_op_t::make<uint32_t, bool    >::op<bool>(is_compatible);
            is_compatible_op_t::make<uint32_t, char    >::op<bool>(is_compatible);
            is_compatible_op_t::make<uint32_t, wchar_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<uint32_t, int8_t  >::op<bool>(is_compatible);
            is_compatible_op_t::make<uint32_t, int16_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<uint32_t, int32_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<uint32_t, int64_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<uint32_t, uint8_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<uint32_t, uint16_t>::op<bool>(is_compatible);
            is_compatible_op_t::make<uint32_t, uint32_t>::op<bool>(is_compatible);
            is_compatible_op_t::make<uint32_t, uint64_t>::op<bool>(is_compatible);
            is_compatible_op_t::make<uint32_t, float   >::op<bool>(is_compatible);
            is_compatible_op_t::make<uint32_t, double  >::op<bool>(is_compatible);

            is_compatible_op_t::make<int64_t, bool    >::op<bool>(is_compatible);
            is_compatible_op_t::make<int64_t, char    >::op<bool>(is_compatible);
            is_compatible_op_t::make<int64_t, wchar_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<int64_t, int8_t  >::op<bool>(is_compatible);
            is_compatible_op_t::make<int64_t, int16_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<int64_t, int32_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<int64_t, int64_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<int64_t, uint8_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<int64_t, uint16_t>::op<bool>(is_compatible);
            is_compatible_op_t::make<int64_t, uint32_t>::op<bool>(is_compatible);
            is_compatible_op_t::make<int64_t, uint64_t>::op<bool>(is_compatible);
            is_compatible_op_t::make<int64_t, float   >::op<bool>(is_compatible);
            is_compatible_op_t::make<int64_t, double  >::op<bool>(is_compatible);

            is_compatible_op_t::make<uint64_t, bool    >::op<bool>(is_compatible);
            is_compatible_op_t::make<uint64_t, char    >::op<bool>(is_compatible);
            is_compatible_op_t::make<uint64_t, wchar_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<uint64_t, int8_t  >::op<bool>(is_compatible);
            is_compatible_op_t::make<uint64_t, int16_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<uint64_t, int32_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<uint64_t, int64_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<uint64_t, uint8_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<uint64_t, uint16_t>::op<bool>(is_compatible);
            is_compatible_op_t::make<uint64_t, uint32_t>::op<bool>(is_compatible);
            is_compatible_op_t::make<uint64_t, uint64_t>::op<bool>(is_compatible);
            is_compatible_op_t::make<uint64_t, float   >::op<bool>(is_compatible);
            is_compatible_op_t::make<uint64_t, double  >::op<bool>(is_compatible);

            is_compatible_op_t::make<bool, bool    >::op<bool>(is_compatible);
            is_compatible_op_t::make<bool, char    >::op<bool>(is_compatible);
            is_compatible_op_t::make<bool, wchar_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<bool, int8_t  >::op<bool>(is_compatible);
            is_compatible_op_t::make<bool, int16_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<bool, int32_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<bool, int64_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<bool, uint8_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<bool, uint16_t>::op<bool>(is_compatible);
            is_compatible_op_t::make<bool, uint32_t>::op<bool>(is_compatible);
            is_compatible_op_t::make<bool, uint64_t>::op<bool>(is_compatible);
            is_compatible_op_t::make<bool, float   >::op<bool>(is_compatible);
            is_compatible_op_t::make<bool, double  >::op<bool>(is_compatible);
            is_compatible_op_t::make<bool, text_t  >::op<bool>(is_compatible);

            is_compatible_op_t::make<float, bool    >::op<bool>(is_compatible);
            is_compatible_op_t::make<float, char    >::op<bool>(is_compatible);
            is_compatible_op_t::make<float, wchar_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<float, int8_t  >::op<bool>(is_compatible);
            is_compatible_op_t::make<float, int16_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<float, int32_t >::op<bool>(is_compatible); // Note: cheating a bit since float only have 23-bit mantissa...
            is_compatible_op_t::make<float, int64_t >::op<bool>(is_compatible); // Note: cheating a lot since float only have 23-bit mantissa...
            is_compatible_op_t::make<float, uint8_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<float, uint16_t>::op<bool>(is_compatible);
            is_compatible_op_t::make<float, uint32_t>::op<bool>(is_compatible); // Note: cheating a bit since float only have 23-bit mantissa...
            is_compatible_op_t::make<float, uint64_t>::op<bool>(is_compatible); // Note: cheating a lot since float only have 23-bit mantissa...
            is_compatible_op_t::make<float, float   >::op<bool>(is_compatible);
            is_compatible_op_t::make<float, double  >::op<bool>(is_compatible);

            is_compatible_op_t::make<double, bool    >::op<bool>(is_compatible);
            is_compatible_op_t::make<double, char    >::op<bool>(is_compatible);
            is_compatible_op_t::make<double, wchar_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<double, int8_t  >::op<bool>(is_compatible);
            is_compatible_op_t::make<double, int16_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<double, int32_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<double, int64_t >::op<bool>(is_compatible); // Note: cheating a bit since double only have 52-bit mantissa...
            is_compatible_op_t::make<double, uint8_t >::op<bool>(is_compatible);
            is_compatible_op_t::make<double, uint16_t>::op<bool>(is_compatible);
            is_compatible_op_t::make<double, uint32_t>::op<bool>(is_compatible);
            is_compatible_op_t::make<double, uint64_t>::op<bool>(is_compatible); // Note: cheating a bit since double only have 52-bit mantissa...
            is_compatible_op_t::make<double, float   >::op<bool>(is_compatible);
            is_compatible_op_t::make<double, double  >::op<bool>(is_compatible);

            is_compatible_op_t::make<text_t, text_t   >::op<bool>(is_compatible);
            is_compatible_op_t::make<text_t, str_ptr_t>::op<bool>(is_compatible);
         }
      };

      is_compatible_op_init_t is_compatible_op_init;
   }

   void is_compatible_op_t::register_ops()
   {
      // Needed so that the global operations are initialized in the tests.
      // All that is needed is to enter this file to create the globals.
   }

   bool is_compatible(const type_info_t& to_type, const type_info_t& from_type)
   {
      if (to_type == from_type)
         return true;

      any_t result = is_compatible_op_t::call_any_with_types<void, void>::op(to_type, from_type);
      if (!result.has_value())
         return false;

      return std::any_cast<bool>(result);
   }
}
