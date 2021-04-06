#include "dak/object/namer.h"
#include "dak/object/name.h"

namespace dak::object
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Constructors.

   namer_t::namer_t()
      : my_names()
   {
   }

   namer_t::namer_t(const name_t& root)
      : my_names()
   {
      add_root(root);
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Add another root.

   void namer_t::add_root(const name_t& root)
   {
      add_subs(L"", root);
   }

   void namer_t::add_subs(const text_t& t, const name_t& n)
   {
      typedef name_t::const_iterator iter;
      const iter end = n.end();
      for (iter pos = n.begin(); pos != end; ++pos)
      {
         my_names[pos->second] = pos->first;
         my_parents[pos->second] = n;
         add_subs(pos->first, pos->second);
      }
   }

   //////////////////////////////////////////////////////////////////////////
   //
   // Reverse lookup of a name_t.

   text_t namer_t::find(const name_t& n) const
   {
      text_t t;

      const auto p_end = my_parents.end();
      const auto n_end = my_names.end();
      name_t tn = n;
      while (true)
      {
         const auto pos = my_names.find(tn);
         if (pos == n_end)
            return t;
         else if (t.empty())
            t = pos->second;
         else
            t = pos->second + text_t(L"/") + t;
         auto parent = my_parents.find(tn);
         if (parent == p_end)
            return t;
         else
            tn = parent->second;
      }
   }
}
