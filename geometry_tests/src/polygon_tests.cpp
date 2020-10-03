#include <dak/geometry/polygon.h>
#include <dak/geometry/transform.h>
#include <dak/geometry/constants.h>

#include <dak/geometry/tests/helpers.h>

#include <cmath>

#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace dak::geometry;

namespace geometry::tests
{
   TEST_CLASS(polygon_tests)
   {
   public:

      TEST_METHOD(polygon_constructors_and_comparisons)
      {
         const polygon_t p1;

         Assert::IsTrue(p1.is_invalid());
         Assert::IsTrue(polygon_t() == p1);
         Assert::IsTrue(p1.center().is_invalid());

         const polygon_t p2({ point_t(1., 2.), point_t(-3., -4.), point_t(5, -6) });
         Assert::AreEqual( 1., p2.points[0].x);
         Assert::AreEqual( 2., p2.points[0].y);
         Assert::AreEqual(-3., p2.points[1].x);
         Assert::AreEqual(-4., p2.points[1].y);
         Assert::AreEqual( 5., p2.points[2].x);
         Assert::AreEqual(-6., p2.points[2].y);
         Assert::AreEqual(point_t(1., -8./3), p2.center());

         Assert::AreNotEqual(p1, p2);
         Assert::AreEqual(p2, p2);
         Assert::AreNotEqual(polygon_t(), p2);
         Assert::IsFalse(p2.is_invalid());
         Assert::IsTrue(p1 != p2);
         Assert::IsTrue(polygon_t() != p2);

         const polygon_t p3({ point_t(2., 1.), point_t(5., 7.), point_t(3., 6.) });
         Assert::AreEqual(2., p3.points[0].x);
         Assert::AreEqual(1., p3.points[0].y);
         Assert::AreEqual(5., p3.points[1].x);
         Assert::AreEqual(7., p3.points[1].y);
         Assert::AreEqual(3., p3.points[2].x);
         Assert::AreEqual(6., p3.points[2].y);
         Assert::AreEqual(point_t(10./3, 14. / 3), p3.center());

         Assert::AreNotEqual(p1, p3);
         Assert::AreNotEqual(p2, p3);
         Assert::AreEqual(p3, p3);
         Assert::AreNotEqual(polygon_t(), p3);
         Assert::IsFalse(p3.is_invalid());
         Assert::IsTrue(p1 != p3);
         Assert::IsTrue(p2 != p3);
         Assert::IsTrue(polygon_t() != p3);

         const polygon_t p4(p3);
         Assert::AreEqual(2., p4.points[0].x);
         Assert::AreEqual(1., p4.points[0].y);
         Assert::AreEqual(5., p4.points[1].x);
         Assert::AreEqual(7., p4.points[1].y);
         Assert::AreEqual(3., p4.points[2].x);
         Assert::AreEqual(6., p4.points[2].y);

         Assert::AreNotEqual(p1, p4);
         Assert::AreNotEqual(p2, p4);
         Assert::AreEqual(p3, p4);
         Assert::AreEqual(p4, p4);
         Assert::AreNotEqual(polygon_t(), p4);
         Assert::IsFalse(p4.is_invalid());
         Assert::IsTrue(p1 != p4);
         Assert::IsTrue(p2 != p4);
         Assert::IsTrue(p3 == p4);
         Assert::IsTrue(polygon_t() != p4);
      }

      TEST_METHOD(polygon_calculations)
      {
         polygon_t p1({ point_t(3., 3.), point_t(3., -3.), point_t(-3., -3.), point_t(-3., 3.), });

         Assert::AreEqual(36., p1.area());
         Assert::AreEqual(24., p1.perimeter());
         Assert::AreEqual(18., p1.perimeter(false));
         Assert::AreEqual(point_t(0, 0), p1.center());

         Assert::IsTrue(p1.is_inside(point_t::origin()));
         Assert::IsTrue(p1.is_inside(point_t::unit_x()));
         Assert::IsTrue(p1.is_inside(point_t::unit_y()));
         Assert::IsTrue(p1.is_inside(point_t(1., -1.)));

         Assert::IsFalse(p1.is_inside(point_t(1., -4.)));
         Assert::IsFalse(p1.is_inside(point_t(3., -4.)));
         Assert::IsFalse(p1.is_inside(point_t(4., 2.)));
         Assert::IsFalse(p1.is_inside(point_t(100., -400.)));
      }

      TEST_METHOD(polygon_regular)
      {
         // Two points or less is always true.
         {
            const polygon_t p1;
            Assert::IsTrue(p1.is_regular());
         }

         {
            const polygon_t p2({ point_t(1., 2.) });
            Assert::IsTrue(p2.is_regular());
            Assert::AreEqual(point_t(1., 2.), p2.center());
         }

         {
            const polygon_t p3({ point_t(-1., 2.), point_t(7., 2.) });
            Assert::IsTrue(p3.is_regular());
            Assert::AreEqual(point_t(3., 2), p3.center());
         }

         {
            // Four points forming a square around the origin is true.
            const polygon_t p4({ point_t( 1.,  1.), point_t(-1.,  1.),
                               point_t(-1., -1.), point_t( 1., -1.) });
            Assert::IsTrue(p4.is_regular());
            Assert::AreEqual(point_t(0., 0), p4.center());

            // Four points forming a square around the another point_t is true.
            const polygon_t p5( p4.apply( transform_t::translate( point_t(-4, 12) ) ) );
            Assert::AreEqual(point_t(-4., 12), p5.center());

            Assert::IsTrue(p5.is_regular());

            // Four points forming a square around the another point_t is true.
            const polygon_t p6( p4.apply( transform_t::rotate( point_t(-2, 3), PI / 5 ) ) );

            Assert::IsTrue(p6.is_regular());
         }

         {
            // Irregular triangle.
            polygon_t p7({ point_t(-1., 2.), point_t(7., 2.), point_t(4., 6.) });

            Assert::IsFalse(p7.is_regular());
         }

         {
            // Four points forming a losange around the origin is false.
            polygon_t p4({ point_t(1., 1.), point_t(-2., 1.), point_t(-1., -1.), point_t(2., -1.) });

            Assert::IsFalse(p4.is_regular());
         }

         // Regular polygon_t should be regular.
         for (int sides = 3; sides < 20; ++sides)
         {
            polygon_t rp = polygon_t::make_regular(sides);

            Assert::IsTrue(rp.is_regular());
            Assert::AreEqual(point_t(0., 0), rp.center());

            Assert::IsTrue(rp.apply(transform_t::translate(point_t(-4, 12))).is_regular());
            Assert::IsTrue(rp.apply(transform_t::rotate(point_t(-2, 3), PI / 5)).is_regular());
         }

         // Translated regular polygon_t should be regular.
         for (int sides = 3; sides < 20; ++sides)
         {
            const polygon_t rp(polygon_t::make_regular(sides).apply(transform_t::translate(point_t(-4, 12))));

            Assert::IsTrue(rp.is_regular());
            Assert::AreEqual(point_t(-4., 12), rp.center());
         }
      }

      TEST_METHOD(polygon_transform)
      {
         {
            const polygon_t p1({ point_t(1., 2.), point_t(-3., -4.) });

            Assert::AreEqual(polygon_t({ point_t(-2., 1.), point_t(4., -3.) }), p1.apply(transform_t::rotate(PI / 2)));
            Assert::AreEqual(polygon_t({ point_t(-1., -2.), point_t(3., 4.) }), p1.apply(transform_t::rotate(PI)));
            Assert::AreEqual(polygon_t({ point_t(2., -1.), point_t(-4., 3.) }), p1.apply(transform_t::rotate(3 * PI / 2)));
            Assert::AreEqual(polygon_t({ point_t(1., 2.), point_t(-3., -4.) }), p1.apply(transform_t::rotate(2 * PI)));
         }

         {
            Assert::AreEqual(polygon_t({ point_t::origin(), point_t(0., 1.) }), polygon_t({ point_t::origin(), point_t::unit_x() }).apply(transform_t::rotate(PI / 2)));
            Assert::AreEqual(polygon_t({ point_t::origin(), point_t(-1., 0.) }), polygon_t({ point_t::origin(), point_t::unit_x() }).apply(transform_t::rotate(PI)));
            Assert::AreEqual(polygon_t({ point_t::origin(), point_t(0., -1.) }), polygon_t({ point_t::origin(), point_t::unit_x() }).apply(transform_t::rotate(3 * PI / 2)));
            Assert::AreEqual(polygon_t({ point_t::origin(), point_t::unit_x() }), polygon_t({ point_t::origin(), point_t::unit_x() }).apply(transform_t::rotate(2 * PI)));

            Assert::AreEqual(polygon_t({ point_t::origin(), point_t(std::sqrt(2.) / 2., std::sqrt(2.) / 2.) }), polygon_t({ point_t::origin(), point_t::unit_x() }).apply(transform_t::rotate(PI / 4)));
         }

         {
            const polygon_t p1({ point_t(1., 2.), point_t(-3., -4.) });

            Assert::AreEqual(polygon_t({ point_t(3., 5.), point_t(-1., -1.) }), p1.apply(transform_t::translate(2., 3.)));
            Assert::AreEqual(polygon_t({ point_t(-2., -5.), point_t(-6., -11.) }), p1.apply(transform_t::translate(point_t(-3., -7.))));
         }

         {
            const polygon_t p1({ point_t(1., 2.), point_t(-3., -4.) });

            Assert::AreEqual(polygon_t({ point_t(2., 4.), point_t(-6., -8.) }), p1.apply(transform_t::scale(2.)));
            Assert::AreEqual(polygon_t({ point_t(-3., -14.), point_t(9., 28.) }), p1.apply(transform_t::scale(-3., -7.)));
         }
      }
   };
}
