#include "bvh.hpp"

#include <iostream>
#include <limits>

#include <utils/bounding_box.hpp>

struct BoxLessMax {
  BoxLessMax(int axis) : axis(axis) {}

  bool operator()(const TriangleRef &p1, const TriangleRef &p2) const {
    return (p1->box.bbmax[axis] < p2->box.bbmax[axis]);
  }

  int axis;
};

void BVHNode::updateBbox(const Tris &tris) {
  for (int axis : {0, 1, 2}) {
    for (const auto &tri : tris) {
      for (int vertex : {0, 1, 2}) {
        bbox.bbmin[axis] =
            std::min(bbox.bbmin[axis], tri->operator[](vertex)[axis]);
        bbox.bbmax[axis] =
            std::max(bbox.bbmax[axis], tri->operator[](vertex)[axis]);
      }
    }
  }
}

void BVHNode::build(const Tris &tris) {
  int TRIS_COUNT = tris.size();

  updateBbox(tris);

  if (TRIS_COUNT <= 2) {
    primitives = tris;
    std::cout << *this << std::endl;
    return;
  }

  std::vector<Tris> sortedTris = {tris, tris, tris};

  for (const int i : {0, 1, 2}) {
    std::sort(sortedTris[i].begin(), sortedTris[i].end(), BoxLessMax(i));
  }

  int min_axis = 0, min_i = 0;
  double min_sah = std::numeric_limits<double>::max();
  for (int axis : {0, 1, 2}) {
    double min_coord = sortedTris[axis][0]->box.bbmin[axis];
    double max_coord = sortedTris[axis][TRIS_COUNT - 1]->box.bbmax[axis];
    for (int i = 0; i + 1 < TRIS_COUNT; i++) {
      double current_sah =
          (sortedTris[axis][i]->box.bbmax[axis] - min_coord) * i +
          (max_coord - sortedTris[axis][i]->box.bbmax[axis]) * (TRIS_COUNT - i);

      if (current_sah < min_sah) {
        min_i = i;
        min_sah = current_sah;
        min_axis = axis;
      }
    }
  }

  Tris children;
  for (int i = 0; i < min_i + 1; i++) {
    children.emplace_back(sortedTris[min_axis][i]);
  }
  this->left = std::make_shared<BVHNode>();
  this->left->build(children);

  children.resize(0);
  for (int i = min_i + 1; i < TRIS_COUNT; i++) {
    children.emplace_back(sortedTris[min_axis][i]);
  }
  this->right = std::make_shared<BVHNode>();
  this->right->build(children);

  //  std::cout << *this << std::endl;
}

bool BVHNode::findIntersection(TriangleRef &triangle, double &t, const Vec3 &O,
                               const Vec3 &R) {
  const auto &bbox_intersection = bbox.isIntersecting(O, R);

  if (!bbox_intersection.is_intersecting || t < bbox_intersection.tmin ||
      bbox_intersection.tmax < 0) {
    return false;
  }

  if (!left) {
    bool is_intersecting = false;
    for (const auto &prim : primitives) {
      double dt;
      if (prim->intersect(O, R, dt) && dt < t) {
        t = dt;
        triangle = prim;
        is_intersecting = true;
      }
    }

    return is_intersecting;
  }

  return left->findIntersection(triangle, t, O, R) ||
         right->findIntersection(triangle, t, O, R);
}

void drawBVH(BVHPtr node, int d) {
  if (node == nullptr)
    return;

  drawBVH(node->left, d + 1);

  for (int i = 0; i < d; i++) {
    std::cout << " ";
  }
  std::cout << node->primitives.size() << std::endl;

  drawBVH(node->right, d + 1);
}

BVHPtr buildBVH(const Tris &tris) {
  BVHPtr root = std::make_shared<BVHNode>();
  root->build(tris);

  drawBVH(root, 0);
  return root;
}

std::ostream &operator<<(std::ostream &os, BVHNode &node) {
  return os << "Tris: " << node.primitives.size() << ", bbox: " << node.bbox;
}