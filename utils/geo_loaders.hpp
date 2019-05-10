#pragma once

#include <string>
#include <vector>

#include <core/material.hpp>
#include <primitives/triangle.hpp>

namespace geo_loaders {
Tris LoadObj(const std::string &filename, const Vec3 &pos, const MatRef &mat);
}
