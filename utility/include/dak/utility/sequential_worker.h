#pragma once

#ifndef DAK_UTILITY_SEQUENTIAL_WORKER_H
#define DAK_UTILITY_SEQUENTIAL_WORKER_H

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <dak/utility/thread_pool.h>

#include <atomic>
#include <future>
#include <mutex>
#include <condition_variable>
#include <map>
#include <algorithm>


namespace dak::utility
{
   ////////////////////////////////////////////////////////////////////////////
   //
   // A dispatcher of work items to a single thread.
   //
   // Execute functions taking WORK_ITEM and producing a RESULT.

   template <class WORK_ITEM, class RESULT>
   struct sequential_worker_t : private work_provider_t
   {
      using result_t = typename RESULT;
      using work_item_t = typename WORK_ITEM;
      using function_t = typename std::function<result_t(work_item_t)>;
      using task_t = std::packaged_task<result_t(work_item_t)>;

      // How the function and work item is kept internally.
      struct work_t
      {
         task_t      task;
         work_item_t item;
      };

      // Create a sequential worker.
      sequential_worker_t() : my_thread_pool(*this, 1) {}

      // Destroy this sequential worker. Stop its thread.
      ~sequential_worker_t() { stop(); }

      // Stop all waiters.
      void stop() override
      {
         my_stop = true;
         my_cond.notify_all();
      }

      // Check if this sequenrtial worker is stopped.
      bool is_stopped() const override { return my_stop; }

      // Queue the given function and work item to be executed in a thread.
      std::future<result_t> add_work(work_item_t a_work_item, function_t a_function)
      {
         if (my_stop)
            return {};

         work_t work;
         work.task = std::move(task_t(a_function));
         work.item = std::move(a_work_item);

         auto result = work.task.get_future();

         {
            std::unique_lock lock(my_mutex);
            my_work_items.emplace_back(std::move(work));
         }

         my_cond.notify_all();

         return result;
      }

      // Wait for a particular result.
      result_t wait_for(std::future<result_t>& a_token)
      {
         while (!is_stopped())
         {
            std::unique_lock lock(my_mutex);

            if (a_token.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
               return a_token.get();

            my_cond.wait(lock);
         }

         return {};
      }

   private:
      // Wait for something to execute or execute something already in queue.
      void wait_or_execute() override
      {
         std::unique_lock lock(my_mutex);

         if (my_stop)
            return;

         // If there is nothing in the queue, wait for something to
         // happen and return immediately in case we are suppored to stop.
         if (my_work_items.size() <= 0)
         {
            my_cond.wait(lock);
            return;
         }

         // Execute the oldest work item.
         work_t work = std::move(my_work_items.back());
         my_work_items.pop_back();
         lock.unlock();

         work.task(work.item);

         // Notify potential waiters that a work item has been executed.
         my_cond.notify_all();
      }

      std::mutex                    my_mutex;
      std::condition_variable       my_cond;
      std::atomic<bool>             my_stop = false;
      std::vector<work_t>           my_work_items;

      // Note: the thread pool must be the last variable so that it gets
      //       destroyed first while the mutex, etc are still valid.  
      thread_pool_t                 my_thread_pool;
   };
}

#endif /* DAK_UTILITY_SEQUENTIAL_WORKER_H */
