#pragma once

#include <renderers/base_renderer.hpp>
#include <utils/task_queue.hpp>

class SamplerRenderer : public BaseRenderer {
 public:
  SamplerRenderer(std::shared_ptr<Settings> settings, SceneRef scene)
      : BaseRenderer(std::move(settings), std::move(scene)) {};

  void render() override;

 private:
  Color traceRay(const Vec3 &O, const Vec3 &R);
  Color calculateLighting(const Vec3 &P, const Vec3 &V, PrimRef &prim);
  void renderPixel(render_queue::Queue &rqueue, const Vec3 &O, int tid,
                   int total_tasks);

};
