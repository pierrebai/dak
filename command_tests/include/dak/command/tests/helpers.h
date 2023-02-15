#pragma once

#ifndef DAK_COMMAND_TESTS_HELPERS_H
#define DAK_COMMAND_TESTS_HELPERS_H

#include <CppUnitTest.h>

#include <dak/object/array.h>
#include <dak/object/dict.h>
#include <dak/object/name.h>
#include <dak/object/object.h>
#include <dak/object_io/ref_ostream_op.h>
#include <dak/object/voc.h>
#include <dak/any_op/stream_op.h>

namespace Microsoft::VisualStudio::CppUnitTestFramework
{
   #define RETURN_REF_STREAM_WIDE_STRING(x) std::wstringstream ss; dak::object::ref_ostream_t(ss) << x; return ss.str()

   template<> inline std::wstring ToString<dak::object::name_t>(const dak::object::name_t& n)
   {
      RETURN_WIDE_STRING(n.to_text());
   }

   template<> inline std::wstring ToString<dak::utility::any_t>(const dak::utility::any_t& a_var)
   {
      using namespace dak::any_op;
      RETURN_WIDE_STRING(a_var);
   }

   template<> inline std::wstring ToString<dak::object::dict_t>(const dak::object::dict_t& d);
   template<> inline std::wstring ToString<dak::object::array_t>(const dak::object::array_t& a);

   template<> inline std::wstring ToString<dak::object::value_t>(const dak::object::value_t& e)
   {
      RETURN_REF_STREAM_WIDE_STRING(e);
   }

   template<> inline std::wstring ToString<dak::object::valid_ref_t<dak::object::object_t>>(const dak::object::valid_ref_t<dak::object::object_t>& o)
   {
      RETURN_REF_STREAM_WIDE_STRING(*o);
   }

   template<> inline std::wstring ToString<dak::object::ref_t<dak::object::object_t>>(const dak::object::ref_t<dak::object::object_t>& o)
   {
      if (o.is_valid())
      {
         RETURN_REF_STREAM_WIDE_STRING(*dak::object::valid_ref_t<dak::object::object_t>(o));
      }
      else
      {
         RETURN_REF_STREAM_WIDE_STRING(0);
      }
   }

   template<> inline std::wstring ToString<dak::object::weak_ref_t<dak::object::object_t>>(const dak::object::weak_ref_t<dak::object::object_t>& o)
   {
      if (o.is_valid())
      {
         RETURN_REF_STREAM_WIDE_STRING(*dak::object::valid_ref_t<dak::object::object_t>(o));
      }
      else
      {
         RETURN_REF_STREAM_WIDE_STRING(0);
      }
   }

   template<> inline std::wstring ToString<dak::object::object_t>(const dak::object::object_t& o)
   {
      RETURN_REF_STREAM_WIDE_STRING(o);
   }

   template<> inline std::wstring ToString<dak::object::namespace_t>(const dak::object::namespace_t& ns)
   {
      RETURN_REF_STREAM_WIDE_STRING(ns);
   }

   template<> inline std::wstring ToString<dak::object::array_t>(const dak::object::array_t& a)
   {
      RETURN_REF_STREAM_WIDE_STRING(a);
   }

   template<> inline std::wstring ToString<dak::object::dict_t>(const dak::object::dict_t& d)
   {
      RETURN_REF_STREAM_WIDE_STRING(d);
   }

   template<> inline std::wstring ToString<const dak::object::datatype_t&>(const dak::object::datatype_t& d)
   {
      RETURN_WIDE_STRING(d.name());
   }

   template<> inline std::wstring ToString<std::type_info>(const std::type_info& d)
   {
      RETURN_WIDE_STRING(d.name());
   }

}

#endif /* DAK_COMMAND_TESTS_HELPERS_H */
