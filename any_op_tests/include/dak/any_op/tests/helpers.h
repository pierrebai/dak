#pragma once

#ifndef DAK_ANY_TESTS_HELPERS_H
#define DAK_ANY_TESTS_HELPERS_H

#include <CppUnitTest.h>

#include <any>
#include <typeinfo>

namespace Microsoft::VisualStudio::CppUnitTestFramework
{
   template<> inline std::wstring ToString<std::type_info>(const std::type_info& an_info)
   {
      RETURN_WIDE_STRING(an_info.name());
   }

   template<> inline std::wstring ToString<dak::utility::any_t>(const dak::utility::any_t& a_var)
   {
      using namespace dak::any_op;
      RETURN_WIDE_STRING(a_var);
   }

   template<> inline std::wstring ToString<dak::any_op::comparison_t>(const dak::any_op::comparison_t& a_cmp)
   {
      using namespace dak::any_op;
      RETURN_WIDE_STRING(a_cmp);
   }

   template<> inline std::wstring ToString<dak::utility::uint16_t>(const dak::utility::uint16_t& e)
   {
      RETURN_WIDE_STRING(dak::utility::uint32_t(e));
   }

}

#endif /* DAK_ANY_TESTS_HELPERS_H */
