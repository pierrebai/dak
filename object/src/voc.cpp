#include <dak/object/voc.h>

namespace dak::object::voc
{
   //////////////////////////////////////////////////////////////////////////
   //
   // The types of names is kept in its own namespace to avoid contaminating
   // the outer namespaces with common words.

   #define DAK_OBJECT_VOC_MAKE_NAME(n) const name_t n(L ## #n)

   #include "dak/object/voc_internal.h"

   #undef DAK_OBJECT_VOC_MAKE_NAME
}
