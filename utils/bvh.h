#pragma once

#include "../primitives/Triangle.hpp"

#include <vector>
#include <memory>

class BVHNode {
public:
    std::shared_ptr<BVHNode> left;
    std::shared_ptr<BVHNode> right;
    BBox bbox;

    Tris primitives;

    void build(const Tris &tris);
};

typedef std::shared_ptr<BVHNode> BVHPtr;

BVHPtr buildBVH(const Tris &tris) {
    BVHPtr root = std::make_shared<BVHNode>();
    root->build(tris);

    return root;
}