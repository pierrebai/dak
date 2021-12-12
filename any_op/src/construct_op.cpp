#include <dak/any_op/construct_op.h>

namespace dak::any_op
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Create a value.

   namespace
   {
      struct construct_op_init_t
      {
         construct_op_init_t()
         {
            construct_op_t::make<bool    >::op<bool    >((std::function<bool    ()>)[]() -> bool     { return false;       });
            construct_op_t::make<char    >::op<char    >((std::function<char    ()>)[]() -> char     { return char    (0); });
            construct_op_t::make<wchar_t >::op<wchar_t >((std::function<wchar_t ()>)[]() -> wchar_t  { return wchar_t (0); });
            construct_op_t::make<int8_t  >::op<int8_t  >((std::function<int8_t  ()>)[]() -> int8_t   { return int8_t  (0); });
            construct_op_t::make<uint8_t >::op<uint8_t >((std::function<uint8_t ()>)[]() -> uint8_t  { return uint8_t (0); });
            construct_op_t::make<int16_t >::op<int16_t >((std::function<int16_t ()>)[]() -> int16_t  { return int16_t (0); });
            construct_op_t::make<uint16_t>::op<uint16_t>((std::function<uint16_t()>)[]() -> uint16_t { return uint16_t(0); });
            construct_op_t::make<int32_t >::op<int32_t >((std::function<int32_t ()>)[]() -> int32_t  { return int32_t (0); });
            construct_op_t::make<uint32_t>::op<uint32_t>((std::function<uint32_t()>)[]() -> uint32_t { return uint32_t(0); });
            construct_op_t::make<int64_t >::op<int64_t >((std::function<int64_t ()>)[]() -> int64_t  { return int64_t (0); });
            construct_op_t::make<uint64_t>::op<uint64_t>((std::function<uint64_t()>)[]() -> uint64_t { return uint64_t(0); });
            construct_op_t::make<float   >::op<float   >((std::function<float   ()>)[]() -> float    { return float   (0); });
            construct_op_t::make<double  >::op<double  >((std::function<double  ()>)[]() -> double   { return double  (0); });
            construct_op_t::make<text_t  >::op<text_t  >((std::function<text_t  ()>)[]() -> text_t   { return text_t  ( ); });
         }
      };

      construct_op_init_t construct_op_init;
   }

   void construct_op_t::register_ops()
   {
      // Needed so that the global operations are initialized in the tests.
      // All that is needed is to enter this file to create the globals.
   }
}
