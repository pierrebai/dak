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

   template<> inline std::wstring ToString<std::any>(const std::any& a_var)
   {
      using namespace dak::any_op;
      RETURN_WIDE_STRING(a_var);
   }

}

#endif /* DAK_ANY_TESTS_HELPERS_H */
