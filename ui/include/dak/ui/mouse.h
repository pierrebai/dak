#pragma once

#ifndef DAK_UI_MOUSE_H
#define DAK_UI_MOUSE_H

#include <dak/ui/modifiers.h>

#include <dak/geometry/point.h>

#include <vector>

namespace dak::ui::mouse
{
   using geometry::point_t;

   ////////////////////////////////////////////////////////////////////////////
   //
   // Mouse buttons. Support three buttons.

   enum class buttons_t
   {
      none  = 0,
      one   = 1,
      two   = 2,
      three = 4,
      all   = 7,
   };

   inline buttons_t operator&(buttons_t a, buttons_t b) { return buttons_t(int(a) & int(b)); }
   inline buttons_t operator|(buttons_t a, buttons_t b) { return buttons_t(int(a) | int(b)); }
   inline buttons_t operator^(buttons_t a, buttons_t b) { return buttons_t(int(a) ^ int(b)); }

   ////////////////////////////////////////////////////////////////////////////
   //
   // Mouse input event.

   class event_t
   {
   public:
      // On-screen position relative to the widget.
      point_t position;

      // Mouse buttons being pressed down.
      mouse::buttons_t buttons;

      // Keyboard modifiers being held down.
      ui::modifiers_t modifiers;

      // Amount of mouse-wheel scrolling.
      double angle_degrees_delta = 0;
      point_t scroll_delta = point_t::origin();

      // Verify if the given buttons are pressed down.
      // Return true if any are pressed.
      bool has_buttons(mouse::buttons_t a) const { return (int(buttons) & int(a)) != 0; }

      // Verify if the given modifiers are held down.
      // Return true if any are pressed.
      bool has_modifiers(ui::modifiers_t a) const { return (int(modifiers) & int(a)) != 0; }

      // Create an event.
      event_t(point_t a_position, mouse::buttons_t some_buttons, ui::modifiers_t some_modifiers, double an_angle_delta, point_t a_scroll_delta)
      : position(a_position), buttons(some_buttons), modifiers(some_modifiers), angle_degrees_delta(an_angle_delta), scroll_delta(a_scroll_delta)
      {
      }
   };

   ////////////////////////////////////////////////////////////////////////////
   //
   // Interface needed to receive mouse events.

   class receiver_t
   {
   public:
      virtual ~receiver_t() = 0 { }

      // Various types of event that can be received.
      virtual void mouse_clicked(const event_t&) = 0;
      virtual void mouse_entered(const event_t&) = 0;
      virtual void mouse_exited(const event_t&) = 0;
      virtual void mouse_pressed(const event_t&) = 0;
      virtual void mouse_released(const event_t&) = 0;
      virtual void mouse_moved(const event_t&) = 0;
      virtual void mouse_dragged(const event_t&) = 0;
      virtual void mouse_wheel(const event_t&) = 0;
   };

   ////////////////////////////////////////////////////////////////////////////
   //
   // Generator of mouse events.

   class emitter_t
   {
   public:
      // Note: make sure to remove receivers before they are destroyed.
      // Note: not thread-safe. Use external mutex if needed.
      std::vector<receiver_t *> event_receivers;

      // Send the given event to all registered receivers.
      void mouse_clicked(const event_t& e);
      void mouse_entered(const event_t& e);
      void mouse_exited(const event_t& e);
      void mouse_pressed(const event_t& e);
      void mouse_released(const event_t& e);
      void mouse_moved(const event_t& e);
      void mouse_dragged(const event_t& e);
      void mouse_wheel(const event_t& e);

   private:
      // Member function type of receivers.
      typedef void (receiver_t::*event_receiver)(const event_t&);

      // Send the event to the specified receiver member function.
      void send(const event_t& e, event_receiver er);
   };

}

#endif

// vim: sw=3 : sts=3 : et : sta : 
