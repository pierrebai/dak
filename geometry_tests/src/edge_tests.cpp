#include <dak/geometry/edge.h>
#include <dak/geometry/transform.h>
#include <dak/geometry/constants.h>

#include <dak/geometry/tests/helpers.h>

#include <cmath>


#include <CppUnitTest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace dak::geometry;

namespace dak::geometry::tests
{		
	TEST_CLASS(edge_tests)
	{
	public:
		
		TEST_METHOD(edge_constructors_and_comparisons)
		{
         const edge_t e1;

         Assert::IsTrue(e1.is_invalid());
         Assert::IsTrue(e1.is_trivial());
         Assert::IsFalse(e1.is_canonical());
         Assert::AreEqual(edge_t::invalid, e1);
         Assert::IsTrue(edge_t::invalid == e1);
         Assert::IsTrue(e1 == e1);
         Assert::IsFalse(e1 < e1);

         const edge_t e2(point_t(1., 2.), point_t(-3., -4.));
         Assert::AreEqual(1., e2.p1.x);
         Assert::AreEqual(2., e2.p1.y);
         Assert::AreEqual(-3., e2.p2.x);
         Assert::AreEqual(-4., e2.p2.y);

         Assert::AreNotEqual(e1, e2);
         Assert::AreNotEqual(edge_t::invalid, e2);
         Assert::IsFalse(e2.is_invalid());
         Assert::IsFalse(e2.is_trivial());
         Assert::IsFalse(e2.is_canonical());
         Assert::IsTrue(e1 != e2);
         Assert::IsTrue(e2 == e2);
         Assert::IsTrue(edge_t::invalid != e2);
         Assert::IsFalse(e1 < e2);
         Assert::IsFalse(e2 < e2);
         Assert::IsFalse(edge_t::invalid < e2);

         const edge_t e3(point_t(2., 1.), point_t(5., 7.));
         Assert::AreEqual(2., e3.p1.x);
         Assert::AreEqual(1., e3.p1.y);
         Assert::AreEqual(5., e3.p2.x);
         Assert::AreEqual(7., e3.p2.y);

         Assert::AreNotEqual(e1, e3);
         Assert::AreNotEqual(e2, e3);
         Assert::AreNotEqual(edge_t::invalid, e3);
         Assert::IsFalse(e3.is_invalid());
         Assert::IsFalse(e3.is_trivial());
         Assert::IsTrue(e3.is_canonical());
         Assert::IsTrue(e1 != e3);
         Assert::IsTrue(e2 != e3);
         Assert::IsTrue(e3 == e3);
         Assert::IsTrue(edge_t::invalid != e3);
         Assert::IsFalse(e1 < e3);
         Assert::IsTrue(e2 < e3);
         Assert::IsFalse(e3 < e3);
         Assert::IsFalse(edge_t::invalid < e3);

         const edge_t e4(e3);
         Assert::AreEqual(2., e4.p1.x);
         Assert::AreEqual(1., e4.p1.y);
         Assert::AreEqual(5., e4.p2.x);
         Assert::AreEqual(7., e4.p2.y);

         Assert::AreNotEqual(e1, e4);
         Assert::AreNotEqual(e2, e4);
         Assert::AreEqual(e3, e4);
         Assert::AreNotEqual(edge_t::invalid, e4);
         Assert::IsFalse(e4.is_invalid());
         Assert::IsFalse(e4.is_trivial());
         Assert::IsTrue(e4.is_canonical());
         Assert::IsTrue(e1 != e4);
         Assert::IsTrue(e2 != e4);
         Assert::IsTrue(e3 == e4);
         Assert::IsTrue(e4 == e4);
         Assert::IsTrue(edge_t::invalid != e4);
         Assert::IsFalse(e1 < e4);
         Assert::IsTrue(e2 < e4);
         Assert::IsFalse(e3 < e4);
         Assert::IsFalse(e4 < e4);
         Assert::IsFalse(edge_t::invalid < e4);

         const edge_t e5(e2.canonical());
         Assert::AreEqual(-3., e5.p1.x);
         Assert::AreEqual(-4., e5.p1.y);
         Assert::AreEqual(1., e5.p2.x);
         Assert::AreEqual(2., e5.p2.y);

         Assert::AreNotEqual(e1, e5);
         Assert::AreNotEqual(e2, e5);
         Assert::AreNotEqual(e3, e5);
         Assert::AreNotEqual(e4, e5);
         Assert::AreNotEqual(edge_t::invalid, e5);
         Assert::IsFalse(e5.is_invalid());
         Assert::IsFalse(e5.is_trivial());
         Assert::IsTrue(e5.is_canonical());
         Assert::IsTrue(e1 != e5);
         Assert::IsTrue(e2 != e5);
         Assert::IsTrue(e3 != e5);
         Assert::IsTrue(e4 != e5);
         Assert::IsTrue(e5 == e5);
         Assert::IsTrue(e2.canonical() == e5);
         Assert::IsTrue(edge_t::invalid != e5);
         Assert::IsFalse(e1 < e5);
         Assert::IsFalse(e2 < e5);
         Assert::IsFalse(e3 < e5);
         Assert::IsFalse(e4 < e5);
         Assert::IsFalse(e5 < e5);
         Assert::IsTrue(e5 < e2);
         Assert::IsTrue(e5 < e3);
         Assert::IsTrue(e5 < e4);
         Assert::IsFalse(edge_t::invalid < e5);

         Assert::AreEqual(point_t::origin(), edge_t::unit_x().p1);
         Assert::AreEqual(point_t::unit_x(), edge_t::unit_x().p2);

         Assert::AreEqual(point_t::origin(), edge_t::unit_y().p1);
         Assert::AreEqual(point_t::unit_y(), edge_t::unit_y().p2);

         const edge_t e6 = edge_t::lowest_edge(e2.p1);
         Assert::IsTrue(e6 < e2);

         const edge_t e7 = edge_t::highest_edge(e2.p1);
         Assert::IsTrue(e2 < e7);

         edge_t e8(point_t(1., 2.), point_t(3., 4.));
         edge_t e9(point_t(5., 6.), point_t(7., 8.));
         Assert::AreEqual(point_t(1., 2.), e8.p1);
         Assert::AreEqual(point_t(3., 4.), e8.p2);
         Assert::AreEqual(point_t(5., 6.), e9.p1);
         Assert::AreEqual(point_t(7., 8.), e9.p2);

         e8.swap(e9);
         Assert::AreEqual(point_t(5., 6.), e8.p1);
         Assert::AreEqual(point_t(7., 8.), e8.p2);
         Assert::AreEqual(point_t(1., 2.), e9.p1);
         Assert::AreEqual(point_t(3., 4.), e9.p2);

         const edge_t e10 = e8.twin();
         Assert::AreEqual(point_t(7., 8.), e10.p1);
         Assert::AreEqual(point_t(5., 6.), e10.p2);

         const edge_t e11(point_t(1., 1.), point_t(1., 1.));
         Assert::AreEqual(1., e11.p1.x);
         Assert::AreEqual(1., e11.p1.y);
         Assert::AreEqual(1., e11.p2.x);
         Assert::AreEqual(1., e11.p2.y);

         Assert::AreNotEqual(e1, e11);
         Assert::AreNotEqual(e2, e11);
         Assert::AreNotEqual(e3, e11);
         Assert::AreNotEqual(e4, e11);
         Assert::AreNotEqual(edge_t::invalid, e11);
         Assert::IsFalse(e11.is_invalid());
         Assert::IsTrue(e11.is_trivial());
         Assert::IsFalse(e11.is_canonical());
         Assert::IsFalse(e11.twin().is_canonical());
         Assert::IsTrue(e1 != e11);
         Assert::IsTrue(e2 != e11);
         Assert::IsTrue(e3 != e11);
         Assert::IsTrue(e4 != e11);
         Assert::IsTrue(e11 == e11);
         Assert::IsTrue(e11.twin() == e11);
         Assert::IsTrue(edge_t::invalid != e11);
         Assert::IsFalse(e1 < e11);
         Assert::IsFalse(e2 < e11);
         Assert::IsFalse(e3 < e11);
         Assert::IsFalse(e4 < e11);
         Assert::IsFalse(e11 < e11);
         Assert::IsTrue(e11 < e2);
         Assert::IsTrue(e11 < e3);
         Assert::IsTrue(e11 < e4);
         Assert::IsFalse(edge_t::invalid < e11);
      }

      TEST_METHOD(edge_angles)
      {
         Assert::AreEqual(0., edge_t::unit_x().angle());
         Assert::AreEqual(PI / 2, edge_t::unit_y().angle());
         Assert::AreEqual(PI / 2, edge_t::unit_x().angle(edge_t::unit_y()));
         Assert::AreEqual(3 * PI / 2, edge_t::unit_y().angle(edge_t::unit_x()));
      }

      TEST_METHOD(edge_transform)
      {
         {
            const edge_t e1(point_t(1., 2.), point_t(-3., -4.));

            Assert::AreEqual(edge_t(point_t(-2., 1.), point_t(4., -3.)), e1.apply(transform_t::rotate(PI / 2)));
            Assert::AreEqual(edge_t(point_t(-1., -2.), point_t(3., 4.)), e1.apply(transform_t::rotate(PI)));
            Assert::AreEqual(edge_t(point_t(2., -1.), point_t(-4., 3.)), e1.apply(transform_t::rotate(3 * PI / 2)));
            Assert::AreEqual(edge_t(point_t(1., 2.), point_t(-3., -4.)), e1.apply(transform_t::rotate(2 * PI)));
         }

         {
            Assert::AreEqual(edge_t(point_t::origin(), point_t(0., 1.)), edge_t::unit_x().apply(transform_t::rotate(PI / 2)));
            Assert::AreEqual(edge_t(point_t::origin(), point_t(-1., 0.)), edge_t::unit_x().apply(transform_t::rotate(PI)));
            Assert::AreEqual(edge_t(point_t::origin(), point_t(0., -1.)), edge_t::unit_x().apply(transform_t::rotate(3 * PI / 2)));
            Assert::AreEqual(edge_t::unit_x(), edge_t::unit_x().apply(transform_t::rotate(2 * PI)));

            Assert::AreEqual(edge_t(point_t::origin(), point_t(std::sqrt(2.) / 2., std::sqrt(2.) / 2.)), edge_t::unit_x().apply(transform_t::rotate(PI / 4)));
         }

         {
            const edge_t e1(point_t(1., 2.), point_t(-3., -4.));

            Assert::AreEqual(edge_t(point_t(3., 5.), point_t(-1., -1.)), e1.apply(transform_t::translate(2., 3.)));
            Assert::AreEqual(edge_t(point_t(-2., -5.), point_t(-6., -11.)), e1.apply(transform_t::translate(point_t(-3., -7.))));
         }

         {
            const edge_t e1(point_t(1., 2.), point_t(-3., -4.));

            Assert::AreEqual(edge_t(point_t(2., 4.), point_t(-6., -8.)), e1.apply(transform_t::scale(2.)));
            Assert::AreEqual(edge_t(point_t(-3., -14.), point_t(9., 28.)), e1.apply(transform_t::scale(-3., -7.)));
         }

      }
   };
}
