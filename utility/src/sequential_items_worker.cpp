#include <dak/utility/sequential_items_worker.h>

namespace dak::utility
{
   using item_ptr_t = sequential_items_worker_t::item_ptr_t;

   namespace
   {
      item_ptr_t execute(item_ptr_t an_item)
      {
         if (an_item)
            an_item->execute();
         return an_item;
      }
   }

   // Create a sequential worker.
   sequential_items_worker_t::sequential_items_worker_t()
      : my_worker()
   {
   }

   // Destroy this sequential worker, stops its worker.
   sequential_items_worker_t::~sequential_items_worker_t()
   {
   }

   // Stop all waiters.
   void sequential_items_worker_t::stop()
   {
      my_worker.stop();
   }

   // Check if this sequential worker is stopped.
   bool sequential_items_worker_t::is_stopped() const
   {
      return my_worker.is_stopped();
   }

   // Queue the given function and work item to be executed in a thread.
   std::future<item_ptr_t> sequential_items_worker_t::add_work(const item_ptr_t& a_work_item)
   {
      return my_worker.add_work(a_work_item, execute);
   }

   // Wait for a particular result, execute work while waiting.
   item_ptr_t sequential_items_worker_t::wait_for(std::future<item_ptr_t>& a_token)
   {
      return my_worker.wait_for(a_token);
   }
}
