#pragma once

#include <base/color.hpp>
#include <base/vec3.hpp>

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
