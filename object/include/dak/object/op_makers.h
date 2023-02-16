#pragma once

#ifndef DAK_OBJECT_OP_MAKERS_H
#define DAK_OBJECT_OP_MAKERS_H

#include <dak/any_op/op_makers.h>
#include <dak/object/make_op.h>
#include <dak/object/edit_ref.h>


//////////////////////////////////////////////////////////////////////////
//
// With T a type and B a base for that type (B can be the type itself)
//
// Declare for a ref-counted type all ops for its references:
//    - compatibility of refs to refs of the base class.
//    - compatibility of stronger refs of the base class to weaker refs.
//    - conversion of refs to refs of the base class.
//    - conversion of stronger refs of the base class to weaker refs.

#define DAK_OBJECT_REF_OP_MAKERS(T, B)                                        \
   dak::any_op::is_compatible_op_t::                                          \
      make<dak::object::ref_t<B>, dak::object::ref_t<T>>::                    \
      op<bool>(dak::any_op::details::yes);                                    \
   dak::any_op::is_compatible_op_t::                                          \
      make<dak::object::weak_ref_t<B>, dak::object::weak_ref_t<T>>::          \
      op<bool>(dak::any_op::details::yes);                                    \
   dak::any_op::is_compatible_op_t::                                          \
      make<dak::object::edit_ref_t<B>, dak::object::edit_ref_t<T>>::          \
      op<bool>(dak::any_op::details::yes);                                    \
   dak::any_op::is_compatible_op_t::                                          \
      make<dak::object::valid_ref_t<B>, dak::object::valid_ref_t<T>>::        \
      op<bool>(dak::any_op::details::yes);                                    \
                                                                              \
   dak::any_op::is_compatible_op_t::                                          \
      make<dak::object::ref_t<B>, dak::object::weak_ref_t<T>>::               \
      op<bool>(dak::any_op::details::yes);                                    \
   dak::any_op::is_compatible_op_t::                                          \
      make<dak::object::ref_t<B>, dak::object::edit_ref_t<T>>::               \
      op<bool>(dak::any_op::details::yes);                                    \
   dak::any_op::is_compatible_op_t::                                          \
      make<dak::object::ref_t<B>, dak::object::valid_ref_t<T>>::              \
      op<bool>(dak::any_op::details::yes);                                    \
   dak::any_op::is_compatible_op_t::                                          \
      make<dak::object::valid_ref_t<B>, dak::object::edit_ref_t<T>>::         \
      op<bool>(dak::any_op::details::yes);                                    \
   dak::any_op::is_compatible_op_t::                                          \
      make<dak::object::weak_ref_t<B>, dak::object::ref_t<T>>::               \
      op<bool>(dak::any_op::details::yes);                                    \
   dak::any_op::is_compatible_op_t::                                          \
      make<dak::object::weak_ref_t<B>, dak::object::edit_ref_t<T>>::          \
      op<bool>(dak::any_op::details::yes);                                    \
   dak::any_op::is_compatible_op_t::                                          \
      make<dak::object::weak_ref_t<B>, dak::object::valid_ref_t<T>>::         \
      op<bool>(dak::any_op::details::yes);                                    \
                                                                              \
   dak::any_op::convert_op_t::                                                \
      make<dak::object::ref_t<B>>::                                           \
      op<dak::object::ref_t<B>, dak::object::ref_t<T>>(                       \
      [](const dak::object::ref_t<T>& arg) -> dak::object::ref_t<B>           \
      { return dak::object::ref_t<B>(arg); });                                \
   dak::any_op::convert_op_t::                                                \
      make<dak::object::weak_ref_t<B>>::                                      \
      op<dak::object::weak_ref_t<B>, dak::object::weak_ref_t<T>>(             \
      [](const dak::object::weak_ref_t<T>& arg) -> dak::object::weak_ref_t<B> \
      { return dak::object::weak_ref_t<B>(arg); });                           \
   dak::any_op::convert_op_t::                                                \
      make<dak::object::edit_ref_t<B>>::                                      \
      op<dak::object::edit_ref_t<B>, dak::object::edit_ref_t<T>>(             \
      [](const dak::object::edit_ref_t<T>& arg) -> dak::object::edit_ref_t<B> \
      { return dak::object::edit_ref_t<B>(arg); });                           \
   dak::any_op::convert_op_t::                                                \
      make<dak::object::valid_ref_t<B>>::                                     \
      op<dak::object::valid_ref_t<B>, dak::object::valid_ref_t<T>>(           \
      [](const dak::object::valid_ref_t<T>& arg) -> dak::object::valid_ref_t<B> \
      { return dak::object::valid_ref_t<B>(arg); });                          \
                                                                              \
   dak::any_op::convert_op_t::                                                \
      make<dak::object::ref_t<B>>::                                           \
      op<dak::object::ref_t<B>, dak::object::weak_ref_t<T>>(                  \
      [](const dak::object::weak_ref_t<T>& arg) -> dak::object::ref_t<B>      \
      { return dak::object::ref_t<B>(arg); });                                \
   dak::any_op::convert_op_t::                                                \
      make<dak::object::ref_t<B>>::                                           \
      op<dak::object::ref_t<B>, dak::object::valid_ref_t<T>>(                 \
      [](const dak::object::valid_ref_t<T>& arg) -> dak::object::ref_t<B>     \
      { return dak::object::ref_t<B>(arg); });                                \
   dak::any_op::convert_op_t::                                                \
      make<dak::object::ref_t<B>>::                                           \
      op<dak::object::ref_t<B>, dak::object::edit_ref_t<T>>(                  \
      [](const dak::object::edit_ref_t<T>& arg) -> dak::object::ref_t<B>      \
      { return dak::object::ref_t<B>(arg); });                                \
   dak::any_op::convert_op_t::                                                \
      make<dak::object::valid_ref_t<B>>::                                     \
      op<dak::object::valid_ref_t<B>, dak::object::edit_ref_t<T>>(            \
      [](const dak::object::edit_ref_t<T>& arg) -> dak::object::valid_ref_t<B>\
      { return dak::object::valid_ref_t<B>(arg); });                          \
   dak::any_op::convert_op_t::                                                \
      make<dak::object::weak_ref_t<B>>::                                      \
      op<dak::object::weak_ref_t<B>, dak::object::ref_t<T>>(                  \
      [](const dak::object::ref_t<T>& arg) -> dak::object::weak_ref_t<B>      \
      { return arg; });                                                       \
   dak::any_op::convert_op_t::                                                \
      make<dak::object::weak_ref_t<B>>::                                      \
      op<dak::object::weak_ref_t<B>, dak::object::valid_ref_t<T>>(            \
      [](const dak::object::valid_ref_t<T>& arg) -> dak::object::weak_ref_t<B>\
      { return arg; });                                                       \
   dak::any_op::convert_op_t::                                                \
      make<dak::object::weak_ref_t<B>>::                                      \
      op<dak::object::weak_ref_t<B>, dak::object::edit_ref_t<T>>(             \
      [](const dak::object::edit_ref_t<T>& arg) -> dak::object::weak_ref_t<B> \
      { return arg; })


//////////////////////////////////////////////////////////////////////////
//
// Declare for a ref-counted type all ops for:
//    - making a default-constructed ref-counted instance.
//    - ops for the references to the type

#define DAK_OBJECT_OP_MAKERS(T)                                               \
   dak::object::make_op_t::make<T>::op<dak::object::ref_t<T>>(                \
      (std::function<dak::object::ref_t<T>()>)                                \
      []() -> dak::object::ref_t<T> { return T::make(); });                   \
                                                                              \
   DAK_OBJECT_REF_OP_MAKERS(T, T);                                            \
                                                                              \
   DAK_ANY_OP_TYPE_MAKERS(dak::object::ref_t<T>);                             \
   DAK_ANY_OP_TYPE_MAKERS(dak::object::valid_ref_t<T>);                       \
   DAK_ANY_OP_TYPE_MAKERS(dak::object::edit_ref_t<T>);                        \
   DAK_ANY_OP_TYPE_MAKERS(dak::object::weak_ref_t<T>)


#endif /* DAK_OBJECT_OP_MAKERS_H */
