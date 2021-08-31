#pragma once

#ifndef DAK_UI_COLOR_H
#define DAK_UI_COLOR_H

#include <random>

namespace dak::ui
{
   ////////////////////////////////////////////////////////////////////////////
   //
   // Four channels color: red, green, blue and alpha. 8-bit values.

   class color_t
   {
   public:
      typedef unsigned char channel;
      channel r = 0;
      channel g = 0;
      channel b = 0;
      channel a = 0;

      constexpr color_t() = default;
      constexpr color_t(channel r, channel g, channel b, channel a = 255) : r(r), g(g), b(b), a(a) { }
      static constexpr color_t from_fractions(double r, double g, double b, double a = 1.) { return color_t(channel(255 * r), channel(255 * g), channel(255 * b), channel(255 * a)); }

      static constexpr color_t black()    { return color_t(  0,   0,   0, 255); }
      static constexpr color_t white()    { return color_t(255, 255, 255, 255); }
      static constexpr color_t red()      { return color_t(255,   0,   0, 255); }
      static constexpr color_t green()    { return color_t(  0, 255,   0, 255); }
      static constexpr color_t blue()     { return color_t(  0,   0, 255, 255); }
      static constexpr color_t cyan()     { return color_t(  0, 255, 255, 255); }
      static constexpr color_t yellow()   { return color_t(255, 255,   0, 255); }
      static constexpr color_t magenta()  { return color_t(255,   0, 255, 255); }
      static constexpr color_t grey()     { return color_t(160, 160, 160, 255); }

      constexpr color_t percent(double pc) const { return color_t(channel(r * pc / 100), channel(g * pc / 100), channel(b * pc / 100), a); }
      constexpr color_t operator+(const color_t& other) const { return color_t(r + other.r, g + other.g, b + other.b, a); }
      constexpr color_t operator-(const color_t& other) const { return color_t(r - other.r, g - other.g, b - other.b, a); }

      // Comparison.
      constexpr bool operator == (const color_t& other) const
      {
         return r == other.r && g == other.g && b == other.b && a == other.a;
      }

      constexpr bool operator != (const color_t& other) const
      {
         return !(*this == other);
      }

      constexpr bool is_pale() const
      {
         return r >= 240 && g >= 240 && b >= 240;
      }

      constexpr bool is_dark() const
      {
         return r <= 20 && g <= 20 && b <= 20;
      }
   };

   class random_colors
   {
   public:
      color_t any();
      color_t red();
      color_t green();
      color_t blue();
      color_t cyan();
      color_t yellow();
      color_t magenta();
      color_t grey();

   private:
      color_t::channel next_color();

      std::minstd_rand rand;
   };
}

#endif

// vim: sw=3 : sts=3 : et : sta : 
