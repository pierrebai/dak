#pragma once

#ifndef DAK_OBJECT_TYPES_H
#define DAK_OBJECT_TYPES_H

#include <dak/utility/types.h>
#include <dak/object/valid_ref.h>

namespace dak::object
{
   USING_DAK_UTILITY_TYPES;

   struct array_t;
   struct dict_t;
   struct exact_name_t;
   struct make_op_t;
   struct name_t;
   struct namespace_t;
   struct object_t;
   struct ref_base_t;
   struct ref_counted_t;
   struct strong_ref_base_t;
   struct timeline_t;
   struct transaction_t;
   struct transaction_item_t;
   struct value_t;
   struct visited_refs_t;
   struct weak_ref_base_t;

}

#define USING_DAK_OBJECT_TYPES            \
   USING_DAK_UTILITY_TYPES;               \
   using dak::object::array_t;            \
   using dak::object::type_info_t;        \
   using dak::object::dict_t;             \
   using dak::object::edit_ref_t;         \
   using dak::object::exact_name_t;       \
   using dak::object::make_op_t;          \
   using dak::object::name_t;             \
   using dak::object::namespace_t;        \
   using dak::object::object_t;           \
   using dak::object::ref_t;              \
   using dak::object::ref_base_t;         \
   using dak::object::ref_counted_t;      \
   using dak::object::strong_ref_base_t;  \
   using dak::object::timeline_t;         \
   using dak::object::transaction_t;      \
   using dak::object::transaction_item_t; \
   using dak::object::valid_ref_t;        \
   using dak::object::value_t;            \
   using dak::object::visited_refs_t;     \
   using dak::object::weak_ref_t;         \
   using dak::object::weak_ref_base_t

#endif /* DAK_OBJECT_TYPES_H */
