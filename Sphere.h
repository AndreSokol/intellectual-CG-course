//
// Created by andresokol on 29.01.2018.
//

#ifndef STUPID_RENDER_SPHERE_H
#define STUPID_RENDER_SPHERE_H

#include "Vec3.h"
#include "Color.h"
#include <vector>

class Sphere {
public:
    Vec3 center;
    double radius;
    Color color;
    double specular;
    double reflective;

    Sphere(double x, double y, double z,
           double r,
           Color color,
           double specular, double reflective);
};


#endif //STUPID_RENDER_SPHERE_H
