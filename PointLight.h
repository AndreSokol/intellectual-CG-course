//
// Created by andresokol on 01.02.2018.
//

#ifndef STUPID_RENDER_POINTLIGHT_H
#define STUPID_RENDER_POINTLIGHT_H

#include "Color.h"
#include "Vec3.h"

class PointLight {
public:
    Color color;
    Vec3 position;

    PointLight(){};
    PointLight(const Vec3 &p, const Color &c) {
        this->position = p;
        this->color = c;
    }

};


#endif //STUPID_RENDER_POINTLIGHT_H
