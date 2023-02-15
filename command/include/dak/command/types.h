#pragma once

#ifndef DAK_COMMAND_TYPES_H
#define DAK_COMMAND_TYPES_H

#include <dak/object/types.h>

namespace dak::command
{
   USING_DAK_OBJECT_TYPES;

   struct command_t;
   struct command_tree_t;
}

#define USING_DAK_COMMAND_TYPES           \
   USING_DAK_OBJECT_TYPES;                \
   using dak::command::command_t;         \
   using dak::object::command_tree_t

#endif /* DAK_COMMAND_TYPES_H */
