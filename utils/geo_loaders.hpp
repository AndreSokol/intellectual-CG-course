#pragma once

#include <string>
#include "../Material.hpp"
#include <vector>
#include "../primitives/Triangle.hpp"

namespace geo_loaders {
    Tris LoadObj(const std::string &filename, const Vec3 &pos, const Material &mat);
}