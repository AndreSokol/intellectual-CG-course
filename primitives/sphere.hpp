#pragma once

#include "base_primitive.hpp"

#include <math.h>

#include <base/vec3.hpp>
#include <core/gl_const.hpp>
#include <core/material.hpp>

class Sphere : public BasePrimitive {
 public:
  Vec3 center = Vec3(0, 0, 0);
  double radius = 0;

//  Sphere() = default;

  Sphere(const Vec3 &center, const double &radius, const MatRef &mat)
      : BasePrimitive(mat) {
    this->center = center;
    this->radius = radius;
    this->mat = mat;
  };

  Vec3 normal(const Vec3 &P) override { return normalize(P - this->center); };

  bool intersect(const Vec3 &O, const Vec3 &R, double &t) override {
    Vec3 C = O - this->center;

    double k1 = dot(R, R);
    double k2 = 2 * dot(C, R);
    double k3 = dot(C, C) - this->radius * this->radius;

    double det = k2 * k2 - 4 * k1 * k3;
    if (det < 0)
      return false;

    double t0 = (-k2 - sqrt(det)) / 2 / k1;
    double t1 = (-k2 + sqrt(det)) / 2 / k1;

    if (t0 > FLOAT_PRECISION && t0 < CLIPPING_DIST) {
      t = t0;
      return true;
    }

    if (t1 > FLOAT_PRECISION && t1 < CLIPPING_DIST) {
      t = t1;
      return true;
    }

    return false;
  }
};

typedef std::shared_ptr<Sphere> SphereRef;
