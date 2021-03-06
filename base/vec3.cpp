#include "vec3.hpp"
#include <math.h>

const Vec3 Vec3::reflectOver(const Vec3 &other) const {
  Vec3 t = *this;
  return (2.0 * dot(t, other)) * other - t;
}

Vec3 &Vec3::operator*=(const double &a) {
  this->x *= a;
  this->y *= a;
  this->z *= a;
  return *this;
}

double Vec3::length() const {
  return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

Vec3 normalize(const Vec3 &v) { return 1.0 / v.length() * v; }

double dot(const Vec3 &a, const Vec3 &b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

double cos(const Vec3 &a, const Vec3 &b) {
  return dot(a, b) / a.length() / b.length();
}

double pcos(const Vec3 &a, const Vec3 &b) {
  double cosValue = cos(a, b);
  if (cosValue > 0)
    return cosValue;
  return 0;
}

std::ostream &operator<<(std::ostream &os, Vec3 &v) {
  return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}