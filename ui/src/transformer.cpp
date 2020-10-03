#include <dak/ui/transformer.h>

#include <dak/geometry/utility.h>

namespace dak
{
   namespace ui
   {
      using geometry::PI;

      constexpr double rotate_oval_radius = 40.;
      constexpr double scale_oval_radius = 40.;

      transformer_t::transformer_t(std::function<void(transformer_t&)> draw_callback)
      : manipulated(nullptr), draw_callback(draw_callback)
      {
         clear_interaction_data();
      }

      transformer_t::transformer_t(transformable_t& tr, std::function<void(transformer_t&)> draw_callback)
      : manipulated(&tr), draw_callback(draw_callback)
      {
         clear_interaction_data();
      }

      point_t transformer_t::screen_to_transformable(const point_t& screen_point) const
      {
         if (!manipulated)
            return screen_point;

         return screen_point.apply(manipulated->get_transform().invert());
      }

      ////////////////////////////////////////////////////////////////////////////
      //
      // Drawing current interaction.

      void transformer_t::draw(drawing_t& drw)
      {
         switch (_interaction_mode)
         {
            default:
            case interaction_mode_t::normal:
               break;
            case interaction_mode_t::moving:
               draw_moving(drw);
               break;
            case interaction_mode_t::rotating:
               draw_rotating(drw);
               break;
            case interaction_mode_t::scaling:
               draw_scaling(drw);
               break;
         }
      }

      double transformer_t::get_feedback_size(const rectangle_t& r)
      {
         return (r.width < r.height ? r.width : r.height) * manipSizePercent / 100;
      }

      void transformer_t::draw_moving(drawing_t& drawing)
      {
         if (initial_point.is_invalid())
            return;

         const double size = get_feedback_size(drawing.get_bounds());
         const point_t& mid = initial_point;

         drawing.set_color(draw_color());

         // Draw four arrows moved by the amount moved.
         {
            drawing.push_transform();
            drawing.compose(transform_t::translate(mid));

            const polygon_t poly
            ({
                point_t(size / 16,      0),
                point_t(size * 1 / 16,  size / 32),
                point_t(size * 3 / 8,   size / 32),
                point_t(size * 3 / 8,   size / 16),
                point_t(size / 2,       0),
                point_t(size * 3 / 8,  -size / 16),
                point_t(size * 3 / 8,  -size / 32),
                point_t(size * 1 / 16, -size / 32),
             });

            const int affected_xs[] = { 1, 0, -1, 0 };
            const int affected_ys[] = { 0, 1, 0, -1 };

            for (int i = 0; i < 4; ++i)
            {
               // Note: yes, we always translate along X axis, even for Y
               //       because we always move in rotated coordinates.
               drawing.push_transform();
               if (affected_xs[i] * interaction_moving_delta.x > 0)
                  drawing.compose(transform_t::translate(interaction_moving_delta.x, 0));
               if (affected_ys[i] * interaction_moving_delta.y > 0)
                  drawing.compose(transform_t::translate(0, interaction_moving_delta.y));
               drawing.compose(transform_t::rotate(PI * i / 2));
               drawing.fill_polygon(poly);
               drawing.pop_transform();
            }

            drawing.pop_transform();
         }

         if (interaction_moving_delta != point_t::origin())
         {
            const stroke_t saved_stroke = drawing.get_stroke();
            //float dashes[] = { size / 1024.0f, size / 16.0f };
            //stroke wideStroke = stroke( size / 16, stroke::cap_style::round, stroke::join_style::round, 1.0f, dashes, 0.0f );
            const stroke_t wideStroke = stroke_t(size / 16, stroke_t::cap_style_t::round, stroke_t::join_style_t::round);
            drawing.set_stroke(wideStroke);
            drawing.draw_line(mid, interaction_moving_delta + mid);
            drawing.set_stroke(saved_stroke);
         }
         else
         {
            drawing.fill_oval(mid, size / 16, size / 16);
         }
      }

