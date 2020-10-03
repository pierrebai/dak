#pragma once

#ifndef DAK_GEOMETRY_MAP_H
#define DAK_GEOMETRY_MAP_H

#include <dak/geometry/edge.h>

#include <utility>
#include <string>
#include <vector>

namespace dak::geometry
{
   class point_t;
   class transform_t;

   ////////////////////////////////////////////////////////////////////////////
   //
   // The implementation of a planar map abstraction.  A planar map is
   // an (undirected) graph represented on the plane in such a way that
   // edges_t don't cross points or other edges_t.
   //
   // What we actually stored are directed edges_t sorted by the x position
   // of the first point of the edge, but each connection between two
   // points are kept twice, once for each direction.

   class edges_map_t
   {
   public:
      // Container of edges_t.
      typedef std::vector<edge_t> edges_t;
      struct range : std::pair<edges_t::const_iterator, edges_t::const_iterator>
      {
         range() { }
         range(const edges_t::const_iterator& b, const edges_t::const_iterator& e) : std::pair<edges_t::const_iterator, edges_t::const_iterator>(b, e) { }
         edges_t::const_iterator begin() const { return first; }
         edges_t::const_iterator end() const { return second; }
         size_t size() const { return second - first; }
      };

      // Empty map.
      edges_map_t() { }

      // Map with all given edges_t inserted.
      edges_map_t(const edges_t& from_edges);

      // Verify if two points are connected by an edge.
      bool are_connected(const point_t& a, const point_t& b) const;

      // Verify if a point is in the map. (End-point of an edge)
      bool contains(const point_t& a) const;

      // Verify if an edge is already in the map.
      bool contains(const edge_t& e) const;

      // Return all edges_t.
      const edges_t& all() const { return _sorted_edges; }

      // Return all edges_t that have the point as their first point.
      range outbounds(const point_t& p) const;

      // Return the preceeding a succeeding edge of an edge.
      std::pair<edge_t, edge_t> before_after(const edge_t& e) const;
      static std::pair<edge_t, edge_t> before_after(const range& outbounds, const edge_t& e);

      const edge_t& before(const edge_t& e) const;
      static const edge_t& before(const range& outbounds, const edge_t& e);

      const edge_t& after(const edge_t& e) const;
      static const edge_t& after(const range& outbounds, const edge_t& e);

      // Return the edge that is opposite of an edge at the p2 intersection.
      const edge_t& continuation(const edge_t& e) const;
      static const edge_t& continuation(const range& outbounds, const edge_t& e);

      // Remove a point and all connected edges_t.
      void remove(const point_t& p);

      // Remove an edge.
      void remove(const edge_t& e);

      // Merge two maps, adding necessary intersection points as needed.
      void merge(const edges_map_t& other);

      // Merge two maps, assuming no too edges_t are the same nor intersect.
      void merge_non_overlapping(const edges_map_t& other);

      // Insert a group of edges_t, adding necessary intersection points as needed.
      void insert(const edges_t& from_edges);

      // Insert one edge, adding necessary intersection points as needed.
      void insert(const edge_t& new_edge);

      // Insert one edge between two points, adding necessary intersection points as needed.
      void connect(const point_t& p1, const point_t& p2);

      // Apply a transform to the map, creating a new map.
      edges_map_t apply(const transform_t& t) const;

      // Apply a transform to the map itself.
      edges_map_t& apply_to_self(const transform_t& t);

      // Verify if there are any errors in the map.
      // Return the list of errors.
      std::vector<std::wstring> verify() const;

      // Verify if there are any errors in the map.
      // Throw an exception if there is at least on error.
      void verify_and_throw() const;

   private:
      // Sort the canonical edges_t in ascending order.
      void internal_sort_edges();

      // Fill the list of connections of the requested kind.
      static void internal_fill_connections(const edges_t& from_edges, const point_t& p, edges_t& conns, bool inbound, bool outbound);

      // Split existing edges_t and record the intersections for each edge,
      // old and new.
      void internal_connect(const edge_t& new_edge, std::vector<std::pair<edge_t, point_t>>& temp_edge_intersections);

      // Insert new edges_t and intersections.
      void internal_add_intersections_and_sort(std::vector<std::pair<edge_t, point_t>>& temp_edge_intersections);

      // Internal implementation of the validity verifications.
      void internal_verify() const;

      edges_t _sorted_edges;

   };
}

#endif

// vim: sw=3 : sts=3 : et : sta : 
