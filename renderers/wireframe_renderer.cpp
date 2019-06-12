#include "wireframe_renderer.hpp"

#include <chrono>
#include <iostream>

void WireframeRenderer::render() {
  Vec3 O = Vec3(0, 0, 0);
  const auto start_render = std::chrono::system_clock::now();

  for (auto prim: scene->primitives) {}

  SDL_RenderPresent(_renderer);
  const auto render_duration = std::chrono::system_clock::now() - start_render;
}

void WireframeRenderer::draw(const SphereRef &sphere) {
  const auto &center = sphere->center;

  double x;
  double y;

  StoW(center.x / center.z, center.y / center.z, x, y);

  putPixel(x, y, COLORS::RED);

  std::cout << x << " " << y << "\n";
}