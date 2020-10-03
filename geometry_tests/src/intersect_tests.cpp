#include <dak/geometry/intersect.h>
#include <dak/geometry/transform.h>
#include <dak/geometry/constants.h>

#include <dak/geometry/tests/helpers.h>

#include <cmath>

#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace dak::geometry;

namespace geometry::tests
{
   TEST_CLASS(intersect_tests)
   {
   public:

      TEST_METHOD(stay_on_units_tests)
      {
         Assert::AreEqual(point_t::unit_x(), intersect::stay_on_units(point_t::unit_x()));
         Assert::AreEqual(point_t::unit_y(), intersect::stay_on_units(point_t::unit_y()));
         Assert::AreEqual(point_t::origin(), intersect::stay_on_units(point_t::origin()));

         Assert::AreEqual(point_t(1., 1.), intersect::stay_on_units(point_t(1., 1.)));

         Assert::AreEqual(point_t::invalid, intersect::stay_on_units(point_t(2., 1.)));
         Assert::AreEqual(point_t::invalid, intersect::stay_on_units(point_t(0., 2.)));
      }

      TEST_METHOD(stay_near_units_tests)
      {
         Assert::AreEqual(point_t::unit_x(), intersect::stay_near_units(point_t::unit_x()));
         Assert::AreEqual(point_t::unit_y(), intersect::stay_near_units(point_t::unit_y()));
         Assert::AreEqual(point_t::origin(), intersect::stay_near_units(point_t::origin()));

         Assert::AreEqual(point_t(1., 1.), intersect::stay_near_units(point_t(1., 1.)));

         Assert::AreEqual(point_t::invalid, intersect::stay_near_units(point_t(2., 1.)));
         Assert::AreEqual(point_t::invalid, intersect::stay_near_units(point_t(0., 2.)));

         Assert::AreEqual(point_t(1.2, 1.), intersect::stay_near_units(point_t(1.2, 1.)));
         Assert::AreEqual(point_t(1., 1.2), intersect::stay_near_units(point_t(1., 1.2)));

         Assert::AreEqual(point_t::invalid, intersect::stay_near_units(point_t(1., 1.21)));
         Assert::AreEqual(point_t::invalid, intersect::stay_near_units(point_t(1.21, 1.)));
      }

      TEST_METHOD(intersection_tests)
      {
         // Parallel
         Assert::AreEqual(point_t::invalid, intersect::intersect(point_t::origin(), point_t::unit_x(), point_t::origin(), point_t::unit_x()));
         Assert::AreEqual(point_t::invalid, intersect::intersect(point_t(0, 1), point_t(0, 4), point_t(3, 3), point_t(3, 7)));
         Assert::AreEqual(point_t::invalid, intersect::intersect(point_t(3, 1), point_t(9, 1), point_t(3, 3), point_t(9, 3)));

         // Barely touching.
         Assert::AreEqual(point_t::origin(), intersect::intersect(point_t::origin(), point_t::unit_x(), point_t::origin(), point_t::unit_y()));
         Assert::AreEqual(point_t(1, 1), intersect::intersect(point_t(1, 1), point_t(22, 32), point_t(67, -12), point_t(1, 1)));

         // Perpendicular, but not touching.
         Assert::AreEqual(point_t::invalid, intersect::intersect(point_t(3, 1), point_t(9, 1), point_t(5, 2), point_t(5, 6)));

         // Near miss.
         Assert::AreEqual(point_t::invalid, intersect::intersect(point_t(3, 1), point_t(9, 1), point_t(5, 1.0001), point_t(5, 2)));
         Assert::AreEqual(point_t::invalid, intersect::intersect(point_t(3, 2), point_t(9, 2), point_t(9.2, -2), point_t(9.2, 6)));

         // Crossing.
         Assert::AreEqual(point_t(5, 1), intersect::intersect(point_t(3, 1), point_t(9, 1), point_t(5, -2), point_t(5, 6)));
         Assert::AreEqual(point_t::origin(), intersect::intersect(point_t(1, 1), point_t(-1, -1), point_t(5, -5), point_t(-5, 5)));
      }

      TEST_METHOD(near_intersection_tests)
      {
         // Parallel
         Assert::AreEqual(point_t::invalid, intersect::intersect_near(point_t::origin(), point_t::unit_x(), point_t::origin(), point_t::unit_x()));
         Assert::AreEqual(point_t::invalid, intersect::intersect_near(point_t(0, 1), point_t(0, 4), point_t(3, 3), point_t(3, 7)));
         Assert::AreEqual(point_t::invalid, intersect::intersect_near(point_t(3, 1), point_t(9, 1), point_t(3, 3), point_t(9, 3)));

         // Barely touching.
         Assert::AreEqual(point_t::origin(), intersect::intersect_near(point_t::origin(), point_t::unit_x(), point_t::origin(), point_t::unit_y()));
         Assert::AreEqual(point_t(1, 1), intersect::intersect_near(point_t(1, 1), point_t(22, 32), point_t(67, -12), point_t(1, 1)));

         // Perpendicular, but not touching.
         Assert::AreEqual(point_t::invalid, intersect::intersect_near(point_t(3, 1), point_t(9, 1), point_t(5, 2), point_t(5, 6)));

         // Near miss.
         Assert::AreEqual(point_t(5, 1), intersect::intersect_near(point_t(3, 1), point_t(9, 1), point_t(5, 1.0001), point_t(5, 2)));
         Assert::AreEqual(point_t(9.2, 2), intersect::intersect_near(point_t(3, 2), point_t(9, 2), point_t(9.2, -2), point_t(9.2, 6)));

         // Crossing.
         Assert::AreEqual(point_t(5, 1), intersect::intersect_near(point_t(3, 1), point_t(9, 1), point_t(5, -2), point_t(5, 6)));
         Assert::AreEqual(point_t::origin(), intersect::intersect_near(point_t(1, 1), point_t(-1, -1), point_t(5, -5), point_t(-5, 5)));
      }

      TEST_METHOD(true_intersection_tests)
      {
         // Parallel
         Assert::AreEqual(point_t::invalid, intersect::intersect_within(point_t::origin(), point_t::unit_x(), point_t::origin(), point_t::unit_x()));
         Assert::AreEqual(point_t::invalid, intersect::intersect_within(point_t(0, 1), point_t(0, 4), point_t(3, 3), point_t(3, 7)));
         Assert::AreEqual(point_t::invalid, intersect::intersect_within(point_t(3, 1), point_t(9, 1), point_t(3, 3), point_t(9, 3)));

         // Barely touching.
         Assert::AreEqual(point_t::invalid, intersect::intersect_within(point_t::origin(), point_t::unit_x(), point_t::origin(), point_t::unit_y()));
         Assert::AreEqual(point_t::invalid, intersect::intersect_within(point_t(1, 1), point_t(22, 32), point_t(67, -12), point_t(1, 1)));

         // Perpendicular, but not touching.
         Assert::AreEqual(point_t::invalid, intersect::intersect_within(point_t(3, 1), point_t(9, 1), point_t(5, 2), point_t(5, 6)));

         // Near miss.
         Assert::AreEqual(point_t::invalid, intersect::intersect_within(point_t(3, 1), point_t(9, 1), point_t(5, 1.0001), point_t(5, 2)));
         Assert::AreEqual(point_t::invalid, intersect::intersect_within(point_t(3, 2), point_t(9, 2), point_t(9.2, -2), point_t(9.2, 6)));

         // Crossing.
         Assert::AreEqual(point_t(5, 1), intersect::intersect_within(point_t(3, 1), point_t(9, 1), point_t(5, -2), point_t(5, 6)));
         Assert::AreEqual(point_t::origin(), intersect::intersect_within(point_t(1, 1), point_t(-1, -1), point_t(5, -5), point_t(-5, 5)));
      }

   };
}
