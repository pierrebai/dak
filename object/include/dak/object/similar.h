#pragma once

#ifndef DAK_OBJECT_SIMILAR_H
#define DAK_OBJECT_SIMILAR_H

#include <dak/object/valid_ref.h>

#include <set>
#include <algorithm>

namespace dak::object
{
   struct array_t;
   struct dict_t;
   struct value_t;
   struct object_t;

   //////////////////////////////////////////////////////////////////////////
   //
   // Compare overall structure, traversing references and comparing the
   // objects contents recursively.
   //
   // Pairs of references already compared must be tracked to avoid infinite
   // recursion when objects end-up referring back to themselves directly or
   // indirectly.
   //
   // That tracking is done by a visited-refs container, declared below.

   struct visited_refs_t
   {
      using ref_pair_t  = std::pair<valid_ref_t<object_t>, valid_ref_t<object_t>>;
      using ref_pairs_t = std::set<ref_pair_t>;

      mutable ref_pairs_t visited;
   };

   bool are_similar(const array_t&   a, const array_t&   b, const visited_refs_t& visited = visited_refs_t());
   bool are_similar(const dict_t&    a, const dict_t&    b, const visited_refs_t& visited = visited_refs_t());
   bool are_similar(const any_t&     a, const any_t&     b, const visited_refs_t& visited = visited_refs_t());
   bool are_similar(const value_t& a, const value_t& b, const visited_refs_t& visited = visited_refs_t());
   bool are_similar(const object_t&  a, const object_t&  b, const visited_refs_t& visited = visited_refs_t());
   bool are_similar(const valid_ref_t<object_t>& a, const valid_ref_t<object_t>& b, const visited_refs_t& visited = visited_refs_t());
   bool are_similar(const weak_ref_t<object_t>& a, const weak_ref_t<object_t>& b, const visited_refs_t& visited = visited_refs_t());
}

#endif /* DAK_OBJECT_SIMILAR_H */
