#pragma once

#ifndef DAK_ANY_OP_MAKERS_H
#define DAK_ANY_OP_MAKERS_H

#include <dak/any_op/compare_op.h>
#include <dak/any_op/convert_op.h>
#include <dak/any_op/get_type_info_op.h>
#include <dak/any_op/get_type_name_op.h>
#include <dak/any_op/is_compatible_op.h>
#include <dak/any_op/construct_op.h>
#include <dak/any_op/size_op.h>
#include <dak/any_op/stream_op.h>
#include <dak/any_op/to_text_op.h>

namespace dak::any_op
{
   namespace details
   {
      extern const std::function<bool()> yes;
   }
}

#define DAK_ANY_OP_TYPE_MAKERS(T)                                                               \
   dak::any_op::get_type_name_op_t::make<T>::op<text_t>((std::function<text_t()>)               \
      []() -> text_t { return L ## # T; });                                                       \
   dak::any_op::add_type_info( L ## # T, typeid(T))

#define DAK_ANY_OP_MAKERS(T)                                                                    \
   DAK_ANY_OP_TYPE_MAKERS(T);                                                                   \
   dak::any_op::construct_op_t::make<T>::op<T>((std::function<T()>)[]() -> T { return T(); });  \
   dak::any_op::is_compatible_op_t::make<T, T>::op<bool>(dak::any_op::details::yes);            \
   dak::any_op::convert_op_t::make<T>::op<T, T>([](const T& arg) -> T { return arg; });         \
   dak::any_op::convert_op_t::make<bool>::op<bool, T>(                                          \
      [](const T& arg) -> bool { return to_bool(arg); })

   //dak::any_op::to_text_op_t::make<>::op<text_t>((std::function<text_t()>)                      \
   //   [](const T& arg) -> text_t { return to_text(arg); });                                     \
   //dak::any_op::ostream_op_t::make<>::op<bool, T>(                                              \
   //   [](std::wostream& a_stream, const T& arg) -> bool { a_stream << arg; return true; })

#define DAK_ANY_OP_COMPARABLE_MAKERS(T)                                                         \
      DAK_ANY_OP_MAKERS(T);                                                                     \
      dak::any_op::compare_op_t::make<>::op<dak::any_op::comparison_t, T, T>(                   \
         [](const T& arg_a, const T& arg_b) -> dak::any_op::comparison_t                        \
         {                                                                                      \
            if (arg_a < arg_b)                                                                  \
               return comparison_t::less;                                                       \
            if (arg_a > arg_b)                                                                  \
               return comparison_t::more;                                                       \
            return comparison_t::equal;                                                         \
         })

#endif /* DAK_ANY_OP_MAKERS_H */
