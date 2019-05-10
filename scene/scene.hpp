#pragma once

#include <vector>

#include <core/point_light.hpp>
#include <primitives/base_primitive.hpp>

class Scene {
public:
  Scene() = default;

  void loadGeometry(const std::string &scene_filename);

  std::vector<PrimRef> primitives;
  std::vector<PointLight> lightSources;
};

typedef std::shared_ptr<Scene> SceneRef;