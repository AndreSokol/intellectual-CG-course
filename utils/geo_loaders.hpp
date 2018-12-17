#pragma once

#include "../core/Material.hpp"
#include "../primitives/Triangle.hpp"

#include <string>
#include <vector>


namespace geo_loaders {
    Tris LoadObj(const std::string &filename, const Vec3 &pos, const Material &mat);
}