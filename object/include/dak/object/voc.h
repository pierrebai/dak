#pragma once

#ifndef DAK_OBJECT_VOC_H
#define DAK_OBJECT_VOC_H

#include <dak/object/name.h>

namespace dak::object::voc
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Create a vocabulary of names.
   // Given as an example of how to create names.
   //
   // The vocabulary is kept here, in a namespace to avoid conflicting
   // with other variables using the same words.
   //
   // The types of names is kept in its own namespace to avoid contaminating
   // the outer namespaces with common words.

   #define DAK_OBJECT_VOC_MAKE_NAME(n) extern const name_t n

   #include "dak/object/voc_internal.h"

   #undef DAK_OBJECT_VOC_MAKE_NAME
}

#endif /* DAK_OBJECT_VOC_H */