      void transformer_t::draw_rotating(drawing_t& drawing)
      {
         if (initial_point.is_invalid())
            return;

         const double size = get_feedback_size(drawing.get_bounds());
         const point_t& mid = initial_point;

         drawing.set_color(draw_color());

         // Draw four arrows around the perimeter of a circle.
         {
            drawing.push_transform();
            drawing.compose(transform_t::translate(mid));
            drawing.compose(transform_t::rotate(interaction_rotating_angle));

            const polygon_t poly
            ({
               point_t(size / 2,        0),
               point_t(size * 9 / 16,   0),
               point_t(size / 2,        size / 8),
               point_t(size / 2,       -size / 16),
               point_t(size * 17 / 32,  0),
             });

            for (int i = 0; i < 4; ++i)
            {
               drawing.push_transform();
               drawing.compose(transform_t::rotate(PI * i / 2));
               drawing.fill_polygon(poly);
               drawing.pop_transform();
            }
            drawing.pop_transform();
         }

         const stroke_t saved_stroke = drawing.get_stroke();
         const stroke_t wideStroke(size / 64);
         drawing.set_stroke(wideStroke);
         drawing.draw_oval(mid, size/2, size/2);
         drawing.set_stroke(saved_stroke);

         drawing.fill_arc(mid, size / 2, size / 2, 0, interaction_rotating_angle);
         drawing.fill_oval(mid, rotate_oval_radius, rotate_oval_radius);
      }

      void transformer_t::draw_scaling(drawing_t& drawing)
      {
         if (initial_point.is_invalid())
            return;

         const double size = get_feedback_size(drawing.get_bounds());
         const point_t& mid = initial_point;
         const double isf = interaction_scaling_factor;

         drawing.set_color(draw_color());

         // Draw four diagonal two-headed arrows with the center scaled to the scaled ratio.
         {
            drawing.push_transform();
            drawing.compose(transform_t::translate(mid));
            drawing.compose(transform_t::rotate(PI / 4));

            const polygon_t poly
            ({
               point_t(size * 1 / 16, 0            ),
               point_t(size * 1 / 8,  size * 1 / 32),
               point_t(size * 1 / 8,  size * 1 / 64),
               point_t(size * 3 / 8 , size * 1 / 32),
               point_t(size * 3 / 8,  size * 1 / 16),
               point_t(size * 1 / 2,  0            ),
               point_t(size * 3 / 8, -size * 1 / 16),
               point_t(size * 3 / 8, -size * 1 / 32),
               point_t(size * 1 / 8, -size * 1 / 64),
               point_t(size * 1 / 8, -size * 1 / 32),
             });


            for (int i = 0; i < 4; ++i)
            {
               drawing.push_transform();
               drawing.compose(transform_t::rotate(PI * i / 2));
               drawing.fill_polygon(poly);
               drawing.pop_transform();
            }
            drawing.pop_transform();
         }

         const stroke_t saved_stroke = drawing.get_stroke();

         drawing.set_stroke(stroke_t(size / 64));
         drawing.draw_oval(mid, size/2, size/2);

         drawing.set_stroke(stroke_t(3));
         if (isf >= 1.)
            drawing.fill_oval(mid, scale_oval_radius, scale_oval_radius);
         else
            drawing.draw_oval(mid, scale_oval_radius, scale_oval_radius);

         drawing.set_stroke(stroke_t(3));
         drawing.draw_oval(mid, scale_oval_radius * isf, scale_oval_radius * isf);

         drawing.set_stroke(saved_stroke);
      }

      ////////////////////////////////////////////////////////////////////////////
      //
      // Internal data handling.

      void transformer_t::clear_interaction_data()
      {
         interaction_moving_delta = point_t::origin();
         interaction_rotating_angle = 0;
         interaction_scaling_factor = 1;

         last_point = point_t();
         initial_point = point_t();
         tracked_point = point_t();
         has_moved_enough_to_interact = false;
      }

      void transformer_t::update_tracked_position(const mouse::event_t& me)
      {
         tracked_point = me.position;
      }

      ////////////////////////////////////////////////////////////////////////////
      //
      // Interaction mode.

