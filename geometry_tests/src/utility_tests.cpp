#include <dak/geometry/utility.h>
#include <dak/geometry/point.h>
#include <dak/geometry/constants.h>

#include <dak/geometry/tests/helpers.h>

#include <CppUnitTest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace dak::geometry;
using namespace dak::utility;

namespace dak::geometry::tests
{
   TEST_CLASS(utility_tests)
   {
   public:

      TEST_METHOD(utility_near)
      {
         Assert::IsTrue(near_zero(point_t::origin()));
         Assert::IsTrue(near_zero(point_t(0., 0.)));
         Assert::IsTrue(near_zero(point_t(dak::utility::TOLERANCE, 0.)));
         Assert::IsTrue(near_zero(point_t(0., dak::utility::TOLERANCE)));
         Assert::IsTrue(near_zero(point_t(dak::utility::TOLERANCE/2, dak::utility::TOLERANCE/2)));

         Assert::IsFalse(near_zero(point_t(dak::utility::TOLERANCE * dak::utility::TOLERANCE + dak::utility::TOLERANCE, 0.)));
         Assert::IsFalse(near_zero(point_t(0., dak::utility::TOLERANCE * dak::utility::TOLERANCE + dak::utility::TOLERANCE)));
         Assert::IsFalse(near_zero(point_t(dak::utility::TOLERANCE * dak::utility::TOLERANCE + dak::utility::TOLERANCE, 0.)));
         Assert::IsFalse(near_zero(point_t(dak::utility::TOLERANCE * 1.1, 0.)));
         Assert::IsFalse(near_zero(point_t(0., dak::utility::TOLERANCE * 1.1)));
         Assert::IsFalse(near_zero(point_t(dak::utility::TOLERANCE, dak::utility::TOLERANCE)));
         Assert::IsFalse(near_zero(point_t(dak::utility::TOLERANCE, dak::utility::TOLERANCE * 2)));
         Assert::IsFalse(near_zero(point_t(dak::utility::TOLERANCE * 2, dak::utility::TOLERANCE * 2)));

         Assert::IsTrue(near(point_t::origin(), point_t::origin()));
         Assert::IsTrue(near(point_t(0., 0.), point_t(0., 0.)));
         Assert::IsTrue(near(point_t(1., 1.), point_t(1., 1.)));
         Assert::IsTrue(near(point_t(0., 0.), point_t(dak::utility::TOLERANCE, 0.)));
         Assert::IsTrue(near(point_t(0., 0.), point_t(0., dak::utility::TOLERANCE)));
         Assert::IsTrue(near(point_t(0., 0.), point_t(dak::utility::TOLERANCE/2, dak::utility::TOLERANCE/2)));

         Assert::IsFalse(near(point_t(0., 0.), point_t(dak::utility::TOLERANCE * 1.1, 0.)));
         Assert::IsFalse(near(point_t(0., 0.), point_t(0., dak::utility::TOLERANCE * 1.1)));
         Assert::IsFalse(near(point_t(0., 0.), point_t(dak::utility::TOLERANCE * 2, dak::utility::TOLERANCE)));
         Assert::IsFalse(near(point_t(0., 0.), point_t(dak::utility::TOLERANCE, dak::utility::TOLERANCE * 2)));
         Assert::IsFalse(near(point_t(0., 0.), point_t(dak::utility::TOLERANCE * 2, dak::utility::TOLERANCE * 2)));
         Assert::IsFalse(near(point_t(0., 0.), point_t(dak::utility::TOLERANCE * dak::utility::TOLERANCE + dak::utility::TOLERANCE, 0.)));
         Assert::IsFalse(near(point_t(0., 0.), point_t(0., dak::utility::TOLERANCE * dak::utility::TOLERANCE + dak::utility::TOLERANCE)));

         const double tolerance = 0.1;
         Assert::IsTrue(near(point_t::origin(), point_t::origin(), tolerance * tolerance));
         Assert::IsTrue(near(point_t(0., 0.), point_t(0., 0.), tolerance * tolerance));
         Assert::IsTrue(near(point_t(1., 1.), point_t(1., 1.), tolerance * tolerance));
         Assert::IsTrue(near(point_t(0., 0.), point_t(tolerance, 0.), tolerance * tolerance));
         Assert::IsTrue(near(point_t(0., 0.), point_t(0., tolerance), tolerance * tolerance));
         Assert::IsTrue(near(point_t(0., 0.), point_t(tolerance/2, tolerance/2), tolerance * tolerance));

         Assert::IsFalse(near(point_t(0., 0.), point_t(tolerance * 2, 0.), tolerance * tolerance));
         Assert::IsFalse(near(point_t(0., 0.), point_t(0., tolerance * 2), tolerance * tolerance));
         Assert::IsFalse(near(point_t(0., 0.), point_t(tolerance, tolerance), tolerance * tolerance));
         Assert::IsFalse(near(point_t(0., 0.), point_t(tolerance * 2, tolerance), tolerance * tolerance));
         Assert::IsFalse(near(point_t(0., 0.), point_t(tolerance, tolerance * 2), tolerance * tolerance));
         Assert::IsFalse(near(point_t(0., 0.), point_t(tolerance * 2, tolerance * 2), tolerance * tolerance));
         Assert::IsFalse(near(point_t(0., 0.), point_t(tolerance * tolerance + tolerance, 0.), tolerance * tolerance));
         Assert::IsFalse(near(point_t(0., 0.), point_t(0., tolerance * tolerance + tolerance), tolerance * tolerance));
      }

      TEST_METHOD(utility_center)
      {
         const std::vector<point_t> pts({ point_t(1., 1.), point_t(-1., 1.), point_t(-1., -1.), point_t(1., -1.) });

         Assert::AreEqual(point_t(0., 0.), center(pts));

         const std::vector<point_t> new_pts = translate(pts, point_t(-3., 5.));

         Assert::AreEqual(point_t(-3., 5.), center(new_pts));
      }

      TEST_METHOD(utility_arc)
      {
         Assert::AreEqual(point_t( 1.,  0.), get_arc(0));
         Assert::AreEqual(point_t( 0.,  1.), get_arc(0.25));
         Assert::AreEqual(point_t(-1.,  0.), get_arc(0.5));
         Assert::AreEqual(point_t( 0., -1.), get_arc(0.75));
      }

      TEST_METHOD(utility_colinear)
      {
         Assert::IsTrue(is_colinear(point_t(0., 0.), point_t(0., 1.), point_t(0., 2.)));
         Assert::IsTrue(is_colinear(point_t(10., 0.), point_t(10., 1.), point_t(10., 2.)));
         Assert::IsTrue(is_colinear(point_t(0., 0.), point_t(1., 0.), point_t(2., 0.)));
         Assert::IsTrue(is_colinear(point_t(10., 0.), point_t(11., 0.), point_t(12., 0.)));
         Assert::IsTrue(is_colinear(point_t(10., 10.), point_t(11., 10.), point_t(12., 10.)));
         Assert::IsTrue(is_colinear(point_t(10., 10.), point_t(0., 0.), point_t(-12., -12.)));
         Assert::IsTrue(is_colinear(point_t(2., 10.), point_t(0., 0.), point_t(-2., -10.)));
         Assert::IsTrue(is_colinear(point_t(1., 2.), point_t(3., 4.), point_t(5., 6.)));

         Assert::IsFalse(is_colinear(point_t(1., 2.), point_t(3., 4.), point_t(5., 7.)));
         Assert::IsFalse(is_colinear(point_t(2., 2.), point_t(0., 0.), point_t(-2., 0.)));
         Assert::IsFalse(is_colinear(point_t(1., 2.), point_t(2., 3.), point_t(3., 2.)));
         Assert::IsFalse(is_colinear(point_t(1., 2.), point_t(2., 1.), point_t(3., 2.)));
      }
   };
}
