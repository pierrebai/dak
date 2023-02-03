#include <dak/geometry/edges_map.h>
#include <dak/geometry/intersect.h>
#include <dak/utility/text.h>

#include <algorithm>
#include <set>

namespace dak::geometry
{
   using utility::L;

   const edge_t edge_t::invalid;

   //#define DAK_GEOMETRY_MAP_INTERNAL_VERIFY

   ////////////////////////////////////////////////////////////////////////////
   //
   // edges_map_t.

   edges_map_t::edges_map_t(const edges_t& from_edges)
   {
      insert(from_edges);
   }

   bool edges_map_t::are_connected(const point_t& a, const point_t& b) const
   {
      const edge_t e(a, b);
      const auto iter = std::lower_bound(_sorted_edges.begin(), _sorted_edges.end(), e);
      return iter != _sorted_edges.end() && *iter == e;
   }

   bool edges_map_t::contains(const point_t& p) const
   {
      const auto iter = std::lower_bound(_sorted_edges.begin(), _sorted_edges.end(), edge_t::lowest_edge(p));
      return (iter != _sorted_edges.end() && iter->p1 == p);
   }

   bool edges_map_t::contains(const edge_t& e) const
   {
      const auto iter = std::lower_bound(_sorted_edges.begin(), _sorted_edges.end(), e);
      return iter != _sorted_edges.end() && *iter == e;
   }

   edges_map_t::range_t edges_map_t::outbounds(const point_t& p) const
   {
      const auto end = _sorted_edges.end();
      auto lower = std::lower_bound(_sorted_edges.begin(), end, edge_t::lowest_edge(p));
      while (lower != end && lower->p1 != p)
         ++lower;
      auto upper = lower;
      while (upper != end && upper->p1 == p)
         ++upper;
      return range_t(lower, upper);
   }

   std::pair<edge_t, edge_t> edges_map_t::before_after(const edge_t& e) const
   {
      const range_t conns = outbounds(e.p2);
      return before_after(conns, e);
   }

   std::pair<edge_t, edge_t> edges_map_t::before_after(const range_t& outbounds, const edge_t& e)
   {
      const auto iter = std::lower_bound(outbounds.begin(), outbounds.end(), e.twin());
      if (iter == outbounds.end())
         return std::pair<edge_t, edge_t>();

      const auto before = (iter == outbounds.begin()) ? *std::prev(outbounds.end()) : *std::prev(iter);
      const auto after = (iter == std::prev(outbounds.end())) ? *outbounds.begin() : *std::next(iter);
      return std::pair<edge_t, edge_t>(before, after);
   }

   const edge_t& edges_map_t::before(const edge_t& e) const
   {
      const range_t conns = outbounds(e.p2);
      return before(conns, e);
   }

   const edge_t& edges_map_t::before(const range_t& outbounds, const edge_t& e)
   {
      const auto iter = std::lower_bound(outbounds.begin(), outbounds.end(), e.twin());
      if (iter == outbounds.end())
         return edge_t::invalid;

      return (iter == outbounds.begin()) ? *std::prev(outbounds.end()) : *std::prev(iter);
   }

   const edge_t& edges_map_t::after(const edge_t& e) const
   {
      const range_t conns = outbounds(e.p2);
      return after(conns, e);
   }

   const edge_t& edges_map_t::after(const range_t& outbounds, const edge_t& e)
   {
      const auto iter = std::lower_bound(outbounds.begin(), outbounds.end(), e.twin());
      if (iter == outbounds.end())
         return edge_t::invalid;

      return (iter == std::prev(outbounds.end())) ? *(outbounds.begin()) : *std::next(iter);
   }

   const edge_t& edges_map_t::continuation(const edge_t& e) const
   {
      const range_t conns = outbounds(e.p2);
      return continuation(conns, e);
   }

