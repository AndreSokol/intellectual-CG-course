#pragma once

#include <base/vec3.hpp>
#include <core/gl_const.hpp>
#include <core/material.hpp>
#include <primitives/base_primitive.hpp>
#include <utils/bounding_box.hpp>

#include <algorithm>
#include <memory>
#include <vector>

class Triangle : public BasePrimitive {
private:
public:
  Vec3 A = Vec3(0, 0, 0);
  Vec3 B = Vec3(0, 0, 0);
  Vec3 C = Vec3(0, 0, 0);
  Vec3 N = Vec3(1, 0, 0);
  BBox box;

  Triangle() = default;

  Triangle(const Vec3 &A, const Vec3 &B, const Vec3 &C, const Vec3 &N,
           const MatRef &mat);

  Vec3 normal(const Vec3 &P) override;

  Vec3 &operator[](int i);

  const Vec3 &operator[](int i) const;

  bool intersect(const Vec3 &O, const Vec3 &R, double &t) override;

  double matrixDet(const Vec3 &I, const Vec3 &J, const Vec3 &K);
};

typedef std::shared_ptr<Triangle> TriangleRef;
typedef std::vector<TriangleRef> Tris;

std::ostream &operator<<(std::ostream &os, TriangleRef &t);