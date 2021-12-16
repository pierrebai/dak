#include <dak/geometry/edges_map.h>
#include <dak/geometry/transform.h>
#include <dak/geometry/constants.h>

#include <dak/geometry/tests/helpers.h>

#include <cmath>

#include <CppUnitTest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace dak::geometry;

namespace dak::geometry::tests
{
   TEST_CLASS(map_tests)
   {
   public:

      static size_t range_size(const edges_map_t::range_t& r)
      {
         return r.second - r.first;
      }

      TEST_METHOD(map_constructors)
      {
         const edges_map_t m1;

         Assert::AreEqual<size_t>(0, m1.all().size());
         Assert::AreEqual<size_t>(0, range_size(m1.outbounds(point_t::origin())));

         Assert::IsFalse(m1.contains(point_t::origin()));
         Assert::IsFalse(m1.are_connected(point_t::origin(), point_t::unit_x()));
         
         Assert::AreEqual<size_t>(0, m1.verify().size());
      }

      TEST_METHOD(map_connections_simple)
      {
         edges_map_t m1({
             edge_t(point_t(1., 2.), point_t(-3., -4.)),
             edge_t(point_t(-3., -4.), point_t(-3., 3.)),
             edge_t(point_t(-3., 3.), point_t(2., 3.)),
             edge_t(point_t(2., 3.), point_t(1., 2.)),
            });

         Assert::AreEqual<size_t>(8, m1.all().size());
         Assert::AreEqual<size_t>(2, range_size(m1.outbounds(point_t(1., 2.))));

         Assert::IsTrue(m1.contains(point_t(1., 2.)));
         Assert::IsTrue(m1.contains(point_t(-3., -4.)));
         Assert::IsTrue(m1.contains(point_t(-3., 3.)));
         Assert::IsTrue(m1.contains(point_t(2., 3.)));

         Assert::IsTrue(m1.are_connected(point_t(1., 2.), point_t(-3., -4.)));
         Assert::IsTrue(m1.are_connected(point_t(-3., -4.), point_t(-3., 3.)));
         Assert::IsTrue(m1.are_connected(point_t(-3., 3.), point_t(2., 3.)));
         Assert::IsTrue(m1.are_connected(point_t(2., 3.), point_t(1., 2.)));

         Assert::IsFalse(m1.are_connected(point_t(1., 2.), point_t(-3., 3.)));
         Assert::IsFalse(m1.are_connected(point_t(-3., -4.), point_t(2., 3.)));

         Assert::AreEqual<size_t>(0, m1.verify().size());
      }

      TEST_METHOD(map_connections_cross)
      {
         edges_map_t m1({
             edge_t(point_t(-2., 0.), point_t(2., 0.)),
             edge_t(point_t(0., -3.), point_t(0., 3.)),
            });

         Assert::AreEqual<size_t>(8, m1.all().size());
         Assert::AreEqual<size_t>(1, range_size(m1.outbounds(point_t(2., 0.))));

         Assert::IsTrue(m1.contains(point_t(-2.,  0.)));
         Assert::IsTrue(m1.contains(point_t( 2.,  0.)));
         Assert::IsTrue(m1.contains(point_t( 0.,  3.)));
         Assert::IsTrue(m1.contains(point_t( 0., -3.)));
         Assert::IsTrue(m1.contains(point_t( 0.,  0.)));

         Assert::IsTrue(m1.are_connected(point_t(-2.,  0.), point_t(0., 0.)));
         Assert::IsTrue(m1.are_connected(point_t( 2.,  0.), point_t(0., 0.)));
         Assert::IsTrue(m1.are_connected(point_t( 0.,  3.), point_t(0., 0.)));
         Assert::IsTrue(m1.are_connected(point_t( 0., -3.), point_t(0., 0.)));

         Assert::IsFalse(m1.are_connected(point_t(-2.,  0.), point_t(2., 0.)));
         Assert::IsFalse(m1.are_connected(point_t( 0., -3.), point_t(0., 3.)));

         Assert::AreEqual<size_t>(0, m1.verify().size());
      }

      TEST_METHOD(map_insert_remove)
      {
         edges_map_t m1;
         
         m1.insert(edge_t(point_t(-2., 0.), point_t(2., 0.)));

         Assert::AreEqual<size_t>(2, m1.all().size());

         Assert::AreEqual<size_t>(1, range_size(m1.outbounds(point_t(-2., 0.))));

         Assert::IsTrue(m1.contains(point_t(-2., 0.)));
         Assert::IsTrue(m1.contains(point_t( 2., 0.)));

         Assert::IsTrue( m1.are_connected(point_t(-2., 0.), point_t( 2., 0.)));
         Assert::IsTrue( m1.are_connected(point_t( 2., 0.), point_t(-2., 0.)));
         Assert::IsFalse(m1.are_connected(point_t( 2., 0.), point_t( 0., 0.)));

         m1.insert(edge_t(point_t(0., -3.), point_t(0., 3.)));

         Assert::AreEqual<size_t>(0, m1.verify().size());

         Assert::AreEqual<size_t>(8, m1.all().size());

         Assert::AreEqual<size_t>(1, range_size(m1.outbounds(point_t(0., 3.))));

         Assert::AreEqual<size_t>(4, range_size(m1.outbounds(point_t(0., 0.))));

         Assert::IsTrue(m1.contains(point_t(-2.,  0.)));
         Assert::IsTrue(m1.contains(point_t( 2.,  0.)));
         Assert::IsTrue(m1.contains(point_t( 0.,  3.)));
         Assert::IsTrue(m1.contains(point_t( 0., -3.)));
         Assert::IsTrue(m1.contains(point_t( 0.,  0.)));

         Assert::IsTrue(m1.are_connected(point_t(-2.,  0.), point_t(0., 0.)));
         Assert::IsTrue(m1.are_connected(point_t( 2.,  0.), point_t(0., 0.)));
         Assert::IsTrue(m1.are_connected(point_t( 0.,  3.), point_t(0., 0.)));
         Assert::IsTrue(m1.are_connected(point_t( 0., -3.), point_t(0., 0.)));

         Assert::IsFalse(m1.are_connected(point_t(-2.,  0.), point_t(2., 0.)));
         Assert::IsFalse(m1.are_connected(point_t( 0., -3.), point_t(0., 3.)));

         m1.remove(edge_t(point_t(0., 0.), point_t(0., 3.)));

         Assert::AreEqual<size_t>(0, m1.verify().size());

         Assert::AreEqual<size_t>(6, m1.all().size());

         Assert::AreEqual<size_t>(0, range_size(m1.outbounds(point_t(0., 3.))));

         Assert::AreEqual<size_t>(1, range_size(m1.outbounds(point_t(0., -3.))));

         Assert::AreEqual<size_t>(3, range_size(m1.outbounds(point_t(0., 0.))));

         Assert::IsTrue(m1.contains(point_t(-2., 0.)));
         Assert::IsTrue(m1.contains(point_t(2., 0.)));
         Assert::IsFalse(m1.contains(point_t(0., 3.)));
         Assert::IsTrue(m1.contains(point_t(0., -3.)));
         Assert::IsTrue(m1.contains(point_t(0., 0.)));

         Assert::IsTrue(m1.are_connected(point_t(-2., 0.), point_t(0., 0.)));
         Assert::IsTrue(m1.are_connected(point_t(2., 0.), point_t(0., 0.)));
         Assert::IsFalse(m1.are_connected(point_t(0., 3.), point_t(0., 0.)));
         Assert::IsTrue(m1.are_connected(point_t(0., -3.), point_t(0., 0.)));

         Assert::IsFalse(m1.are_connected(point_t(-2., 0.), point_t(2., 0.)));
         Assert::IsFalse(m1.are_connected(point_t(0., -3.), point_t(0., 3.)));

         m1.remove(point_t(2., 0.));

         Assert::AreEqual<size_t>(0, m1.verify().size());

         Assert::AreEqual<size_t>(4, m1.all().size());

         Assert::AreEqual<size_t>(0, range_size(m1.outbounds(point_t(2., 0.))));

         Assert::AreEqual<size_t>(1, range_size(m1.outbounds(point_t(-2., 0.))));

         Assert::IsTrue(m1.contains(point_t(-2., 0.)));
         Assert::IsFalse(m1.contains(point_t(2., 0.)));
         Assert::IsFalse(m1.contains(point_t(0., 3.)));
         Assert::IsTrue(m1.contains(point_t(0., -3.)));
         Assert::IsTrue(m1.contains(point_t(0., 0.)));

         Assert::IsTrue(m1.are_connected(point_t(-2., 0.), point_t(0., 0.)));
         Assert::IsFalse(m1.are_connected(point_t(2., 0.), point_t(0., 0.)));
         Assert::IsFalse(m1.are_connected(point_t(0., 3.), point_t(0., 0.)));
         Assert::IsTrue(m1.are_connected(point_t(0., -3.), point_t(0., 0.)));

         Assert::IsFalse(m1.are_connected(point_t(-2., 0.), point_t(2., 0.)));
         Assert::IsFalse(m1.are_connected(point_t(0., -3.), point_t(0., 3.)));
      }

      TEST_METHOD(map_singleton_transform)
      {
         {
            edges_map_t m1({ edge_t(point_t(1., 2.), point_t(-3., -4.)) });

            Assert::AreEqual<size_t>(0, m1.verify().size());

            edges_map_t m2 = m1.apply(transform_t::rotate(PI / 2));
            Assert::IsTrue(m2.contains(edge_t(point_t(-2., 1.), point_t(4., -3.))));

            Assert::AreEqual<size_t>(0, m2.verify().size());
         }

         {
            edges_map_t m1({ edge_t(point_t(1., 2.), point_t(-3., -4.)) });

            Assert::AreEqual<size_t>(0, m1.verify().size());

            edges_map_t m2 = m1.apply(transform_t::rotate(PI));
            Assert::IsTrue(m2.contains(edge_t(point_t(-1., -2.), point_t(3., 4.))));

            Assert::AreEqual<size_t>(0, m2.verify().size());
         }

         {
            edges_map_t m1({ edge_t(point_t(1., 2.), point_t(-3., -4.)) });

            Assert::AreEqual<size_t>(0, m1.verify().size());

            edges_map_t m2 = m1.apply(transform_t::rotate(3 * PI / 2));
            Assert::IsTrue(m2.contains(edge_t(point_t(2., -1.), point_t(-4., 3.))));

            Assert::AreEqual<size_t>(0, m2.verify().size());
         }

         {
            edges_map_t m1({ edge_t(point_t(1., 2.), point_t(-3., -4.)) });

            Assert::AreEqual<size_t>(0, m1.verify().size());

            edges_map_t m2 = m1.apply(transform_t::rotate(2 * PI));
            Assert::IsTrue(m2.contains(edge_t(point_t(1., 2.), point_t(-3., -4.))));

            Assert::AreEqual<size_t>(0, m2.verify().size());
         }

         {
            edges_map_t m1({ edge_t(point_t::origin(), point_t::unit_x()) });

            Assert::AreEqual<size_t>(0, m1.verify().size());

            edges_map_t m2 = m1.apply(transform_t::rotate(PI / 4));
            Assert::IsTrue(m2.contains(edge_t(point_t::origin(), point_t(std::sqrt(2.) / 2., std::sqrt(2.) / 2.))));

            Assert::AreEqual<size_t>(0, m2.verify().size());
         }

         {
            edges_map_t m1({ edge_t(point_t(1., 2.), point_t(-3., -4.)) });

            Assert::AreEqual<size_t>(0, m1.verify().size());

            edges_map_t m2 = m1.apply(transform_t::translate(2., 3.));
            Assert::IsTrue(m2.contains(edge_t(point_t(3., 5.), point_t(-1., -1.))));

            Assert::AreEqual<size_t>(0, m2.verify().size());
         }

         {
            edges_map_t m1({ edge_t(point_t(1., 2.), point_t(-3., -4.)) });

            Assert::AreEqual<size_t>(0, m1.verify().size());

            edges_map_t m2 = m1.apply(transform_t::translate(point_t(-3., -7.)));
            Assert::IsTrue(m2.contains(edge_t(point_t(-2., -5.), point_t(-6., -11.))));

            Assert::AreEqual<size_t>(0, m2.verify().size());
         }

         {
            edges_map_t m1({ edge_t(point_t(1., 2.), point_t(-3., -4.)) });

            Assert::AreEqual<size_t>(0, m1.verify().size());

            edges_map_t m2 = m1.apply(transform_t::scale(2.));
            Assert::IsTrue(m2.contains(edge_t(point_t(2., 4.), point_t(-6., -8.))));

            Assert::AreEqual<size_t>(0, m2.verify().size());
         }

         {
            edges_map_t m1({ edge_t(point_t(1., 2.), point_t(-3., -4.)) });

            Assert::AreEqual<size_t>(0, m1.verify().size());

            edges_map_t m2 = m1.apply(transform_t::scale(-3., -7.));
            Assert::IsTrue(m2.contains(edge_t(point_t(-3., -14.), point_t(9., 28.))));

            Assert::AreEqual<size_t>(0, m2.verify().size());
         }
      }

      TEST_METHOD(map_crossing_edges_transform)
      {
         {
            const edges_map_t m1({
                edge_t(point_t(-2., 0.), point_t(2., 0.)),
                edge_t(point_t(0., -3.), point_t(0., 3.)),
                   });

            Assert::AreEqual<size_t>(0, m1.verify().size());

            edges_map_t m2 = m1.apply(transform_t::rotate(PI / 2));
            Assert::IsTrue(m2.contains(edge_t(point_t(-3.,  0.), point_t(0., 0.))));
            Assert::IsTrue(m2.contains(edge_t(point_t( 3.,  0.), point_t(0., 0.))));
            Assert::IsTrue(m2.contains(edge_t(point_t( 0., -2.), point_t(0., 0.))));
            Assert::IsTrue(m2.contains(edge_t(point_t( 0.,  2.), point_t(0., 0.))));

            Assert::AreEqual<size_t>(0, m2.verify().size());
         }

         {
            const edges_map_t m1({
                edge_t(point_t(-2., 0.), point_t(2., 0.)),
                edge_t(point_t(0., -3.), point_t(0., 3.)),
                   });

            Assert::AreEqual<size_t>(0, m1.verify().size());

            edges_map_t m2 = m1.apply(transform_t::rotate(PI));
            Assert::IsTrue(m2.contains(edge_t(point_t(-2., 0.), point_t(0., 0.))));
            Assert::IsTrue(m2.contains(edge_t(point_t(2., 0.), point_t(0., 0.))));
            Assert::IsTrue(m2.contains(edge_t(point_t(0., -3.), point_t(0., 0.))));
            Assert::IsTrue(m2.contains(edge_t(point_t(0., 3.), point_t(0., 0.))));

            Assert::AreEqual<size_t>(0, m2.verify().size());
         }

         {
            const edges_map_t m1({
                edge_t(point_t(-2., 0.), point_t(2., 0.)),
                edge_t(point_t(0., -3.), point_t(0., 3.)),
                   });

            Assert::AreEqual<size_t>(0, m1.verify().size());

            edges_map_t m2 = m1.apply(transform_t::translate(-7, 5.));
            Assert::IsTrue(m2.contains(edge_t(point_t(-9., 5.), point_t(-7., 5.))));
            Assert::IsTrue(m2.contains(edge_t(point_t(-5., 5.), point_t(-7., 5.))));
            Assert::IsTrue(m2.contains(edge_t(point_t(-7., 2.), point_t(-7., 5.))));
            Assert::IsTrue(m2.contains(edge_t(point_t(-7., 8.), point_t(-7., 5.))));

            Assert::AreEqual<size_t>(0, m2.verify().size());
         }

         {
            const edges_map_t m1({
                edge_t(point_t(-2., 0.), point_t(2., 0.)),
                edge_t(point_t(0., -3.), point_t(0., 3.)),
                   });

            Assert::AreEqual<size_t>(0, m1.verify().size());

            edges_map_t m2 = m1.apply(transform_t::scale(3.));
            Assert::IsTrue(m2.contains(edge_t(point_t(-6.,  0.), point_t(0., 0.))));
            Assert::IsTrue(m2.contains(edge_t(point_t( 6.,  0.), point_t(0., 0.))));
            Assert::IsTrue(m2.contains(edge_t(point_t( 0., -9.), point_t(0., 0.))));
            Assert::IsTrue(m2.contains(edge_t(point_t( 0.,  9.), point_t(0., 0.))));

            Assert::AreEqual<size_t>(0, m2.verify().size());
         }

         {
            const edges_map_t m1({
                edge_t(point_t(-2., 0.), point_t(2., 0.)),
                edge_t(point_t(0., -3.), point_t(0., 3.)),
                   });

            Assert::AreEqual<size_t>(0, m1.verify().size());

            edges_map_t m2 = m1.apply(transform_t::scale(0.5, -2.));
            Assert::IsTrue(m2.contains(edge_t(point_t(-1.,  0.), point_t(0., 0.))));
            Assert::IsTrue(m2.contains(edge_t(point_t( 1.,  0.), point_t(0., 0.))));
            Assert::IsTrue(m2.contains(edge_t(point_t( 0., -6.), point_t(0., 0.))));
            Assert::IsTrue(m2.contains(edge_t(point_t( 0.,  6.), point_t(0., 0.))));

            Assert::AreEqual<size_t>(0, m2.verify().size());
         }
      }

      TEST_METHOD(map_small_merge)
      {
         map_merge(100);
      }

      //#define DAK_GEOMETRY_SLOW_MAP_TESTS

      #ifdef DAK_GEOMETRY_SLOW_MAP_TESTS

      TEST_METHOD(map_medium_merge_333ms)
      {
         map_merge(400);
      }

      TEST_METHOD(map_big_merge_2s)
      {
         map_merge(1000);
      }

      TEST_METHOD(map_very_big_merge_9s)
      {
         map_merge(2000);
      }

      #endif

   private:
      void map_merge(int count)
      {
         edges_map_t horiz;
         for (int i = 1; i <= count; ++i)
         {
            horiz.insert(edge_t(point_t(-count, i / 2.), point_t(count, i / 2.)));
         }
         Assert::AreEqual<size_t>(count * 2, horiz.all().size());

         Assert::AreEqual<size_t>(0, horiz.verify().size());

         edges_map_t verti;
         for (int i = 1; i <= count; ++i)
         {
            verti.insert(edge_t(point_t(i / 2., -count), point_t(i / 2., count)));
         }
         Assert::AreEqual<size_t>(count * 2, verti.all().size());

         Assert::AreEqual<size_t>(0, verti.verify().size());

         horiz.merge(verti);

         Assert::AreEqual<size_t>(0, horiz.verify().size());

         Assert::AreEqual<size_t>((count + 1) * count * 2 * 2, horiz.all().size());

         for (int x = 1; x <= count; ++x)
         {
            for (int y = 1; y <= count; ++y)
            {
               Assert::AreEqual<size_t>(4, range_size(horiz.outbounds(point_t(x / 2., y / 2.))));
            }
         }
      }
   };
}
