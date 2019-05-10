#pragma once

#include <sstream>
#include <stdint.h>

#include <base/vec3.hpp>

class Color : public Vec3 {
public:
  Color() : Vec3(){};

  Color(double x, double y, double z) : Vec3(x / 255.0, y / 255.0, z / 255.0){};

  Color(Vec3 vec) : Vec3(vec){};

  Color(const std::string &color_str) {
    const auto s = color_str.substr(1);

    int hex_color;
    std::istringstream(s) >> std::hex >> hex_color;

    int r = hex_color / 65536;
    int g = (hex_color / 256) % 256;
    int b = hex_color % 256;

    x = (double)r / 255.0;
    y = (double)g / 255.0;
    z = (double)b / 255.0;
  }

  Color &operator+=(const Color &other) {
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    return *this;
  }

  uint8_t r() { return this->normalize_color_component(this->x); };

  uint8_t g() { return this->normalize_color_component(this->y); };

  uint8_t b() { return this->normalize_color_component(this->z); };

  uint8_t normalize_color_component(double val) {
    if (val < 0)
      return 0;
    if (val > 1)
      return 255;
    return uint8_t(val * 255);
  };
};
