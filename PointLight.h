#pragma once

#include "Color.h"
#include "Vec3.h"

class PointLight {
public:
    Color color;
    Vec3 position;

    PointLight() {};

    PointLight(const Vec3 &p, const Color &c) {
        this->position = p;
        this->color = c;
    }

};
