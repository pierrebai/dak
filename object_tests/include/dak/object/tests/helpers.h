#pragma once

#ifndef DAK_OBJECT_TESTS_HELPERS_H
#define DAK_OBJECT_TESTS_HELPERS_H

#include "CppUnitTest.h"

#include "dak/object/array.h"
#include "dak/object/dict.h"
#include "dak/object/name.h"
#include "dak/object/object.h"
#include "dak/object/ref_stream.h"
#include "dak/object/voc.h"

namespace Microsoft::VisualStudio::CppUnitTestFramework
{
   #define RETURN_REF_STREAM_WIDE_STRING(x) std::wstringstream ss; dak::object::ref_ostream_t(ss) << x; return ss.str()

   template<> inline std::wstring ToString<dak::object::name_t>(const dak::object::name_t& n)
   {
      RETURN_WIDE_STRING(n.to_text());
   }

   template<> inline std::wstring ToString<dak::object::dict_t>(const dak::object::dict_t& d);
   template<> inline std::wstring ToString<dak::object::array_t>(const dak::object::array_t& a);

   template<> inline std::wstring ToString<dak::object::element_t>(const dak::object::element_t& e)
   {
      RETURN_REF_STREAM_WIDE_STRING(e);
   }

   template<> inline std::wstring ToString<dak::object::valid_ref_t<dak::object::object_t>>(const dak::object::valid_ref_t<dak::object::object_t>& o)
   {
      RETURN_REF_STREAM_WIDE_STRING(*o);
   }

   template<> inline std::wstring ToString<dak::object::object_t>(const dak::object::object_t& o)
   {
      RETURN_REF_STREAM_WIDE_STRING(o);
   }

   template<> inline std::wstring ToString<dak::utility::uint16_t>(const dak::utility::uint16_t& e)
   {
      RETURN_WIDE_STRING(dak::utility::uint32_t(e));
   }

   template<> inline std::wstring ToString<dak::object::array_t>(const dak::object::array_t& a)
   {
      RETURN_REF_STREAM_WIDE_STRING(a);
   }

   template<> inline std::wstring ToString<dak::object::dict_t>(const dak::object::dict_t& d)
   {
      RETURN_REF_STREAM_WIDE_STRING(d);
   }

   template<> inline std::wstring ToString<dak::object::datatype_t>(const dak::object::datatype_t& d)
   {
      RETURN_WIDE_STRING(static_cast<int>(d));
   }

}

#endif /* DAK_OBJECT_TESTS_HELPERS_H */
