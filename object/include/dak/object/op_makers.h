#pragma once

#ifndef DAK_OBJECT_OP_MAKERS_H
#define DAK_OBJECT_OP_MAKERS_H

#include <dak/any_op/op_makers.h>
#include <dak/object/make_op.h>
#include <dak/object/edit_ref.h>

#define DAK_OBJECT_OP_MAKERS(T)                                               \
   dak::object::make_op_t::make<T>::op<dak::object::ref_t<T>>(                \
      (std::function<dak::object::ref_t<T>()>)                                \
      []() -> dak::object::ref_t<T> { return T::make(); });                   \
   dak::any_op::convert_op_t::                                                \
      make<dak::object::ref_t<T>>::                                           \
      op<dak::object::ref_t<T>, dak::object::weak_ref_t<T>>(                  \
      [](const dak::object::weak_ref_t<T>& arg) -> dak::object::ref_t<T>      \
      { return dak::object::ref_t<T>(arg); });                                \
   dak::any_op::convert_op_t::                                                \
      make<dak::object::ref_t<T>>::                                           \
      op<dak::object::ref_t<T>, dak::object::valid_ref_t<T>>(                 \
      [](const dak::object::valid_ref_t<T>& arg) -> dak::object::ref_t<T>     \
      { return dak::object::ref_t<T>(arg); });                                \
   dak::any_op::convert_op_t::                                                \
      make<dak::object::ref_t<T>>::                                           \
      op<dak::object::ref_t<T>, dak::object::edit_ref_t<T>>(                  \
      [](const dak::object::edit_ref_t<T>& arg) -> dak::object::ref_t<T>      \
      { return dak::object::ref_t<T>(arg); });                                \
   dak::any_op::convert_op_t::                                                \
      make<dak::object::valid_ref_t<T>>::                                     \
      op<dak::object::valid_ref_t<T>, dak::object::edit_ref_t<T>>(            \
      [](const dak::object::edit_ref_t<T>& arg) -> dak::object::valid_ref_t<T>\
      { return dak::object::valid_ref_t<T>(arg); });                          \
   dak::any_op::convert_op_t::                                                \
      make<dak::object::weak_ref_t<T>>::                                      \
      op<dak::object::weak_ref_t<T>, dak::object::ref_t<T>>(                  \
      [](const dak::object::ref_t<T>& arg) -> dak::object::weak_ref_t<T>      \
      { return arg; });                                                       \
   dak::any_op::convert_op_t::                                                \
      make<dak::object::weak_ref_t<T>>::                                      \
      op<dak::object::weak_ref_t<T>, dak::object::valid_ref_t<T>>(            \
      [](const dak::object::valid_ref_t<T>& arg) -> dak::object::weak_ref_t<T>\
      { return arg; });                                                       \
   dak::any_op::convert_op_t::                                                \
      make<dak::object::weak_ref_t<T>>::                                      \
      op<dak::object::weak_ref_t<T>, dak::object::edit_ref_t<T>>(             \
      [](const dak::object::edit_ref_t<T>& arg) -> dak::object::weak_ref_t<T> \
      { return arg; });                                                       \
   dak::any_op::is_compatible_op_t::                                          \
      make<dak::object::ref_t<T>, dak::object::weak_ref_t<T>>::               \
      op<bool>(dak::any_op::details::yes);                                    \
   dak::any_op::is_compatible_op_t::                                          \
      make<dak::object::ref_t<T>, dak::object::edit_ref_t<T>>::               \
      op<bool>(dak::any_op::details::yes);                                    \
   dak::any_op::is_compatible_op_t::                                          \
      make<dak::object::ref_t<T>, dak::object::valid_ref_t<T>>::              \
      op<bool>(dak::any_op::details::yes);                                    \
   dak::any_op::is_compatible_op_t::                                          \
      make<dak::object::valid_ref_t<T>, dak::object::edit_ref_t<T>>::         \
      op<bool>(dak::any_op::details::yes);                                    \
   dak::any_op::is_compatible_op_t::                                          \
      make<dak::object::weak_ref_t<T>, dak::object::ref_t<T>>::               \
      op<bool>(dak::any_op::details::yes);                                    \
   dak::any_op::is_compatible_op_t::                                          \
      make<dak::object::weak_ref_t<T>, dak::object::edit_ref_t<T>>::          \
      op<bool>(dak::any_op::details::yes);                                    \
   dak::any_op::is_compatible_op_t::                                          \
      make<dak::object::weak_ref_t<T>, dak::object::valid_ref_t<T>>::         \
      op<bool>(dak::any_op::details::yes);                                    \
   DAK_ANY_OP_TYPE_MAKERS(dak::object::ref_t<T>);                             \
   DAK_ANY_OP_TYPE_MAKERS(dak::object::valid_ref_t<T>);                       \
   DAK_ANY_OP_TYPE_MAKERS(dak::object::edit_ref_t<T>);                        \
   DAK_ANY_OP_TYPE_MAKERS(dak::object::weak_ref_t<T>)


#endif /* DAK_OBJECT_OP_MAKERS_H */
