#pragma once

#include <vector>
#include <memory>

#include "../utils/Color.hpp"
#include "../core/Material.hpp"

class BasePrimitive {
 public:
  MatRef mat;

  BasePrimitive() {};

  BasePrimitive(const MatRef &mat) : mat(mat) {}

  virtual Vec3 normal(const Vec3 &P) { return Vec3(0, 0, 0); };

  virtual bool intersect(const Vec3 &O, const Vec3 &R, double &t) { return false; };
};

typedef std::shared_ptr<BasePrimitive> PrimRef;
typedef std::vector<PrimRef> Prims;
