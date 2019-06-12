#include <renderers/base_renderer.hpp>
#include "triangle.hpp"

Triangle::Triangle(const Vec3 &A, const Vec3 &B, const Vec3 &C, const Vec3 &N,
                   const MatRef &mat) : BasePrimitive(mat) {
  this->A = A;
  this->B = B;
  this->C = C;
  this->N = N;
  this->mat = mat;

  for (const auto &i : {0, 1, 2}) {
    for (const auto &j : {0, 1, 2}) {
      box.bbmin[i] = std::min(box.bbmin[i], this->operator[](j)[i]);
      box.bbmax[i] = std::max(box.bbmax[i], this->operator[](j)[i]);
    }
  }
};

Vec3 Triangle::normal(const Vec3 &P) { return this->N; };

Vec3 &Triangle::operator[](int i) {
  if (i == 0)
    return A;
  if (i == 1)
    return B;
  return C;
}

const Vec3 &Triangle::operator[](int i) const {
  if (i == 0)
    return A;
  if (i == 1)
    return B;
  return C;
}

bool Triangle::intersect(const Vec3 &O, const Vec3 &R, double &t) {
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

  if (alpha < -FLOAT_PRECISION || beta < -FLOAT_PRECISION ||
      alpha + beta > 1 + FLOAT_PRECISION) {
    return false;
  }

  t = gamma;
  return true;
}

double Triangle::matrixDet(const Vec3 &I, const Vec3 &J, const Vec3 &K) {
  return I.x * J.y * K.z + J.x * K.y * I.z + K.x * I.y * J.z -
      (I.x * K.y * J.z + J.x * I.y * K.z + K.x * J.y * I.z);
}

std::ostream &operator<<(std::ostream &os, TriangleRef &t) {
  return os << "[" << t->A << ", " << t->B << "," << t->C << "]";
}