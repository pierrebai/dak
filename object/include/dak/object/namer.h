#pragma once

#ifndef DAK_OBJECT_NAMER_H
#define DAK_OBJECT_NAMER_H

#include <dak/object/name.h>

#include <map>

namespace dak::object
{
   //////////////////////////////////////////////////////////////////////////
   //
   // Lookup table for names based on some roots.
   //
   // Translates a given name to its text_t equivalent.

   struct namer_t
   {
      // Constructors.
      namer_t();
      namer_t(const name_t& root);

      // Add another root.
      void add_root(const name_t& root);

      // Reverse lookup of a name.
      text_t find(const name_t&) const;

   private:
      void add_subs(const text_t& t, const name_t& n);

      typedef std::map<name_t, text_t> names_t;
      typedef std::map<name_t, name_t> parents_t;

      names_t    my_names;
      parents_t  my_parents;
   };
}

#endif /* DAK_OBJECT_NAMER_H */
