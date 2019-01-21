#include "bounding_box.hpp"

double BBox::volume() {
  const auto &diagonal = bbmax - bbmin;

  return diagonal.x * diagonal.y * diagonal.z;
}

BBox::IntersectionData BBox::isIntersecting(const Vec3 &O, const Vec3 &R) {
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

std::ostream &operator<<(std::ostream &os, BBox &bbox) {
  return os << bbox.bbmin << " <-> " << bbox.bbmax << ", volume=" << bbox.volume();
}
