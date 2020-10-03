#pragma once

#ifndef DAK_GEOMETRY_FACE_H
#define DAK_GEOMETRY_FACE_H

#include <dak/geometry/edges_map.h>
#include <dak/geometry/polygon.h>

#include <vector>

namespace dak::geometry
{
   ////////////////////////////////////////////////////////////////////////////
   //
   // A face is a loop of edges.

   namespace face_t
   {
      // Create faces_t from a map.
      typedef std::vector<polygon_t> faces_t;

      void make_faces(const edges_map_t& m, faces_t& white, faces_t& black, faces_t& red, faces_t& exteriors);

      // Verify if there are any errors in the faces_t.
      // Return the list of errors.
      std::vector<std::wstring> verify(const edges_map_t& m, const faces_t& white, const faces_t& black, const faces_t& red, const faces_t& exteriors);

      // Verify if there are any errors in the faces_t.
      // Throw an exception if there is at least on error.
      void verify_and_throw(const edges_map_t& m, const faces_t& white, const faces_t& black, const faces_t& red, const faces_t& exteriors);
   }
}

#endif

// vim: sw=3 : sts=3 : et : sta : 
