#include <dak/utility/threaded_items_worker.h>


namespace dak::utility
{
   using work_item_ptr_t = threaded_items_worker_t::work_item_ptr_t;

   namespace
   {
      work_item_ptr_t execute(work_item_ptr_t an_item, size_t a_recursion_depth)
      {
         if (an_item)
            an_item->execute();
         return an_item;
      }
   }

   // Create a threaded work using the given thread pool.
   threaded_items_worker_t::threaded_items_worker_t(size_t a_max_recursion, size_t a_reserved_ui_thread)
      : my_worker(a_max_recursion, a_reserved_ui_thread)
   {
   }

   // Destroy the threaded work, stops all workers.
   threaded_items_worker_t::~threaded_items_worker_t()
   {
   }

   // Stop all waiters.
   void threaded_items_worker_t::stop()
   {
      my_worker.stop();
   }

   // Check if this threaded work is stopped.
   bool threaded_items_worker_t::is_stopped() const
   {
      return my_worker.is_stopped();
   }

   // Queue the given function and work item to be executed in a thread.
   std::future<work_item_ptr_t> threaded_items_worker_t::add_work(const work_item_ptr_t& a_work_item, size_t a_recursion_depth)
   {
      return my_worker.add_work(a_work_item, a_recursion_depth, execute);
   }

   // Wait for a particular result, execute work while waiting.
   work_item_ptr_t threaded_items_worker_t::wait_for(std::future<work_item_ptr_t>& a_token, size_t a_recursion_depth)
   {
      return my_worker.wait_for(a_token, a_recursion_depth);
   }
}
