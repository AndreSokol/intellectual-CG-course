#ifndef STUPID_RENDER_TRIANGLE_H
#define STUPID_RENDER_TRIANGLE_H

#include "../Vec3.h"
#include "../Material.h"
#include "../gl_const.h"

class Triangle : public BasePrimitive {
private:

public:
    Vec3 A = Vec3(0, 0, 0);
    Vec3 B = Vec3(0, 0, 0);
    Vec3 C = Vec3(0, 0, 0);
    Vec3 N = Vec3(1, 0, 0);

    Triangle() {};
    Triangle(const Vec3 &A, const Vec3 &B, const Vec3 &C, const Vec3 &N, const Material &mat) {
        this->A = A;
        this->B = B;
        this->C = C;
        this->N = N;
        this->mat = mat;
    };

    Vec3 normal(const Vec3 &P) {
        return this->N;
    };

    bool intersect(const Vec3 &O, const Vec3 &R, double &t) {
        Vec3 P = this->C - this->A;
        Vec3 Q = this->B - this->A;
        Vec3 S = this->A - O;


        double det = matrixDet(P, Q, -R);
        if (det == 0) {
            return false;
        }

        double alpha = matrixDet(-S, Q, -R) / det;
        double beta = matrixDet(P, -S, -R) / det;
        double gamma = matrixDet(P, Q, -S) / det;

        if (alpha < - FLOAT_PRECISION || beta < - FLOAT_PRECISION || alpha + beta > 1 + FLOAT_PRECISION) {
            return false;
        }

        t = gamma;
        return true;
    }

    double matrixDet(const Vec3 &I, const Vec3 &J, const Vec3 &K) {
        return I.x * J.y * K.z + J.x * K.y * I.z + K.x * I.y * J.z - (
               I.x * K.y * J.z + J.x * I.y * K.z + K.x * J.y * I.z);
    }
};


#endif //STUPID_RENDER_TRIANGLE_H
