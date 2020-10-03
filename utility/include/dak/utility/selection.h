#pragma once

#ifndef DAK_UTILITY_SELECTION_H
#define DAK_UTILITY_SELECTION_H

#include <any>
#include <vector>

namespace dak::utility
{
   ////////////////////////////////////////////////////////////////////////////
   //
   // A selection_t container.
   class selection_t
   {
   public:
      // The data kept in the selection_t.
      std::vector<std::any> data;

      // Create an empty selection_t.
      selection_t() { }

      // Create a selection_t with data.
      selection_t(const std::any& d) { data.emplace_back(d); }

      // Add to the selection_t.
      void add(const std::any& d) { data.emplace_back(d); }

      // Verify if there is anything to undo.
      bool has_selection() const { return !data.empty(); }
   };
}

#endif

// vim: sw=3 : sts=3 : et : sta : 
