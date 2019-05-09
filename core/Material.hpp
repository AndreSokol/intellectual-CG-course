#pragma once

#include <memory>

#include "../utils/Color.hpp"

class Material {
 public:
  Color diffuseColor = Color(0, 0, 0);
  double specular = 0;
  double reflective = 0;

  Material() = default;

  Material(Color diffuseColor, double specular, double reflective = 0.0)
      : diffuseColor(diffuseColor), specular(specular), reflective(reflective) {}
};

typedef std::shared_ptr<Material> MatRef;
