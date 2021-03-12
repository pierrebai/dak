#pragma once

#ifndef DAK_UI_LAYER_H
#define DAK_UI_LAYER_H

#include <dak/ui/transformable.h>

#include <memory>

namespace dak::ui
{
   class drawing_t;

   ////////////////////////////////////////////////////////////////////////////
   //
   // A drawable, transformable layer.
   //
   // Sub-class must provide the internal draw implementation.

   class layer_t : public transformable_t
   {
   public:
      // If false, the layer is not drawn.
      bool is_drawn = true;

      // If false, the layer ignores set_transform().
      bool is_moving = true;

      // Create a layer.
      layer_t() { }

      // Copy a layer.
      virtual std::shared_ptr<layer_t> clone() const = 0;
      virtual void make_similar(const layer_t& other) = 0;

      // Draw the transformed layer.
      void draw(drawing_t& drw);

      // transformable implementation.
      const transform_t& get_transform() const override;
      layer_t& set_transform(const transform_t& t) override;
      layer_t& compose(const transform_t& t) override;

   protected:
      // The internal draw is called with the layer transform already applied.
      virtual void internal_draw(drawing_t& drw) = 0;

   private:
      transform_t trf = transform_t::identity();
   };
}

#endif

// vim: sw=3 : sts=3 : et : sta : 
