#pragma once

#include "vec3.hpp"
//#include "../primitives/Triangle.hpp"
#include <limits>

class BBox {
public:
    BBox() {};
    Vec3 bbmin = Vec3{std::numeric_limits<double>::max(),
                      std::numeric_limits<double>::max(),
                      std::numeric_limits<double>::max()};
    Vec3 bbmax = Vec3{-std::numeric_limits<double>::max(),
                      -std::numeric_limits<double>::max(),
                      -std::numeric_limits<double>::max()};

};