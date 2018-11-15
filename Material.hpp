#pragma once

#include "Color.hpp"

class Material {
public:
    Color diffuseColor = Color(0, 0, 0);
    double specular = 0;
    double reflective = 0;

    Material() {};

    Material(Color diffuseColor, double specular, double reflective = 0.0) {
        this->diffuseColor = diffuseColor;
        this->specular = specular;
        this->reflective = reflective;
    };
};
