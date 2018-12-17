#pragma once

#include "../utils/vec3.hpp"
#include "../core/Material.hpp"
#include "../core/gl_const.hpp"
#include "../utils/bounding_box.hpp"

#include <algorithm>
#include <memory>
#include <vector>

class Triangle {
private:

public:
    Vec3 A = Vec3(0, 0, 0);
    Vec3 B = Vec3(0, 0, 0);
    Vec3 C = Vec3(0, 0, 0);
    Vec3 N = Vec3(1, 0, 0);
    Material mat;
    BBox box;


    Triangle() = default;

    Triangle(const Vec3 &A, const Vec3 &B, const Vec3 &C, const Vec3 &N, const Material &mat) {
        this->A = A;
        this->B = B;
        this->C = C;
        this->N = N;
        this->mat = mat;

        for (const auto &i: {0, 1, 2}) {
            for (const auto &j: {0, 1, 2}) {
                box.bbmin[i] = std::min(box.bbmin[i], this->operator[](j)[i]);
                box.bbmax[i] = std::max(box.bbmax[i], this->operator[](j)[i]);
            }
        }
    };

    Vec3 normal(const Vec3 &P) {
        return this->N;
    };

    Vec3 &operator[](int i) {
        if (i == 0) return A;
        if (i == 1) return B;
        return C;
    }

    const Vec3 &operator[](int i) const {
        if (i == 0) return A;
        if (i == 1) return B;
        return C;
    }

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

        if (alpha < -FLOAT_PRECISION || beta < -FLOAT_PRECISION || alpha + beta > 1 + FLOAT_PRECISION) {
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

typedef std::shared_ptr<Triangle> TriangleRef;

typedef std::vector<TriangleRef> Tris;