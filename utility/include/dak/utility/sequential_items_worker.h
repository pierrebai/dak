#pragma once

#ifndef DAK_UTILITY_SEQUENTIAL_ITEMS_WORKER_H
#define DAK_UTILITY_SEQUENTIAL_ITEMS_WORKER_H

#include <dak/utility/sequential_worker.h>
#include <dak/utility/work_item.h>

namespace dak::utility
{
   ////////////////////////////////////////////////////////////////////////////
   //
   // A dispatcher of work items to a thread.
   //
   // Execute work_item_t.

   struct sequential_items_worker_t
   {
      using item_ptr_t = work_item_t::ptr_t;

      // Create a sequential worker.
      sequential_items_worker_t();

      // Destroy thkis sequential worker, stops all workers.
      ~sequential_items_worker_t();

      // Stop all waiters.
      void stop();

      // Check if this sequential worker is stopped.
      bool is_stopped() const;

      // Queue the given function and work item to be executed in a thread.
      std::future<item_ptr_t> add_work(const item_ptr_t& a_work_item);

      // Wait for a particular result, execute work while waiting.
      item_ptr_t wait_for(std::future<item_ptr_t>& a_token);

   private:
      sequential_worker_t<item_ptr_t, item_ptr_t> my_worker;
   };
}

#endif /* DAK_UTILITY_SEQUENTIAL_ITEMS_WORKER_H */
