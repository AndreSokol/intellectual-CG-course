#pragma once

#include "../primitives/Triangle.hpp"

#include <vector>
#include <memory>

class BVHNode {
 public:
  std::shared_ptr<BVHNode> left;
  std::shared_ptr<BVHNode> right;
  BBox bbox;

  Tris primitives;

  void build(const Tris &tris);

  void updateBbox(const Tris &tris);

  bool findIntersection(TriangleRef &triangle, double &t, const Vec3 &O, const Vec3 &R);
};

typedef std::shared_ptr<BVHNode> BVHPtr;

BVHPtr buildBVH(const Tris &tris);

std::ostream &operator<<(std::ostream &os, BVHNode &node);