   const edge_t& edges_map_t::continuation(const range_t& outbounds, const edge_t& e)
   {
      const auto iter = std::lower_bound(outbounds.begin(), outbounds.end(), e.twin());
      if (iter == outbounds.end())
         return edge_t::invalid;

      const ptrdiff_t delta = (outbounds.end() - outbounds.begin()) / 2;
      const auto opposite = ((iter - outbounds.begin()) >= delta) ? std::prev(iter, delta) : std::next(iter, delta);
      return *opposite;
   }

   void edges_map_t::remove(const point_t& p)
   {
      const range_t range_to_remove = outbounds(p);
      const edges_t to_remove = edges_t(range_to_remove.begin(), range_to_remove.end());
      _sorted_edges.erase(range_to_remove.begin(), range_to_remove.end());
      for (const auto e : to_remove)
      {
         remove(e.twin());
      }
   }

   void edges_map_t::remove(const edge_t& e)
   {
      auto i = std::lower_bound(_sorted_edges.begin(), _sorted_edges.end(), e);
      if (i != _sorted_edges.end() && *i == e)
         _sorted_edges.erase(i);
      i = std::lower_bound(_sorted_edges.begin(), _sorted_edges.end(), e.twin());
      if (i != _sorted_edges.end() && *i == e.twin())
         _sorted_edges.erase(i);
      internal_verify();
   }

   void edges_map_t::reserve(size_t edge_count)
   {
      _sorted_edges.reserve(edge_count);
   }

   void edges_map_t::begin_merge_non_overlapping()
   {
   }

   void edges_map_t::merge_non_overlapping(const edges_map_t& other)
   {
      _sorted_edges.insert(_sorted_edges.end(), other._sorted_edges.begin(), other._sorted_edges.end());
   }

   void edges_map_t::end_merge_non_overlapping()
   {
      internal_sort_edges();
      internal_verify();
   }

   void edges_map_t::merge(const edges_map_t& other)
   {
      std::vector<std::pair<edge_t, point_t>> temp_edge_intersections;
      temp_edge_intersections.reserve(_sorted_edges.size() + other._sorted_edges.size());
      for (const auto& new_edge : other._sorted_edges)
         if (new_edge.is_canonical())
            if (!contains(new_edge))
               internal_connect(new_edge, temp_edge_intersections);
      internal_add_intersections_and_sort(temp_edge_intersections);
      internal_verify();
   }

   void edges_map_t::insert(const edges_t& from_edges)
   {
      std::vector<std::pair<edge_t, point_t>> temp_edge_intersections;
      temp_edge_intersections.reserve(_sorted_edges.size() + from_edges.size());
      for (const auto& new_edge : from_edges)
      {
         if (new_edge.is_trivial())
            return;

         if (contains(new_edge))
            continue;

         temp_edge_intersections.clear();
         internal_connect(new_edge.canonical(), temp_edge_intersections);
         internal_add_intersections_and_sort(temp_edge_intersections);
      }
      internal_verify();
   }

   void edges_map_t::insert(const edge_t& new_edge)
   {
      if (new_edge.is_trivial())
         return;

      if (contains(new_edge))
         return;

      std::vector<std::pair<edge_t, point_t>> temp_edge_intersections;
      internal_connect(new_edge.canonical(), temp_edge_intersections);
      internal_add_intersections_and_sort(temp_edge_intersections);
      internal_verify();
   }

   void edges_map_t::connect(const point_t& p1, const point_t& p2)
   {
      insert(edge_t(p1, p2));
   }

   edges_map_t edges_map_t::simplify() const
   {
      edges_map_t simplified;

      std::set<edge_t> merged;

      auto find_other_edge = [](const range_t& connections, const edge_t& edge) -> edge_t
      {
         for (const edge_t& other_edge : connections)
         {
            if (other_edge.twin() == edge)
               continue;

            return other_edge.twin();
         }

         return edge;
      };

      for (edge_t edge : _sorted_edges)
      {
         if (!edge.is_canonical())
            continue;

         if (merged.count(edge))
            continue;

         while (true)
         {
            const range_t connections = outbounds(edge.p2);
            if (connections.size() != 2)
               break;

            const edge_t other_edge = find_other_edge(connections, edge);
            if (merged.count(other_edge.canonical()))
               break;

            const double angle = edge.angle(other_edge);
            if (!utility::near(angle, 0.0) && !utility::near(angle, geometry::PI))
               break;

            merged.insert(other_edge.canonical());
            merged.insert(edge);
            edge.p2 = other_edge.p2;
         }

         simplified.insert(edge);
      }

      return simplified;
   }

