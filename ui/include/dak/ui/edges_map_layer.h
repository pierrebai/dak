#pragma once

#ifndef DAK_UI_MAP_LAYER_H
#define DAK_UI_MAP_LAYER_H

#include <dak/ui/layer.h>

#include <dak/geometry/edges_map.h>

namespace dak::ui
{
   class drawing_t;

   ////////////////////////////////////////////////////////////////////////////
   //
   // A layer showing a map.

   class edges_map_layer_t : public layer_t
   {
   public:
      geometry::edges_map_t map;

      // Create a layer.
      edges_map_layer_t() { }
      edges_map_layer_t(geometry::edges_map_t& map) :map(map) { }

      // Copy a layer.
      std::shared_ptr<layer_t> clone() const override;
      void make_similar(const layer_t& other) override;

      // Comparison.
      virtual bool operator==(const layer_t& other) const override { return layer_t::operator==(other); }

   protected:
      // The internal draw is called with the layer transform already applied.
      void internal_draw(drawing_t& drw) override;
   };
}

#endif

// vim: sw=3 : sts=3 : et : sta : 
