#pragma once

#ifndef DAK_GEOMETRY_EDGE_H
#define DAK_GEOMETRY_EDGE_H

#include <dak/geometry/point.h>
#include <dak/geometry/constants.h>

namespace dak::geometry
{
   class transform_t;

   ////////////////////////////////////////////////////////////////////////////
   //
   // Oriented edge connecting two points in a geometrical map.

   class edge_t
   {
   private:
      static constexpr double very_negative = -1e100;

   public:

      // Three common edges.
      static edge_t unit_x() { return edge_t(point_t::origin(), point_t::unit_x()); }
      static edge_t unit_y() { return edge_t(point_t::origin(), point_t::unit_y()); }
      static const edge_t invalid;

      // The ordered points.
      point_t p1;
      point_t p2;

      // The order of edges around a point. Roughly anti-clockwise angle.
      double order = very_negative;

      // Invalid edge.
      constexpr edge_t() { }

      // Edge between two points.
      edge_t(const point_t& p1, const point_t& p2) : p1(p1), p2(p2), order(angle()) { }

      // Special edge used to search for the first edge around a point, when they are sorted.
      static edge_t lowest_edge(const point_t& p1)
      {
         return edge_t(p1, very_negative);
      }

      // Special edge used to search for the last edge around a point, when they are sorted.
      static edge_t highest_edge(const point_t& p1)
      {
         return edge_t(p1, -very_negative);
      }

      // Swap two edges.
      constexpr void swap(edge_t& other)
      {
         p1.swap(other.p1);
         p2.swap(other.p2);
         { const double t = order; order = other.order; other.order = t; }
      }

      // Edge comparisons. Two invalid are equal.
      bool operator ==(const edge_t& other) const
      {
         return p1 == other.p1 && p2 == other.p2;
      }

      bool operator !=(const edge_t& other) const
      {
         return !(*this == other);
      }

      // The less-than operator compares the first point, then the order.
      // Thus, two overlapped edges with different second point will not be less than each other,
      // yet they won't be equal. This cannot happen in a map anyway since edges never overlap.
      bool operator <(const edge_t& other) const
      {
         return (p1 < other.p1)
               || (p1 == other.p1 && order < other.order - TOLERANCE);
      }

      // Possibly swap the points of the edge to make the first point be less than the second.
      edge_t& make_canonical()
      {
         if (p2 < p1)
         {
            p1.swap(p2);
            order = angle();
         }
         return *this;
      }

      // Create a copy that is guaranteed to be canonical if the original was a valid edge.
      edge_t canonical() const
      {
         return p1 < p2 ? *this : twin();
      }

      // Create a copy that has the points swapped.
      edge_t twin() const
      {
         return edge_t(p2, p1);
      }

      // Verify if the edge is canonical.
      bool is_canonical() const
      {
         return p1 < p2;
      }

      // Verify if the edge is invalid.
      constexpr bool is_invalid() const
      {
         return order == very_negative;
      }

      // Verify if the edge is trivial (both points are equal).
      bool is_trivial() const
      {
         return p1 == p2;
      }

      // Calculates the angle between two edges.
      double angle(const edge_t& other) const
      {
         double res = other.angle() - angle();

         while (res < 0.0)
            res += 2.0 * PI;

         return res;
      }

      // Calculates the angle the edges and the x-axis.
      double angle() const
      {
         return p1.angle(p2);
      }

      // Apply a transform to an edge.
      edge_t apply(const transform_t& t) const
      {
         return edge_t(p1.apply(t), p2.apply(t));
      }

   private:
      constexpr edge_t(const point_t& p1, double order) : p1(p1), p2(), order(order) { }
      constexpr edge_t(const point_t& p1, const point_t& p2, double order) : p1(p1), p2(p2), order(order) { }
   };
}

#endif

// vim: sw=3 : sts=3 : et : sta : 
