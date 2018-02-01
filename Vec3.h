//
// Created by andresokol on 29.01.2018.
//

#ifndef STUPID_RENDER_VEC3_H
#define STUPID_RENDER_VEC3_H


class Vec3 {
public:
    double x, y, z;

    Vec3(){};
    Vec3(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    const Vec3 reflectOver(const Vec3 &other) const;


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

    Vec3& operator*= (const double &a);

    double length() const;
};

Vec3 normalize(const Vec3 &v);
double dot(const Vec3 &a, const Vec3 &b);
double cos(const Vec3 &a, const Vec3 &b);

#endif //STUPID_RENDER_VEC3_H
