#pragma once

#include "../utils/Color.hpp"
#include "../utils/vec3.hpp"

class PointLight {
public:
  Color color;
  Vec3 position;

  PointLight() = default;

  PointLight(const Vec3 &p, const Color &c) {
    this->position = p;
    this->color = c;
  }
};
