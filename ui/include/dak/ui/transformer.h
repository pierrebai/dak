#pragma once

#ifndef DAK_UI_TRANSFORMER_H
#define DAK_UI_TRANSFORMER_H

#include <dak/ui/transformable.h>
#include <dak/ui/modifiers.h>
#include <dak/ui/mouse.h>
#include <dak/ui/drawing.h>

#include <dak/geometry/constants.h>

#include <functional>

namespace dak::ui
{
   using geometry::PI;

   ////////////////////////////////////////////////////////////////////////////
   //
   // Transformer has all kinds of useful built-in interactions
   // for changing the transform of something.

   class transformer_t : public mouse::receiver_t
   {
   public:
      // What is being transformed and where it is drawn.
      transformable_t* manipulated;
      std::function<void(transformer_t&)> draw_callback;

      // Mode used to track how the mouse is handled: normally, move, rotate, scale.
      enum class interaction_mode_t
      {
         normal   = 0,
         moving   = 1,
         rotating = 2,
         scaling  = 3,

         lowest   = 0,
         highest  = 3,
      };

      // Force a particular interaction mode.
      interaction_mode_t forced_interaction_mode = interaction_mode_t::normal;

      // Modifier to be held to allow mouse interaction. By default, shift.
      modifiers_t mouse_interaction_modifier = modifiers_t::shift;

      // Creation.
      transformer_t(std::function<void(transformer_t&)> draw_callback);
      transformer_t(transformable_t& tr, std::function<void(transformer_t&)> draw_callback);

      // Draw interaction feedback when needed. Returns True if it drew something.
      bool draw(drawing_t& drw);

      // Mouse event handling from mouse::receiver_t.
      void mouse_clicked(const mouse::event_t& me) override;
      void mouse_entered(const mouse::event_t& me) override;
      void mouse_exited(const mouse::event_t& me) override;
      void mouse_pressed(const mouse::event_t& me) override;
      void mouse_released(const mouse::event_t& me) override;
      void mouse_moved(const mouse::event_t& me) override;
      void mouse_dragged(const mouse::event_t& me) override;
      void mouse_wheel(const mouse::event_t& me) override;

      const point_t& get_tracked_point() const { return tracked_point; }

      void end_interaction();

   private:
      // Interaction modes.
      interaction_mode_t get_wheel_interaction_mode(const mouse::event_t& me);
      interaction_mode_t get_button_interaction_mode(const mouse::event_t& me);

      // Drawing current interaction. Returns True if it drew something.
      bool draw_moving(drawing_t& drawing_t);
      bool draw_rotating(drawing_t& drawing_t);
      bool draw_scaling(drawing_t& drawing_t);

      // Internal data handling.
      void clear_interaction_data();
      void update_tracked_position(const mouse::event_t& me);

      // Mouse interactions.
      void start_interaction(const mouse::event_t& me);

      void common_move(const point_t& from, const point_t& to);
      void common_rotate(const point_t& from, const point_t& to);
      void common_rotate(const point_t& a_center_of_rotation, double a_radians_angle);
      void common_scale(const point_t& from, const point_t& to);
      void common_scale(const point_t& a_center_of_scale, double a_ratio);

      void drag_move(const mouse::event_t& me);
      void drag_rotate(const mouse::event_t& me);
      void drag_scale(const mouse::event_t& me);

      void wheel_move(const mouse::event_t& me);
      void wheel_rotate(const mouse::event_t& me);
      void wheel_scale(const mouse::event_t& me);

      double calculate_scaling(const point_t& p);
      point_t screen_to_transformable(const point_t& screen_point) const;

      // User input tracking..
      point_t last_point;
      point_t tracked_point;
      point_t initial_point;
      bool has_moved_enough_to_interact = false;
      interaction_mode_t _interaction_mode = interaction_mode_t::normal;

      // Current transformation during one interaction.
      double interaction_rotating_angle = 0;
      double interaction_scaling_factor = 0;
      point_t  interaction_moving_delta = point_t::origin();

      // Size of drawings showing feedback for the interaction.
      static const int manipSizePercent = 80;
      static double get_feedback_size(const rectangle_t& r);

      // Color of feedback drawings.
      static constexpr color_t draw_color() { return color_t(225, 190, 50, 190); }
   };
}

#endif

// vim: sw=3 : sts=3 : et : sta : 

