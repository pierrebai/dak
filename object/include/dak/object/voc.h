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
   // This vocabulary is kept in an anonymous namespace that you can retrieve
   // by calling the get_namespace function declared below.
   //
   // The vocabulary is kept here, in a C++ namespace to avoid conflicting
   // with other variables or types using the same words.

   edit_ref_t<namespace_t>& get_namespace();

   #define DAK_OBJECT_VOC_MAKE_NAME(n) extern const name_t n
   #define DAK_OBJECT_VOC_MAKE_SHORTHAND(n, s) extern const name_t n

   #include <dak/object/voc_internal.h>

   #undef DAK_OBJECT_VOC_MAKE_NAME
   #undef DAK_OBJECT_VOC_MAKE_SHORTHAND
}

#endif /* DAK_OBJECT_VOC_H */
