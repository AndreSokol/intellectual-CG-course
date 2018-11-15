#pragma once

#include "../Color.h"
#include "../Material.h"
#include <vector>

class BasePrimitive {
public:
    Material mat;

    BasePrimitive() {};

    BasePrimitive(const Material &mat) {
        this->mat = mat;
    }

    Vec3 normal(const Vec3 &P) {
        return Vec3(0, 0, 0);
    };

    bool intersect(const Vec3 &O, const Vec3 &R, double &t) {
        return false;
    }
};
