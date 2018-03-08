#ifndef STUPID_RENDER_TRIANGLE_H
#define STUPID_RENDER_TRIANGLE_H

#include "../Vec3.h"
#include "../Material.h"
#include "../gl_const.h"

class Triangle : public BasePrimitive {
public:
    Vec3 A = Vec3(0, 0, 0);
    Vec3 B = Vec3(0, 0, 0);
    Vec3 C = Vec3(0, 0, 0);

    Triangle() {};
    Triangle(const Vec3 &A, const Vec3 &B, const Vec3 &C, const Material &mat) {
        this->A = A;
        this->B = B;
        this->C = C;
        this->mat = mat;
    };

    Vec3 normal(const Vec3 &P) {
        return normalize(P - this->center);
    };

    bool intersect(const Vec3 &O, const Vec3 &R, double &t) {
        Vec3 C = O - this->center;

        double k1 = dot(R, R),
                k2 = 2 * dot(C, R),
                k3 = dot(C, C) - this->radius * this->radius;

        double det = k2 * k2 - 4 * k1 * k3;
        if (det < 0) return false;

        double t0 = (-k2 - sqrt(det)) / 2 / k1;
        double t1 = (-k2 + sqrt(det)) / 2 / k1;

        if (t0 > FLOATING_PRECISION && t0 < CLIPPING_DIST) {
            t = t0;
            return true;
        }

        if (t1 > FLOATING_PRECISION && t1 < CLIPPING_DIST) {
            t = t1;
            return true;
        }

        return false;
    }

};


#endif //STUPID_RENDER_TRIANGLE_H
