#pragma once

#ifndef DAK_GEOMETRY_TRANSFORM_H
#define DAK_GEOMETRY_TRANSFORM_H

#include <dak/geometry/point.h>
#include <dak/utility/number.h>

namespace dak::geometry
{
   ////////////////////////////////////////////////////////////////////////////
   //
   // A two-dimensional affine transform.  I store the top two rows of 
   // the homogeneous 3x3 matrix.  Or, looked at another way, it's the
   // 2D linear transform ((scale_x rot_1) (rot_2 scale_y)) together with
   // the translation (trans_x trans_y).

   class transform_t
   {
   public:
      // Note: the name of the variable are only somwhat indicative.
      //       for example rotations get mixed with scale.
      double scale_x, rot_1, trans_x;
      double rot_2, scale_y, trans_y;

      // Two common transform.
      static constexpr transform_t zero() { return scale(0.0); }
      static constexpr transform_t identity() { return scale(1.0); }

      // Static invalid transform, to be returned from some functions.
      static const transform_t invalid;

      // Invalid transform.
      constexpr transform_t()
         : scale_x(0), rot_1(0), trans_x(0), rot_2(0), scale_y(0), trans_y(0)
      {
      }

      // Transform initialized from the given values.
      constexpr transform_t(double scale_x, double rot_1, double trans_x, double rot_2, double scale_y, double trans_y)
         : scale_x(scale_x), rot_1(rot_1), trans_x(trans_x), rot_2(rot_2), scale_y(scale_y), trans_y(trans_y)
      {
      }

      // Uniform scaling from the origin.
      static constexpr transform_t scale(double r)
      {
         return transform_t(
            r, 0, 0,
            0, r, 0);
      }

      // Non-uniform scaling from the origin.
      static constexpr transform_t scale(double xs, double ys)
      {
         return transform_t(
            xs, 0, 0,
            0, ys, 0);
      }

      // Uniform scaling from the given point.
      static transform_t scale(const point_t& pt, double r)
      {
         return translate(-pt.x, -pt.y).then(scale(r)).then(translate(pt));
      }

      // Non-uniform scaling from the given point.
      static transform_t scale(const point_t& pt, double xs, double ys)
      {
         return translate(-pt.x, -pt.y).then(scale(xs, ys)).then(translate(pt));
      }

      // Translation of the given distances.
      static constexpr transform_t translate(double x, double y)
      {
         return transform_t(
            1.0, 0, x,
            0, 1.0, y);
      }

      // Translation of the given distances.
      static constexpr transform_t translate(const point_t& pt)
      {
         return transform_t(
            1.0, 0, pt.x,
            0, 1.0, pt.y);
      }

      // Rotation around the origin.
      static transform_t rotate(double t);

      // Rotation around the given point.
      static transform_t rotate(const point_t& pt, double t);

      // Reflection accross the given line.
      static constexpr transform_t reflect(const point_t& p, const point_t& q)
      {
         transform_t T = match_line(p, q);
         return T.compose(
            scale(1.0, -1.0).compose(T.invert()));
      }

      // Create a transform to bring points from the normal corrdinates to a coordinate system with basis u and v.
      // (With u and v expressed in coordinate from the source coordinates system.)
      static constexpr transform_t to_basis(const point_t& u, const point_t& v)
      {
         return transform_t(u.x, v.x, 0,
                           u.y, v.y, 0).invert();
      }

      // Transform composition.
      constexpr transform_t compose(const transform_t& other) const
      {
         return transform_t(
            scale_x * other.scale_x + rot_1 * other.rot_2,
            scale_x * other.rot_1   + rot_1 * other.scale_y,
            scale_x * other.trans_x + rot_1 * other.trans_y + trans_x,

            rot_2 * other.scale_x + scale_y * other.rot_2,
            rot_2 * other.rot_1   + scale_y * other.scale_y,
            rot_2 * other.trans_x + scale_y * other.trans_y + trans_y);
      }

      constexpr transform_t then(const transform_t& other) const
      {
         return other.compose(*this);
      }

      // Invert the transform.
      constexpr transform_t invert() const
      {
         double det = scale_x * scale_y - rot_1 * rot_2;

         if (det == 0.0)
            return transform_t();

         return transform_t(
            scale_y / det, -rot_1 / det, (rot_1 * trans_y - trans_x * scale_y) / det,
            -rot_2 / det, scale_x / det, (trans_x * rot_2 - scale_x * trans_y) / det);
      }

      // Provide the transform matrix to carry the unit interval
      // on the positive X axis to the line segment from p to q.
      static constexpr transform_t match_line(const point_t& p, const point_t& q)
      {
         double px = p.x;
         double py = p.y;
         double qx = q.x;
         double qy = q.y;

         return transform_t(
            qx - px, py - qy, px,
            qy - py, qx - px, py);
      }

      // Get the transform that carries p1->q1 to p2->q2.
      static constexpr transform_t match_lines(
         const point_t& p1, const point_t& q1, const point_t& p2, const point_t& q2)
      {
         transform_t top1q1 = match_line(p1, q1);
         transform_t top2q2 = match_line(p2, q2);
         return top2q2.compose(top1q1.invert());
      }

      // Get distance from zero for a double value.
      // Used to calculate radius, jitters, etc.
      double dist_from_zero(double v) const;

      double dist_from_inverted_zero(double v) const;

      // Returns true if this transform includes a reflection.
      constexpr bool flips() const
      {
         return (scale_x*scale_y - rot_1 * rot_2) < 0.0;
      }

      // Comparison.
      bool operator ==(const transform_t& t) const
      {
         return utility::near(scale_x, t.scale_x) && utility::near(rot_1, t.rot_1)     && utility::near(trans_x, t.trans_x) &&
                  utility::near(rot_2, t.rot_2)     && utility::near(scale_y, t.scale_y) && utility::near(trans_y, t.trans_y);
      }

      bool operator !=(const transform_t& t) const
      {
         return !(*this == t);
      }

      bool operator <(const transform_t& t) const
      {
         if (utility::near_less(scale_x, t.scale_x))
            return true;
         if (utility::near_greater(scale_x, t.scale_x))
            return false;

         if (utility::near_less(rot_1, t.rot_1))
            return true;
         if (utility::near_greater(rot_1, t.rot_1))
            return false;

         if (utility::near_less(trans_x, t.trans_x))
            return true;
         if (utility::near_greater(trans_x, t.trans_x))
            return false;

         if (utility::near_less(rot_2, t.rot_2))
            return true;
         if (utility::near_greater(rot_2, t.rot_2))
            return false;

         if (utility::near_less(scale_y, t.scale_y))
            return true;
         if (utility::near_greater(scale_y, t.scale_y))
            return false;

         if (utility::near_less(trans_y, t.trans_y))
            return true;
         if (utility::near_greater(trans_y, t.trans_y))
            return false;

         return false;
      }

      // Verify if it is invalid.
      bool is_invalid() const
      {
         return *this == transform_t();
      }
   };
}

#endif

// vim: sw=3 : sts=3 : et : sta : 
