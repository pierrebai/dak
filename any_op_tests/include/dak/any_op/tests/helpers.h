#pragma once

#ifndef DAK_ANY_TESTS_HELPERS_H
#define DAK_ANY_TESTS_HELPERS_H

#include <CppUnitTest.h>

#include <any>
#include <typeinfo>

namespace Microsoft::VisualStudio::CppUnitTestFramework
{
   template<> inline std::wstring ToString<dak::utility::type_info_t>(const dak::utility::type_info_t& an_info)
   {
      RETURN_WIDE_STRING(an_info.name());
   }

   template<> inline std::wstring ToString<std::vector<const dak::utility::type_info_t*>>(const std::vector<const dak::utility::type_info_t*>& some_info)
   {
      std::string result;
      for (const auto info : some_info)
         result += info->name();
      RETURN_WIDE_STRING(result.c_str());
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

}

#endif /* DAK_ANY_TESTS_HELPERS_H */
