#pragma once

#ifndef DAK_UI_LAYERED_H
#define DAK_UI_LAYERED_H

#include <dak/ui/layer.h>

#include <vector>
#include <memory>

namespace dak::ui
{
   ////////////////////////////////////////////////////////////////////////////
   //
   // Transformable container of multiple layers.
   // When transformed, transforms all its layers.

   class layered_t : public transformable_t
   {
   public:
      using layers_t = std::vector<std::shared_ptr<layer_t>>;

      // Create a layers container.
      layered_t() { }

      // The layers.
      // The one at index zero is the highest when drawn (on top).
      const layers_t& get_layers() const { return _layers; }
      void set_layers(const layers_t& l);

      // Draw the layers.
      void draw(drawing_t& drw);

      // transformable implementation.
      const transform_t& get_transform() const override;
      layered_t& set_transform(const transform_t& t) override;
      layered_t& compose(const transform_t& t) override;

   private:
      transform_t trf = transform_t::identity();
      layers_t _layers;
   };

   ////////////////////////////////////////////////////////////////////////////
   //
   // Draw the layered transformable in the given drawing.

   void draw_layered(drawing_t& drw, ui::layered_t* layered);
}

#endif

// vim: sw=3 : sts=3 : et : sta : 
