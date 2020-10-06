#include <dak/geometry/face.h>
#include <dak/utility/text.h>

#include <algorithm>
#include <numeric>
#include <deque>
#include <map>

namespace dak::geometry
{
   using utility::L;

   namespace
   {
      //#define DAK_GEOMETRY_FACE_FACES_INTERNAL_VERIFY

      void automatic_verify(const edges_map_t& map, const face_t::faces_t& white, const face_t::faces_t& black, const face_t::faces_t& red, const face_t::faces_t& exteriors)
      {
         #ifdef DAK_GEOMETRY_FACE_FACES_INTERNAL_VERIFY
            face::verify_and_throw(map, white, black, red, exteriors);
         #endif
      }

      std::vector<std::wstring> internal_verify(const edges_map_t& map, const face_t::faces_t& white, const face_t::faces_t& black, const face_t::faces_t& red, const face_t::faces_t& exteriors)
      {
         std::vector<std::wstring> errors;

         // Unfortunately, some tilings are degenrate with faces_t that are simple lines and cause checks to fail.
         // Don't verify those tilings.
         const std::vector<polygon_t>* all_faces[4] = { &white, &black, &red, &exteriors };
         for (const auto& faces_t : all_faces)
         {
            for (const polygon_t& face : *faces_t)
            {
               if (face.points.size() < 3)
               {
                  return errors;
               }
            }
         }
            
         wchar_t error[200];

         // The number of white and black face times their number of edges should be equal.
         const size_t white_edges = std::accumulate(white.begin(), white.end(), size_t(0), [](size_t val, const polygon_t& f) { return f.points.size() + val; });
         const size_t black_edges = std::accumulate(black.begin(), black.end(), size_t(0), [](size_t val, const polygon_t& f) { return f.points.size() + val; });
         const size_t red_edges = std::accumulate(red.begin(), red.end(), size_t(0), [](size_t val, const polygon_t& f) { return f.points.size() + val; });
         const size_t exterior_edges = std::accumulate(exteriors.begin(), exteriors.end(), size_t(0), [](size_t val, const polygon_t& f) { return f.points.size() + val; });
         if (std::abs(long(white_edges - black_edges)) > red_edges + exterior_edges)
         {
            _snwprintf_s(error, sizeof(error) / sizeof(error[0]), L::t(L"White faces_t contains more edges than black faces_t (%ld vs %ld vs %ld vs %ld)."),
                           long(white_edges), long(black_edges), long(red_edges), long(exterior_edges));
            errors.emplace_back(error);
         }

         // Make sure there are exactly as many points in the faces_t as in the map.
         const size_t map_edge_count = map.all().size();
         const size_t faces_edge_count = white_edges + black_edges + red_edges + exterior_edges;
         if (map_edge_count != faces_edge_count)
         {
            _snwprintf_s(error, sizeof(error) / sizeof(error[0]), L::t(L"Face and map do not contain the same number of points: %ld vs. %ld."),
                           long(faces_edge_count), long(map_edge_count));
            errors.emplace_back(error);
         }

         // Note: there used to be a check for non-duplicate points, but polygons sometimes have bow-tie forms.

         return errors;
      }

   }

