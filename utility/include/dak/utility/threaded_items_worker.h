#pragma once

#ifndef DAK_UTILITY_THREADED_ITEMS_WORKER_H
#define DAK_UTILITY_THREADED_ITEMS_WORKER_H

#include <dak/utility/threaded_worker.h>
#include <dak/utility/work_item.h>

namespace dak::utility
{
   ////////////////////////////////////////////////////////////////////////////
   //
   // A dispatcher of work items to a thread pool.
   //
   // Execute work_item_t.

   struct threaded_items_worker_t
   {
      using work_item_ptr_t = std::shared_ptr<work_item_t>;

      // Create a threaded work using the given thread pool.
      threaded_items_worker_t(size_t a_max_recursion = 3, size_t a_reserved_ui_threads = 0);

      // Destroy the threaded work, stops all workers.
      ~threaded_items_worker_t();

      // Stop all waiters.
      void stop();

      // Check if this threaded work is stopped.
      bool is_stopped() const;

      // Queue the given function and work item to be executed in a thread.
      std::future<work_item_ptr_t> add_work(const work_item_ptr_t& a_work_item, size_t a_recursion_depth = 0);

      // Wait for a particular result, execute work while waiting.
      work_item_ptr_t wait_for(std::future<work_item_ptr_t>& a_token, size_t a_recursion_depth = 0);

   private:
      threaded_worker_t<work_item_ptr_t, work_item_ptr_t> my_worker;
   };
}

#endif /* DAK_UTILITY_THREADED_ITEMS_WORKER_H */
