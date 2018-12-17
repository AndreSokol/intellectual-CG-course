//
// Created by andresokol on 21.11.18.
//

#include "bvh.h"

#include <iostream>
#include <limits>
#include "bounding_box.h"

struct BoxLessMax {
    BoxLessMax(int axis) : axis(axis) {}

    bool operator()(const TriangleRef &p1, const TriangleRef &p2) const {
        return (p1->box.bbmax[axis] < p2->box.bbmax[axis]);
    }

    int axis;
};


void BVHNode::build(const Tris &tris) {
    int TRIS_COUNT = tris.size();

    std::cout << "TRIS_CNT=" << TRIS_COUNT << "\n";

    if (TRIS_COUNT <= 2) {
        primitives = tris;
        return;
    }

    std::vector<Tris> sortedTris = {tris, tris, tris};

    for (const int i : {0, 1, 2}) {
        std::sort(sortedTris[i].begin(), sortedTris[i].end(), BoxLessMax(i));
    }


    int min_axis, min_i;
    double min_sep, min_sah = std::numeric_limits<double>::max();
    for (int axis: {0, 1, 2}) {
//            std::cout << "### axis " << axis << " \n";
        double min_coord = sortedTris[axis][0]->box.bbmin[axis];
        double max_coord = sortedTris[axis][TRIS_COUNT - 1]->box.bbmax[axis];
        for (int i = 0; i + 1 < TRIS_COUNT; i++) {
            double current_sah = (sortedTris[axis][i]->box.bbmax[axis] - min_coord) * i +
                                 (max_coord - sortedTris[axis][i]->box.bbmax[axis]) * (TRIS_COUNT - i);

//                std::cout << current_sah << std::endl;
//                std::cout << i << std::endl;

            if (current_sah < min_sah) {
//                std::cout << "take " << i << "\n";
                min_i = i;
                min_sah = current_sah;
                min_axis = axis;
                min_sep = sortedTris[axis][i]->box.bbmax[axis];
            }
        }
    }

//        std::cout << "min_axis=" << min_axis << " min_sep=" << min_sep << " min_sah" << min_sah << " TRIS_COUNT="
//                  << TRIS_COUNT << "\n";

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
}
