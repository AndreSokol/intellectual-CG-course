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

void BaseRenderer::WtoS(const double &Cx, const double &Cy, double &Sx, double &Sy) {
  Sx = Cx + double(settings->WIDTH) / 2.0;
  Sy = double(settings->HEIGHT) / 2.0 - Cy;
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

void BaseRenderer::putPixel(int x, int y, Color c) {
  draw_mutex.lock();
  SDL_SetRenderDrawColor(_renderer, c.r(), c.g(), c.b(), SDL_ALPHA_OPAQUE);
  if (settings->SCALING_ENABLED) {
    SDL_RenderDrawPoint(_renderer, 2 * x, 2 * y);
    SDL_RenderDrawPoint(_renderer, 2 * x + 1, 2 * y);
    SDL_RenderDrawPoint(_renderer, 2 * x, 2 * y + 1);
    SDL_RenderDrawPoint(_renderer, 2 * x + 1, 2 * y + 1);
  } else {
    SDL_RenderDrawPoint(_renderer, x, y);
  }
  draw_mutex.unlock();
}