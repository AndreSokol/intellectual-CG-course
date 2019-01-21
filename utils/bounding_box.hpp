#pragma once

#include "vec3.hpp"
#include <limits>
#include <cmath>
#include <algorithm>

class BBox {
 public:
  BBox() = default;

  Vec3 bbmin = Vec3{std::numeric_limits<double>::max(),
                    std::numeric_limits<double>::max(),
                    std::numeric_limits<double>::max()};
  Vec3 bbmax = Vec3{-std::numeric_limits<double>::max(),
                    -std::numeric_limits<double>::max(),
                    -std::numeric_limits<double>::max()};

  inline bool isInside(const Vec3 &point) {
    return bbmin.x <= point.x && bbmin.y <= point.y && bbmin.z <= point.z &&
        bbmax.x >= point.x && bbmax.y >= point.y && bbmax.z >= point.z;
  }

  struct IntersectionData {
    bool is_intersecting;
    double tmax;
    double tmin;
  };

  double volume();

  IntersectionData isIntersecting(const Vec3 &O, const Vec3 &R);
};

std::ostream &operator<<(std::ostream &os, BBox &bbox);