   edges_map_t& edges_map_t::apply_to_self(const transform_t& t)
   {
      for (auto& e : _sorted_edges)
         e = edge_t(e.p1.apply(t), e.p2.apply(t));
      internal_sort_edges();
      internal_verify();
      return *this;
   }

   edges_map_t edges_map_t::apply(const transform_t& t) const
   {
      edges_map_t other(*this);
      other.apply_to_self(t);
      return other;
   }

   void edges_map_t::internal_sort_edges()
   {
      std::sort(_sorted_edges.begin(), _sorted_edges.end());
   }

   // Split existing edges and record the intersections for each edge, old and new.
   void edges_map_t::internal_connect(const edge_t& new_edge, std::vector<std::pair<edge_t, point_t>>& temp_edge_intersections)
   {
      const point_t& new_p1 = new_edge.p1;
      const point_t& new_p2 = new_edge.p2;

      const auto new_min_max_x = std::minmax(new_p1.x, new_p2.x);
      const auto new_min_max_y = std::minmax(new_p1.y, new_p2.y);

      int intersection_count = 0;

      for (auto& my_edge : _sorted_edges)
      {
         if (!my_edge.is_canonical())
            continue;

         const point_t& my_p1 = my_edge.p1;
         const point_t& my_p2 = my_edge.p2;

         if (std::min(my_p1.x, my_p2.x) > new_min_max_x.second)
            break;

         if (std::max(my_p1.x, my_p2.x) < new_min_max_x.first)
            continue;

         if (std::min(my_p1.y, my_p2.y) > new_min_max_y.second)
            continue;

         if (std::max(my_p1.y, my_p2.y) < new_min_max_y.first)
            continue;

         const point_t ipt = intersect::intersect_within(new_p1, new_p2, my_p1, my_p2);

         if (ipt.is_invalid())
            continue;

         if (ipt != my_p1 && ipt != my_p2)
            temp_edge_intersections.emplace_back(my_edge, ipt);
         if (ipt != new_p1 && ipt != new_p2)
            temp_edge_intersections.emplace_back(new_edge, ipt);
         intersection_count++;
      }

      if (intersection_count == 0)
      {
         // If no intersection found, just add the new edge with an invalid intersection point.
         temp_edge_intersections.emplace_back(new_edge, point_t());
      }
   }

