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

    Vec3 operator+ (const Vec3 &other) const;
    Vec3 operator- (const Vec3 &other) const;
    Vec3 operator* (const double &other) const;
    //Vec3 operator* (int other, Vec3 self);

    Vec3 reflectOver(const Vec3 &other) const;

    double length() const;
};

double dot(const Vec3 &a, const Vec3 &b);
double cos(const Vec3 &a, const Vec3 &b);

#endif //STUPID_RENDER_VEC3_H
