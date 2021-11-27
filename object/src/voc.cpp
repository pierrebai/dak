#include <dak/object/voc.h>
#include <dak/object/namespace.h>

namespace dak::object::voc
{
   // The anonymous global namespace.

   edit_ref_t<namespace_t>& get_namespace()
   {
      static edit_ref_t<namespace_t> anon_ns = namespace_t::make();
      return anon_ns;
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // The types of names is kept in its own namespace to avoid contaminating
   // the outer namespaces with common words.

   #define DAK_OBJECT_VOC_MAKE_NAME(n) const name_t n(get_namespace(), L ## #n)

   #include "dak/object/voc_internal.h"

   #undef DAK_OBJECT_VOC_MAKE_NAME
}
