#pragma once

class Vec3 {
 public:
  double x, y, z;

  Vec3() {};

  Vec3(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }

  const Vec3 reflectOver(const Vec3 &other) const;

  double &operator[](int i) {
    if (i == 0) return x;
    if (i == 1) return y;
    return z;
  };

  const double &operator[](int i) const {
    if (i == 0) return x;
    if (i == 1) return y;
    return z;
  };

  friend const Vec3 operator*(const double &a, const Vec3 &v) {
    return Vec3(v.x * a, v.y * a, v.z * a);
  }

  friend const Vec3 operator+(const Vec3 &a, const Vec3 &b) {
    return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
  }

  friend const Vec3 operator-(const Vec3 &a, const Vec3 &b) {
    return a + (-1 * b);
  }

  const Vec3 operator*(const double &a) {
    return a * *this;
  }

  Vec3 &operator*=(const double &a);

  Vec3 operator-() const {
    return -1 * *this;
  };

  double length() const;
};

Vec3 normalize(const Vec3 &v);

double dot(const Vec3 &a, const Vec3 &b);

double cos(const Vec3 &a, const Vec3 &b);

double pcos(const Vec3 &a, const Vec3 &b);
