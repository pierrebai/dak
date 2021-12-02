#pragma once

#ifndef DAK_UTILITY_SELECTION_H
#define DAK_UTILITY_SELECTION_H

#include <dak/utility/types.h>
#include <vector>

namespace dak::utility
{
   ////////////////////////////////////////////////////////////////////////////
   //
   // A selection container.

   class selection_t
   {
   public:
      // The data kept in the selection.
      std::vector<any_t> data;

      // Create an empty selection.
      selection_t() { }

      // Create a selection with data.
      selection_t(const any_t& d) { data.emplace_back(d); }

      // Add to the selection.
      void add(const any_t& d) { data.emplace_back(d); }

      // Verify if there is anything to undo.
      bool has_selection() const { return !data.empty(); }
   };
}

#endif

// vim: sw=3 : sts=3 : et : sta : 
