#pragma once

#include <renderers/base_renderer.hpp>
#include <primitives/triangle.hpp>
#include <primitives/sphere.hpp>

class WireframeRenderer : public BaseRenderer {
 public:
  WireframeRenderer(std::shared_ptr<Settings> settings, SceneRef scene)
      : BaseRenderer(std::move(settings), std::move(scene)) {};

  void render() override;

 private:
  void draw(const TriangleRef &t);
  void draw(const SphereRef &t);
};
