#include <dak/ui/mouse.h>

namespace dak
{
   namespace ui
   {
      namespace mouse
      {
         void emitter_t::mouse_clicked(const event_t& e)
         {
            send(e, &receiver_t::mouse_clicked);
         }

         void emitter_t::mouse_entered(const event_t& e)
         {
            send(e, &receiver_t::mouse_entered);
         }

         void emitter_t::mouse_exited(const event_t& e)
         {
            send(e, &receiver_t::mouse_exited);
         }

         void emitter_t::mouse_pressed(const event_t& e)
         {
            send(e, &receiver_t::mouse_pressed);
         }

         void emitter_t::mouse_released(const event_t& e)
         {
            send(e, &receiver_t::mouse_released);
         }

         void emitter_t::mouse_moved(const event_t& e)
         {
            send(e, &receiver_t::mouse_moved);
         }

         void emitter_t::mouse_dragged(const event_t& e)
         {
            send(e, &receiver_t::mouse_dragged);
         }

         void emitter_t::mouse_wheel(const event_t& e)
         {
            send(e, &receiver_t::mouse_wheel);
         }

         void emitter_t::send(const event_t& e, event_receiver er)
         {
            for (receiver_t* rec : event_receivers)
               (rec->*er)(e);
         }
      }
   }
}

// vim: sw=3 : sts=3 : et : sta : 
