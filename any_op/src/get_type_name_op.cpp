#include <dak/any_op/get_type_name_op.h>
#include <dak/any_op/get_type_info_op.h>

namespace dak::any_op
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Create a value.

   namespace
   {
      struct get_type_name_op_init_t
      {
         get_type_name_op_init_t()
         {
            get_type_name_op_t::make<bool    >::op<text_t>((std::function<text_t()>)[]() -> text_t { return L"bool"    ; });
            get_type_name_op_t::make<char    >::op<text_t>((std::function<text_t()>)[]() -> text_t { return L"char"    ; });
            get_type_name_op_t::make<wchar_t >::op<text_t>((std::function<text_t()>)[]() -> text_t { return L"wchar_t" ; });
            get_type_name_op_t::make<int8_t  >::op<text_t>((std::function<text_t()>)[]() -> text_t { return L"int8_t"  ; });
            get_type_name_op_t::make<uint8_t >::op<text_t>((std::function<text_t()>)[]() -> text_t { return L"uint8_t" ; });
            get_type_name_op_t::make<int16_t >::op<text_t>((std::function<text_t()>)[]() -> text_t { return L"int16_t" ; });
            get_type_name_op_t::make<uint16_t>::op<text_t>((std::function<text_t()>)[]() -> text_t { return L"uint16_t"; });
            get_type_name_op_t::make<int32_t >::op<text_t>((std::function<text_t()>)[]() -> text_t { return L"int32_t" ; });
            get_type_name_op_t::make<uint32_t>::op<text_t>((std::function<text_t()>)[]() -> text_t { return L"uint32_t"; });
            get_type_name_op_t::make<int64_t >::op<text_t>((std::function<text_t()>)[]() -> text_t { return L"int64_t" ; });
            get_type_name_op_t::make<uint64_t>::op<text_t>((std::function<text_t()>)[]() -> text_t { return L"uint64_t"; });
            get_type_name_op_t::make<float   >::op<text_t>((std::function<text_t()>)[]() -> text_t { return L"float"   ; });
            get_type_name_op_t::make<double  >::op<text_t>((std::function<text_t()>)[]() -> text_t { return L"double"  ; });
            get_type_name_op_t::make<text_t  >::op<text_t>((std::function<text_t()>)[]() -> text_t { return L"dak::utility::text_t"; });

            add_type_info(L"bool"    , typeid(bool));
            add_type_info(L"char"    , typeid(char));
            add_type_info(L"wchar_t" , typeid(wchar_t));
            add_type_info(L"int8_t"  , typeid(int8_t));
            add_type_info(L"uint8_t" , typeid(uint8_t));
            add_type_info(L"int16_t" , typeid(int16_t));
            add_type_info(L"uint16_t", typeid(uint16_t));
            add_type_info(L"int32_t" , typeid(int32_t));
            add_type_info(L"uint32_t", typeid(uint32_t));
            add_type_info(L"int64_t" , typeid(int64_t));
            add_type_info(L"uint64_t", typeid(uint64_t));
            add_type_info(L"float"   , typeid(float));
            add_type_info(L"double"  , typeid(double));

            add_type_info(L"dak::utility::text_t", typeid(text_t));
         }
      };

      get_type_name_op_init_t get_type_name_op_init;
   }

   void get_type_name_op_t::register_ops()
   {
      // Needed so that the global operations are initialized in the tests.
      // All that is needed is to enter this file to create the globals.
   }

   text_t get_type_name(const std::type_info& arg_a)
   {
      any_t result = get_type_name_op_t::call_extra_any<void>::op(arg_a);
      return as<text_t>(result);
   }

}
