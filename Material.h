#ifndef STUPID_RENDER_MATERIAL_H
#define STUPID_RENDER_MATERIAL_H

#include "Color.h"

class Material {
public:
    Color diffuseColor = Color(0, 0, 0);
    double specular = 0;
    double reflective = 0;

    Material() {};
    Material(Color diffuseColor, double specular, double reflective) {
        this->diffuseColor = diffuseColor;
        this->specular = specular;
        this->reflective = reflective;
    };
};


#endif //STUPID_RENDER_MATERIAL_H
