#include <dak/any_op/stream_op.h>

namespace dak::any_op
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Write to an input text stream.

   namespace
   {
      // Note: for some reason, Visual-Studio 2019 in C++ 2020 mode cannot
      //       deduce the N_ARY variadic template argument in the calls
      //       to ::op below when we pass the lambda directly,
      //
      //       It also fails if we replace the lambda with a real function
      //       taking no argument.
      //
      //       It only works when we pass an explicit std::function.
      //       The problem only manistfest itself for the nullary
      //       op_t. It seems the complete absence of type in a nullary
      //       function fails to be automatically deduced as an empty
      //       N_ARY variadic template...
      struct stream_op_init_t
      {
         stream_op_init_t()
         {
            // Note: we do *not* register op for str_ptr_t nor char:
            //          - str_ptr_t cannot be written to.
            //          - Trying toread a single char from a wide input stream is doomed to failure.

            istream_op_t::make<bool    >::op<bool    >((std::function<bool    (std::wistream&)>)[](std::wistream& a_stream) -> bool     { bool     value; a_stream >> value; return value; });
            istream_op_t::make<wchar_t >::op<wchar_t >((std::function<wchar_t (std::wistream&)>)[](std::wistream& a_stream) -> wchar_t  { wchar_t  value; a_stream >> value; return value; });
            istream_op_t::make<int8_t  >::op<int8_t  >((std::function<int8_t  (std::wistream&)>)[](std::wistream& a_stream) -> int8_t   { int8_t   value; int16_t tmp; a_stream >> tmp; value = int8_t(tmp); return value; });
            istream_op_t::make<int16_t >::op<int16_t >((std::function<int16_t (std::wistream&)>)[](std::wistream& a_stream) -> int16_t  { int16_t  value; a_stream >> value; return value; });
            istream_op_t::make<int32_t >::op<int32_t >((std::function<int32_t (std::wistream&)>)[](std::wistream& a_stream) -> int32_t  { int32_t  value; a_stream >> value; return value; });
            istream_op_t::make<int64_t >::op<int64_t >((std::function<int64_t (std::wistream&)>)[](std::wistream& a_stream) -> int64_t  { int64_t  value; a_stream >> value; return value; });
            istream_op_t::make<uint8_t >::op<uint8_t >((std::function<uint8_t (std::wistream&)>)[](std::wistream& a_stream) -> uint8_t  { uint8_t  value; uint16_t tmp; a_stream >> tmp; value = uint8_t(tmp); return value; });
            istream_op_t::make<uint16_t>::op<uint16_t>((std::function<uint16_t(std::wistream&)>)[](std::wistream& a_stream) -> uint16_t { uint16_t value; a_stream >> value; return value; });
            istream_op_t::make<uint32_t>::op<uint32_t>((std::function<uint32_t(std::wistream&)>)[](std::wistream& a_stream) -> uint32_t { uint32_t value; a_stream >> value; return value; });
            istream_op_t::make<uint64_t>::op<uint64_t>((std::function<uint64_t(std::wistream&)>)[](std::wistream& a_stream) -> uint64_t { uint64_t value; a_stream >> value; return value; });
            istream_op_t::make<float   >::op<float   >((std::function<float   (std::wistream&)>)[](std::wistream& a_stream) -> float    { float    value; a_stream >> value; return value; });
            istream_op_t::make<double  >::op<double  >((std::function<double  (std::wistream&)>)[](std::wistream& a_stream) -> double   { double   value; a_stream >> value; return value; });
            istream_op_t::make<text_t  >::op<text_t  >((std::function<text_t  (std::wistream&)>)[](std::wistream& a_stream) -> text_t   { text_t   value; a_stream >> value; return value; });
         }
      };

      stream_op_init_t stream_op_init;
   }

   std::wistream& operator>>(std::wistream& a_stream, any_t& a_value)
   {
      return stream(a_stream, a_value);
   }

   void istream_op_t::register_ops()
   {
      // Needed so that the global operations are initialized in the tests.
      // All that is needed is to enter this file to create the globals.
   }
}
