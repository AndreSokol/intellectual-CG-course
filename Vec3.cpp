//
// Created by andresokol on 29.01.2018.
//

#include "Vec3.h"
#include <math.h>

Vec3 Vec3::operator*(const double &other) const {
    return Vec3(this->x * other, this->y * other, this->z * other);
}

Vec3 Vec3::operator+(const Vec3 & other) const {
    return Vec3(this->x + other.x, this->y + other.y, this->z + other.z);
}

Vec3 Vec3::operator-(const Vec3 & other) const {
    return Vec3(this->x - other.x, this->y - other.y, this->z - other.z);
}

Vec3 Vec3::reflectOver(const Vec3& other) const {
    return other * (2 * dot(*this, other)) + *this * -1.0;
}

double Vec3::length() const {
    return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

double dot(const Vec3 &a, const Vec3 &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

double cos(const Vec3 &a, const Vec3 &b) {
    return dot(a, b) / a.length() / b.length();
}