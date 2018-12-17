//
// Created by andresokol on 22.11.18.
//

#include "bounding_box.h"


//void BBox::getBBoxForTriangle(const Triangle &tri) {
//    bbmin = Vec3{std::numeric_limits<double>::max(),
//                 std::numeric_limits<double>::max(),
//                 std::numeric_limits<double>::max()};
//    bbmax = Vec3{-std::numeric_limits<double>::max(),
//                 -std::numeric_limits<double>::max(),
//                 -std::numeric_limits<double>::max()};
//
//    for (const auto &i: {0, 1, 2}) {
//        for (const auto &j: {0, 1, 2}) {
//            bbmin[i] = std::min(bbmin[i], tri[j][i]);
//            bbmax[i] = std::max(bbmax[i], tri[j][i]);
//        }
//    }
//}