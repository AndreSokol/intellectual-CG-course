//
// Created by andresokol on 29.01.2018.
//

#ifndef STUPID_RENDER_COLOR_H
#define STUPID_RENDER_COLOR_H


#include <stdint.h>
#include "Vec3.h"

class Color : public Vec3 {
public:
    Color():Vec3() {};
    Color(double x, double y, double z):Vec3(x / 255.0, y / 255.0, z / 255.0){};
    Color(Vec3 vec):Vec3(vec) {};

    uint8_t r() {
        return this->normalize_color_component(this->x);
    };
    uint8_t g() {
        return this->normalize_color_component(this->y);
    };
    uint8_t b() {
        return this->normalize_color_component(this->z);
    };

    uint8_t normalize_color_component(double val) {
        if (val < 0) return 0;
        if (val > 1) return 255;
        return uint8_t(val * 255);
    };
};


#endif //STUPID_RENDER_COLOR_H