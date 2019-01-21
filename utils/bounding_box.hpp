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

  IntersectionData isIntersecting(const Vec3 &O, const Vec3 &R) {
    IntersectionData res{false,
                         std::numeric_limits<double>::min(),
                         std::numeric_limits<double>::max()};

    for (int axis : {0, 1, 2}) {
      if (R[axis] != 0) {
        double dtmin = (bbmin[axis] - O[axis]) / R[axis];
        const auto &intersection_min = O + dtmin * R;
        if (isInside(intersection_min)) {
          res.is_intersecting = true;
          res.tmin = std::min(res.tmin, dtmin);
          res.tmax = std::max(res.tmax, dtmin);
        }

        double dtmax = (bbmax[axis] - O[axis]) / R[axis];
        const auto &intersection_max = O + dtmin * R;
        if (isInside(intersection_max)) {
          res.is_intersecting = true;
          res.tmin = std::min(res.tmin, dtmax);
          res.tmax = std::max(res.tmax, dtmax);
        }
      }
    }

    return res;
  }
};