#pragma once

#ifndef DAK_UI_DRAWING_BASE_H
#define DAK_UI_DRAWING_BASE_H

#include <dak/ui/drawing.h>

namespace dak::ui
{
   ////////////////////////////////////////////////////////////////////////////
   //
   // A drawing interface common implementation that manages the color, stroke
   // and the transform stack.

   class drawing_base_t : public ui::drawing_t
   {
   public:
      // drawing interface partially implemented.
      stroke_t get_stroke() const override;
      drawing_base_t& set_stroke(const stroke_t& s) override;

      color_t get_color() const override;
      drawing_base_t& set_color(const color_t& c) override;

      const transform_t& get_transform() const override;
      drawing_base_t& set_transform(const transform_t&) override;
      drawing_base_t& compose(const transform_t&) override;
      drawing_base_t& push_transform() override;
      drawing_base_t& pop_transform() override;

   private:
      color_t co = color_t::black();
      stroke_t strk = stroke_t(1);
      transform_t trf = transform_t::identity();
      std::vector<transform_t> saved_trfs;
   };
}

#endif

// vim: sw=3 : sts=3 : et : sta : 
