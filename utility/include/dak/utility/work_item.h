#pragma once

#ifndef DAK_UTILITY_WORK_ITEM_H
#define DAK_UTILITY_WORK_ITEM_H

#include <memory>
#include <functional>

namespace dak::utility
{
   ////////////////////////////////////////////////////////////////////////////
   //
   // An item of work that can be executed.
   
   struct work_item_t
   {
      virtual ~work_item_t() = default;
      virtual void execute() = 0;
   };
}

#endif /* DAK_UTILITY_WORK_ITEM_H */
