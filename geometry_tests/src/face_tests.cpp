#include <dak/geometry/face.h>

#include <dak/geometry/tests/helpers.h>

#include <cmath>

#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace dak::geometry;

namespace geometry::tests
{
   TEST_CLASS(face_tests)
   {
   public:

      TEST_METHOD(face_faces_simple)
      {
         edges_map_t m1({
             edge_t(point_t(1., 2.), point_t(-3., -4.)),
             edge_t(point_t(-3., -4.), point_t(-3., 3.)),
             edge_t(point_t(-3., 3.), point_t(2., 3.)),
             edge_t(point_t(2., 3.), point_t(1., 2.)),
         });

         face_t::faces_t white, black, red, exteriors;
         face_t::make_faces(m1, white, black, red, exteriors);
         Assert::AreEqual<size_t>(2, white.size() + black.size());
         Assert::AreEqual<size_t>(0, exteriors.size());
         Assert::AreEqual<size_t>(4, white[0].points.size());
         Assert::AreEqual<size_t>(4, black[0].points.size());
      }

      TEST_METHOD(face_faces_cross)
      {
         edges_map_t m1({
             edge_t(point_t(-2., 0.), point_t(2., 0.)),
             edge_t(point_t(0., -3.), point_t(0., 3.)),
         });

         face_t::faces_t white, black, red, exteriors;
         face_t::make_faces(m1, white, black, red, exteriors);
         Assert::AreEqual<size_t>(0, white.size());
         Assert::AreEqual<size_t>(0, black.size());
         Assert::AreEqual<size_t>(0, exteriors.size());
         Assert::AreEqual<size_t>(1, red.size());
         Assert::AreEqual<size_t>(8, red[0].points.size());
      }
   };
}
