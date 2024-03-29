#include <dak/geometry/rectangle.h>
#include <dak/geometry/transform.h>

#include <dak/geometry/tests/helpers.h>

#include <cmath>

#include <CppUnitTest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace dak::geometry;

namespace dak::geometry::tests
{
   TEST_CLASS(rect_tests)
   {
   public:

      TEST_METHOD(rect_constructor)
      {
         rectangle_t r1;

         Assert::IsTrue(r1.is_invalid());
         Assert::AreEqual(point_t(), r1.center());
         Assert::AreEqual(rectangle_t(), r1);
         Assert::IsTrue(rectangle_t() == r1);
         Assert::IsFalse(rectangle_t() != r1);
         Assert::IsTrue(r1 == r1);
         Assert::IsFalse(r1 != r1);

         rectangle_t r2(0, 0, 1, 1);

         Assert::IsFalse(r2.is_invalid());
         Assert::AreEqual(point_t(0.5, 0.5), r2.center());
         Assert::AreEqual(rectangle_t(0, 0, 1, 1), r2);
         Assert::IsTrue(rectangle_t(0, 0, 1, 1) == r2);
         Assert::IsFalse(rectangle_t(0, 0, 1, 1) != r2);
         Assert::IsTrue(r2 == r2);
         Assert::IsFalse(r2 != r2);

         Assert::IsFalse(rectangle_t() == r2);
         Assert::IsFalse(r1 == r2);
         Assert::IsTrue(rectangle_t() != r2);
         Assert::IsTrue(r1 != r2);
         Assert::AreNotEqual(r1, r2);

         rectangle_t r3(point_t(4, 5), 6, 7);

         Assert::IsFalse(r3.is_invalid());
         Assert::AreEqual(point_t(7., 8.5), r3.center());
         Assert::AreEqual(rectangle_t(point_t(4, 5), 6, 7), r3);
         Assert::IsTrue(rectangle_t(point_t(4, 5), 6, 7) == r3);
         Assert::IsFalse(rectangle_t(point_t(4, 5), 6, 7) != r3);
         Assert::AreEqual(rectangle_t(4, 5, 6, 7), r3);
         Assert::IsTrue(rectangle_t(4, 5, 6, 7) == r3);
         Assert::IsFalse(rectangle_t(4, 5, 6, 7) != r3);
         Assert::IsTrue(r3 == r3);
         Assert::IsFalse(r3 != r3);

         Assert::IsFalse(rectangle_t() == r3);
         Assert::IsFalse(r1 == r3);
         Assert::IsTrue(rectangle_t() != r3);
         Assert::IsTrue(r1 != r3);
         Assert::AreNotEqual(r1, r3);

         Assert::IsFalse(rectangle_t(0, 0, 1, 1) == r3);
         Assert::IsFalse(r2 == r3);
         Assert::IsTrue(rectangle_t(0, 0, 1, 1) != r3);
         Assert::IsTrue(r2 != r3);
         Assert::AreNotEqual(r2, r3);

         rectangle_t r4(point_t(4, 5), point_t(6, 7));

         Assert::IsFalse(r4.is_invalid());
         Assert::AreEqual(point_t(5., 6.), r4.center());
         Assert::AreEqual(rectangle_t(point_t(4, 5), point_t(6, 7)), r4);
         Assert::IsTrue(rectangle_t(point_t(4, 5), point_t(6, 7)) == r4);
         Assert::IsFalse(rectangle_t(point_t(4, 5), point_t(6, 7)) != r4);
         Assert::AreEqual(rectangle_t(4, 5, 2, 2), r4);
         Assert::IsTrue(rectangle_t(4, 5, 2, 2) == r4);
         Assert::IsFalse(rectangle_t(4, 5, 2, 2) != r4);
         Assert::IsTrue(r4 == r4);
         Assert::IsFalse(r4 != r4);

         Assert::IsFalse(rectangle_t() == r4);
         Assert::IsFalse(r1 == r4);
         Assert::IsTrue(rectangle_t() != r4);
         Assert::IsTrue(r1 != r4);
         Assert::AreNotEqual(r1, r4);

         Assert::IsFalse(rectangle_t(0, 0, 1, 1) == r4);
         Assert::IsFalse(r2 == r4);
         Assert::IsTrue(rectangle_t(0, 0, 1, 1) != r4);
         Assert::IsTrue(r2 != r4);
         Assert::AreNotEqual(r2, r4);

         Assert::IsFalse(rectangle_t(point_t(4, 5), 6, 7) == r4);
         Assert::IsFalse(r3 == r4);
         Assert::IsTrue(rectangle_t(point_t(4, 5), 6, 7) != r4);
         Assert::IsTrue(r3 != r4);
         Assert::AreNotEqual(r3, r4);
      }

      TEST_METHOD(rect_calculations)
      {
         rectangle_t r1(0, 0, 10, 10);
         rectangle_t r2(4, -4, 20, 20);

         Assert::AreEqual(rectangle_t(0, -4, 24, 20), r1.combine(r2));
         Assert::AreEqual(rectangle_t(4, 0, 6, 10), r1.intersect(r2));

         Assert::AreEqual(r1, r1.combine(point_t(1, 1)));
         Assert::AreEqual(r1, r1.combine(point_t(5, 7)));
         Assert::AreEqual(rectangle_t(0, 0, 11, 11), r1.combine(point_t(11, 11)));

         rectangle_t r3(-14, -14, 10, 10);
         Assert::AreEqual(rectangle_t(), r1.intersect(r3));
         Assert::IsTrue(r1.intersect(r3).is_invalid());

         Assert::AreEqual(rectangle_t(-11.5, -11.5, 5, 5), r3.central_scale(0.5));
         Assert::AreEqual(rectangle_t(-10, -10, 2, 2), r3.central_scale(0.2));
      }

      TEST_METHOD(rect_apply_trf)
      {
         const rectangle_t r1(0, 0, 10, 10);

         Assert::AreEqual(rectangle_t(0, 0, 20, 20), r1.apply(transform_t::scale(2.)));
         Assert::AreEqual(rectangle_t(0, 0, 10, 10), r1.apply(transform_t::reflect(point_t(5., 0), point_t(5, .10))));
         Assert::AreEqual(rectangle_t(10, 0, 10, 10), r1.apply(transform_t::reflect(point_t(10., 00), point_t(10, .10))));
      }

      TEST_METHOD(rect_center_inside)
      {
         rectangle_t small(0, 0, 10, 10);
         rectangle_t big(-5, -5, 20, 20);

         Assert::AreEqual(transform_t::translate(2.5, 2.5).compose(transform_t::scale(0.5)), big.center_inside(small));

         Assert::AreEqual(transform_t::translate(-5, -5).compose(transform_t::scale(2)), small.center_inside(big));
      }

      TEST_METHOD(rect_combine)
      {
      }
   };
}