   void edges_map_t::internal_add_intersections_and_sort(std::vector<std::pair<edge_t, point_t>>& temp_edge_intersections)
   {
      // Sort intersections.
      std::sort(temp_edge_intersections.begin(), temp_edge_intersections.end());


      // We will build a new vector of sorted edges.
      // It will be filled by iterating over the existing sorted edges and the intersections
      // in parallel so that edges are inserted in already sorted order.
      edges_t new_sorted_canonical_edges;
      new_sorted_canonical_edges.reserve(_sorted_edges.size() + temp_edge_intersections.size());

      // Keep track of previous edge and point so we can detect when
      // we've finished splitting one particular edge.
      edge_t prev_edge;
      point_t prev_point;
      point_t last_point;

      auto inter_iter = temp_edge_intersections.begin();
      const auto inter_end = temp_edge_intersections.end();

      auto edges_iter = _sorted_edges.begin();
      const auto edges_end = _sorted_edges.end();

      while (true)
      {
         const bool valid_edges = (edges_iter != edges_end);
         const bool valid_inter = (inter_iter != inter_end);
         const bool do_edges = valid_edges && (!valid_inter || *edges_iter < inter_iter->first);
         if (do_edges)
         {
            const edge_t& old_edge = *edges_iter;
            if (old_edge.is_canonical())
            {
               new_sorted_canonical_edges.emplace_back(old_edge);
               new_sorted_canonical_edges.emplace_back(old_edge.twin());
            }
            ++edges_iter;
         }
         else if (valid_inter)
         {
            // Skip over sorted edge that is split, if any.
            if (valid_edges && *edges_iter == inter_iter->first)
            {
               ++edges_iter;
            }

            const edge_t& split_edge = inter_iter->first;
            const point_t& intersection = inter_iter->second;

            if (intersection.is_invalid())
            {
               // If the edge was not split, then it was a new edge
               // that didn't touch any existing edges.
               // Just add it straight to the edges map.
               new_sorted_canonical_edges.emplace_back(split_edge);
               new_sorted_canonical_edges.emplace_back(split_edge.twin());
            }
            else
            {
               // If the edge was split, we need to remove it and replace
               // it by new smaller edges.

               // First, check if we've changed which edge we're splitting.
               if (split_edge != prev_edge)
               {
                  // Finish any previous splitted edge.
                  if (!prev_point.is_invalid())
                  {
                     new_sorted_canonical_edges.emplace_back(prev_point, last_point);
                     new_sorted_canonical_edges.emplace_back(last_point, prev_point);
                  }
                  prev_edge = split_edge;
                  prev_point = split_edge.p1 < split_edge.p2 ? split_edge.p1 : split_edge.p2;
                  last_point = split_edge.p1 < split_edge.p2 ? split_edge.p2 : split_edge.p1;
               }

               // Split the input edge at every intersection. Beware that an edge might get split twice
               // if it is intersected by an end-point of the other edges map, which result in two identical
               // intersections.
               if (prev_point != intersection)
               {
                  new_sorted_canonical_edges.emplace_back(prev_point, intersection);
                  new_sorted_canonical_edges.emplace_back(intersection, prev_point);
               }
               prev_point = intersection;
            }
            ++inter_iter;
         }
         else
         {
            break;
         }
      }

      // Finish any previous splitted edge.
      if (!prev_point.is_invalid())
      {
         new_sorted_canonical_edges.emplace_back(prev_point, last_point);
         new_sorted_canonical_edges.emplace_back(last_point, prev_point);
      }

      _sorted_edges.swap(new_sorted_canonical_edges);
      internal_sort_edges();
      _sorted_edges.erase(std::unique(_sorted_edges.begin(), _sorted_edges.end()), _sorted_edges.end());
   }

   void edges_map_t::internal_verify() const
   {
      #ifdef DAK_GEOMETRY_MAP_INTERNAL_VERIFY
         verify_and_throw();
      #endif
   }

   void edges_map_t::verify_and_throw() const
   {
      if (verify().size() > 0)
         throw std::exception(L::t("Map is invalid."));
   }

   std::vector<std::wstring> edges_map_t::verify() const
   {
      std::vector<std::wstring> errors;

      wchar_t error[200];

      // Make sure there are no trivial edges.
      for (const auto& e : _sorted_edges)
      {
         if (e.p1 == e.p2)
         {
            _snwprintf_s(error, sizeof(error)/sizeof(error[0]), L::t(L"Trivial edge %f/%f - %f/%f."), e.p1.x, e.p1.y, e.p2.x, e.p2.y);
            errors.emplace_back(error);
         }

         if (e.p1.is_invalid() || e.p2.is_invalid())
         {
            _snwprintf_s(error, sizeof(error) / sizeof(error[0]), L::t(L"Invalid edge %f/%f - %f/%f."), e.p1.x, e.p1.y, e.p2.x, e.p2.y);
            errors.emplace_back(error);
         }
      }

      // Make sure the edges are in sorted order.
      {
         edge_t prev;
         for (const auto& e : _sorted_edges)
         {
            if (!prev.is_invalid())
            {
               if (e < prev)
               {
                  _snwprintf_s(error, sizeof(error) / sizeof(error[0]), L::t(L"Canonical edges are not sorted."));
                  errors.emplace_back(error);
               }
            }
            prev = e;
         }
      }

      return errors;
   }
}

// vim: sw=3 : sts=3 : et : sta : 