      transformer_t::interaction_mode_t transformer_t::get_wheel_interaction_mode(const mouse::event_t& me)
      {
         if (forced_interaction_mode != interaction_mode_t::normal)
            _interaction_mode = forced_interaction_mode;
         else if (me.has_modifiers(modifiers_t::shift))
            _interaction_mode = interaction_mode_t::rotating;
         else if (me.has_modifiers(modifiers_t::alt))
            _interaction_mode = interaction_mode_t::scaling;
         else
            _interaction_mode = interaction_mode_t::moving;

         return _interaction_mode;
      }

      transformer_t::interaction_mode_t transformer_t::get_button_interaction_mode(const mouse::event_t& me)
      {
         if (forced_interaction_mode != interaction_mode_t::normal)
            _interaction_mode = forced_interaction_mode;
         else if (!me.has_modifiers(modifiers_t::shift))
            _interaction_mode = interaction_mode_t::normal;
         else if ((me.has_buttons(mouse::buttons_t::two)) != 0)
            _interaction_mode = interaction_mode_t::rotating;
         else if ((me.has_buttons(mouse::buttons_t::three)) != 0)
            _interaction_mode = interaction_mode_t::scaling;
         else
            _interaction_mode = interaction_mode_t::moving;

         return _interaction_mode;
      }

      ////////////////////////////////////////////////////////////////////////////
      //
      // Common mouse/wheel interactions.

      void transformer_t::start_interaction(const mouse::event_t& me)
      {
         clear_interaction_data();
         last_point = me.position;
         draw_callback(*this);
      }

      void transformer_t::common_move(const point_t& from, const point_t& to)
      {
         if (manipulated)
            manipulated->compose(transform_t::translate(to.x - from.x, to.y - from.y));
         draw_callback(*this);
      }

      void transformer_t::common_rotate(const point_t& from, const point_t& to)
      {
         const point_t mid = screen_to_transformable(initial_point);

         double delta_angle = mid.sweep(from, to);
         if (delta_angle > PI)
            delta_angle -= 2 * PI;

         interaction_rotating_angle += delta_angle;
         while (interaction_rotating_angle >= 2 * PI)
            interaction_rotating_angle -= 2 * PI;
         while (interaction_rotating_angle <= -2 * PI)
            interaction_rotating_angle += 2 * PI;

         if (manipulated)
            manipulated->compose(transform_t::rotate(mid, delta_angle));
         draw_callback(*this);
      }

      double transformer_t::calculate_scaling(const point_t& p)
      {
         const double dist = p.distance(initial_point);
         if (dist < rotate_oval_radius)
            return 1.;

         const double delta = (p - initial_point).x;

         return (delta > 0) ? (dist / rotate_oval_radius) : (rotate_oval_radius / dist);
      }

      void transformer_t::common_scale(const point_t& from, const point_t& to)
      {
         const double from_ratio = calculate_scaling(from);
         const double to_ratio = calculate_scaling(to);
         if (from_ratio == 0. || to_ratio == 0.)
         {
            draw_callback(*this);
            return;
         }

         const double ratio = to_ratio / from_ratio;

         interaction_scaling_factor *= ratio;

         if (manipulated)
            manipulated->compose(transform_t::scale(screen_to_transformable(initial_point), ratio));

         draw_callback(*this);
      }

      void transformer_t::end_interaction()
      {
         clear_interaction_data();
         _interaction_mode = forced_interaction_mode;
         draw_callback(*this);
      }

      ////////////////////////////////////////////////////////////////////////////
      //
      // Mouse interactions.

      void transformer_t::drag_move(const mouse::event_t& me)
      {
         if (!last_point.is_invalid())
         {
            const point_t from = screen_to_transformable(last_point);
            const point_t to = screen_to_transformable(me.position);

            interaction_moving_delta = interaction_moving_delta + (me.position - last_point);

            common_move(from, to);
         }
         else
         {
            draw_callback(*this);
         }

         last_point = me.position;
      }

