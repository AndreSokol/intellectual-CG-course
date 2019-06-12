#pragma once

#include <memory>
#include <vector>

#include <base/color.hpp>
#include <core/material.hpp>
#include <core/gl_const.hpp>

class BasePrimitive {
 public:
  MatRef mat;

//  BasePrimitive() = default;

  BasePrimitive(const MatRef &mat) : mat(mat) {}

  virtual Vec3 normal(const Vec3 &P) { return {0, 0, 0}; };

  virtual bool intersect(const Vec3 &O, const Vec3 &R, double &t) {
    return false;
  };
};

typedef std::shared_ptr<BasePrimitive> PrimRef;
typedef std::vector<PrimRef> Prims;
