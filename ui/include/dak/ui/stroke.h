#pragma once

#ifndef DAK_UI_STROKE_H
#define DAK_UI_STROKE_H

namespace dak::ui
   {
   ////////////////////////////////////////////////////////////////////////////
   //
   // Stroke style to draw lines.

   class stroke_t
   {
   public:
      enum class cap_style_t
      {
         flat,
         square,
         round,
      };

      enum class join_style_t
      {
         miter,
         bevel,
         round,
      };

      // Width of the line.
      double width = 1.;

      // How lines are ended.
      cap_style_t cap = cap_style_t::round;

      // How lines are joined.
      join_style_t join = join_style_t::round;

      // Stroke with a width, line-end and line-join styles.
      stroke_t(double w, cap_style_t c, join_style_t j) : width(w), cap(c), join(j) { }

      // Stroke with a width.
      stroke_t(double w) : width(w) { }

      // Comparison.
      bool operator == (const stroke_t& other) const
      {
         return width == other.width && cap == other.cap && join == other.join;
      }

      bool operator != (const stroke_t& other) const
      {
         return !(*this == other);
      }
   };
}

#endif

// vim: sw=3 : sts=3 : et : sta : 