      void transformer_t::drag_rotate(const mouse::event_t& me)
      {
         if (has_moved_enough_to_interact)
         {
            {
               const point_t from = screen_to_transformable(last_point);
               const point_t to = screen_to_transformable(me.position);
               common_rotate(from, to);
            }
         }
         else
         {
            if (!last_point.is_invalid() && !initial_point.is_invalid())
            {
               has_moved_enough_to_interact = (initial_point.distance_2(me.position) >= rotate_oval_radius * rotate_oval_radius);
            }
            draw_callback(*this);
         }

         last_point = me.position;
      }

      void transformer_t::drag_scale(const mouse::event_t& me)
      {
         const point_t from = last_point;
         const point_t to = me.position;
         common_scale(from, to);

         last_point = me.position;
      }

      ////////////////////////////////////////////////////////////////////////////
      //
      // Mouse wheel interactions.

      void transformer_t::wheel_move(const mouse::event_t& me)
      {
         const int amount = me.scroll_amount;

         const point_t from = screen_to_transformable(point_t::origin());
         const point_t to = screen_to_transformable(point_t(0, -amount));

         common_move(from, to);
      }

      void transformer_t::wheel_rotate(const mouse::event_t& me)
      {
         const int amount = me.scroll_amount;

         const point_t from = screen_to_transformable(point_t::origin());
         const point_t to = screen_to_transformable(point_t(0, amount));

         common_rotate(from, to);
      }

      void transformer_t::wheel_scale(const mouse::event_t& me)
      {
         const int amount = me.scroll_amount;

         const point_t from = point_t::origin();
         const point_t to = point_t(0, amount);

         common_scale(from, to);
      }

      ////////////////////////////////////////////////////////////////////////////
      //
      // Mouse event handling.

      void transformer_t::mouse_clicked(const mouse::event_t& me)
      {
         update_tracked_position(me);
      }

      void transformer_t::mouse_entered(const mouse::event_t& me)
      {
         update_tracked_position(me);

         switch (get_button_interaction_mode(me)) {
            default:
            case interaction_mode_t::normal:
               break;
            case interaction_mode_t::moving:
            case interaction_mode_t::rotating:
            case interaction_mode_t::scaling:
               draw_callback(*this);
               break;
         }
      }

      void transformer_t::mouse_exited(const mouse::event_t& me)
      {
         update_tracked_position(me);

         _interaction_mode = interaction_mode_t::normal;
         draw_callback(*this);
      }

      void transformer_t::mouse_pressed(const mouse::event_t& me)
      {
         update_tracked_position(me);
         initial_point = me.position;

         switch (get_button_interaction_mode(me)) {
            default:
            case interaction_mode_t::normal:
               break;
            case interaction_mode_t::moving:
            case interaction_mode_t::rotating:
            case interaction_mode_t::scaling:
               start_interaction(me);
               break;
         }
      }

      void transformer_t::mouse_released(const mouse::event_t& me)
      {
         update_tracked_position(me);
         end_interaction();
      }

      void transformer_t::mouse_moved(const mouse::event_t& me)
      {
         update_tracked_position(me);
      }

      void transformer_t::mouse_dragged(const mouse::event_t& me)
      {
         update_tracked_position(me);
         if (initial_point.is_invalid())
            initial_point = me.position;

         switch (get_button_interaction_mode(me)) {
            default:
            case interaction_mode_t::normal:
               break;
            case interaction_mode_t::moving:
               drag_move(me);
               break;
            case interaction_mode_t::rotating:
               drag_rotate(me);
               break;
            case interaction_mode_t::scaling:
               drag_scale(me);
               break;
         }
      }

      void transformer_t::mouse_wheel(const mouse::event_t& me)
      {
         update_tracked_position(me);
         initial_point = me.position;

         switch (get_wheel_interaction_mode(me)) {
            default:
            case interaction_mode_t::moving:
               wheel_move(me);
               break;
            case interaction_mode_t::rotating:
               wheel_rotate(me);
               break;
            case interaction_mode_t::scaling:
               wheel_scale(me);
               break;
         }
      }
   }
}

// vim: sw=3 : sts=3 : et : sta : 