   void face_t::make_faces(const edges_map_t& m, faces_t& white, faces_t& black, faces_t& red, faces_t& exteriors)
   {
      // The edges we need to process.
      //
      // Because the edges are sorted by their p1, we can easily find all edges around the same point
      // as another edge_t by "looking around" the address of the edge_t in the vector.
      const std::vector<edge_t>& all_edges = m.all();
      if (all_edges.empty())
         return;

      const edge_t* const first_edge = &all_edges.front();
      const edge_t* const last_edge = &all_edges.back();

      auto edge_index = [first_edge=first_edge](const edge_t* edge) -> size_t
      {
         return edge - first_edge;
      };

      // Crossings where this is an odd number of edges cannot propagate the checker-board
      // pattern properly. We will ignore them during propagation to avoid completely random
      // checker-boards.
      auto is_p1_odd_crossing = [first_edge=first_edge,last_edge=last_edge] (const edge_t* e) -> bool
      {
         const point_t& p1 = e->p1;
         int count = 1;
         for (const edge_t* pe = e - 1; pe >= first_edge && pe->p1 == p1; --pe)
            count += 1;
         for (const edge_t* ne = e + 1; ne <= last_edge  && ne->p1 == p1; ++ne)
            count += 1;
         return (count & 1) == 1;
      };

      auto next_edge_around_p1 = [first_edge=first_edge,last_edge=last_edge] (const edge_t* e) -> const edge_t*
      {
         const point_t& p1 = e->p1;
         if (e < last_edge && (e+1)->p1 == p1)
            return (e + 1);
         while (e > first_edge)
            if ((e - 1)->p1 == p1)
               --e;
            else
               break;
         return e;
      };

      auto find_twin = [first_edge=first_edge,last_edge=last_edge] (const edge_t twin) -> const edge_t*
      {
         const edge_t* iter = std::lower_bound(first_edge, last_edge, twin);
         return iter;
      };

      // Keeping track of which edge_t needs to be done and which are already done.
      std::deque<const edge_t *> edges_todo;
      std::vector<bool> done_edges(all_edges.size(), false);
      std::vector<bool> seen_edges(all_edges.size(), false);
      std::vector<bool> edge_colors(all_edges.size(), false);

      auto add_point = [&edge_index, &done_edges, &seen_edges, &is_p1_odd_crossing](polygon_t& poly, const edge_t* cur_edge, size_t cur_edge_index) -> bool
      {
         poly.points.emplace_back(cur_edge->p1);

         done_edges[cur_edge_index] = true;
         seen_edges[cur_edge_index] = true;

         return is_p1_odd_crossing(cur_edge);
      };

      for (const edge_t* edge_iter = first_edge; edge_iter != last_edge; ++edge_iter)
      {
         const size_t edge_iter_index = edge_index(edge_iter);
         if (done_edges[edge_iter_index])
            continue;
         seen_edges[edge_iter_index] = true;

         edges_todo.emplace_back(edge_iter);

         while (edges_todo.size() > 0)
         {
            const edge_t* cur_edge = edges_todo.front();
            size_t cur_index = edge_index(cur_edge);
            const bool is_white = edge_colors[cur_index];
            edges_todo.pop_front();

            if (done_edges[cur_index])
               continue;

            polygon_t new_face;
            const point_t until_point = cur_edge->p1;
            bool face_has_odd_crossing = add_point(new_face, cur_edge, cur_index);
            while (cur_edge->p2 != until_point)
            {
               const edge_t* twin = find_twin(cur_edge->twin());
               const size_t twin_index = edge_index(twin);
               if (!done_edges[twin_index] && !seen_edges[twin_index])
               {
                  edge_colors[edge_index(twin)] = !is_white;
                  seen_edges[twin_index] = true;
                  edges_todo.emplace_back(twin);
               }

               const edge_t* next_edge = next_edge_around_p1(twin);
               if (new_face.points.size() > 50000)
                  break;
               cur_edge = next_edge;
               cur_index = edge_index(next_edge);
               face_has_odd_crossing |= add_point(new_face, cur_edge, cur_index);
            }

            // Note: we don't want to have the exterior polygon!
            // TODO: better detection of the exterior polygon than using the number of points...
            if (new_face.points.size() > 50)
            {
               exteriors.emplace_back(new_face);
               continue;
            }

            // Odd-crossing faces_t are not part of the black/white division.
            if (face_has_odd_crossing)
            {
               red.emplace_back(new_face);
               continue;
            }

            if (is_white)
               white.emplace_back(new_face);
            else
               black.emplace_back(new_face);
         }
      }

      automatic_verify(m, white, black, red, exteriors);
   }

   std::vector<std::wstring> face_t::verify(const edges_map_t& map, const faces_t& white, const faces_t& black, const faces_t& red, const faces_t& exteriors)
   {
      return internal_verify(map, white, black, red, exteriors);
   }

   void face_t::verify_and_throw(const edges_map_t& map, const faces_t& white, const faces_t& black, const faces_t& red, const faces_t& exteriors)
   {
      const auto errors = verify(map, white, black, red, exteriors);
      if (errors.size() > 0)
         throw std::exception(L::t("Faces are invalid."));
   }

}

// vim: sw=3 : sts=3 : et : sta : 
