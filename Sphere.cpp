//
// Created by andresokol on 29.01.2018.
//

#include "Sphere.h"
#include "Vec3.h"

Sphere::Sphere(double x, double y, double z, double r, Color color, double specular, double reflective) {
    this->center = Vec3(x, y, z);
    this->radius = r;

    this->color = color;

    this->specular = specular;
    this->reflective = reflective;
}

