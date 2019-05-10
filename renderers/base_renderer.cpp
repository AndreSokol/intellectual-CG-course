#include "base_renderer.hpp"

#include <SDL.h>

#include <core/gl_const.hpp>
#include <primitives/base_primitive.hpp>

void BaseRenderer::init() {
  SDL_Init(SDL_INIT_VIDEO);
  _window = SDL_CreateWindow("Stupid Renderer", 10, 10, settings->WIDTH * 2,
                             settings->HEIGHT * 2, SDL_WINDOW_SHOWN);
  _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_SOFTWARE);
  SDL_RenderClear(_renderer);
}

void BaseRenderer::deinit() {
  SDL_DestroyWindow(_window);
  SDL_Quit();
}

void BaseRenderer::StoW(const double &Sx, const double &Sy, double &Cx,
                        double &Cy) {
  Cx = Sx;
  Cy = Sy;

  Cx = Cx - double(settings->WIDTH) / 2.0;
  Cy = -(Cy - double(settings->HEIGHT) / 2.0);
}

bool BaseRenderer::findIntersection(const Vec3 &O, const Vec3 &R,
                                    double &closest_t,
                                    PrimRef &intersected_primitive) {
  double t;
  bool is_intersected;
  closest_t = CLIPPING_DIST;

  for (const auto &prim : scene->primitives) {
    is_intersected = prim->intersect(O, R, t);

    if (!is_intersected)
      continue;

    if (t < closest_t && t > FLOAT_PRECISION) {
      closest_t = t;
      intersected_primitive = prim;
    }
  }

  return closest_t < CLIPPING_DIST - FLOAT_PRECISION;
}
