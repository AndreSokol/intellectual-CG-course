#pragma once

#include <memory>
#include <mutex>

#include <SDL.h>

#include <core/settings.hpp>
#include <primitives/base_primitive.hpp>
#include <scene/scene.hpp>

class BaseRenderer {
 public:
  BaseRenderer() = default;
  BaseRenderer(std::shared_ptr<Settings> settings, SceneRef scene)
      : settings(std::move(settings)), scene(std::move(scene)) {}
  ~BaseRenderer() = default;

  void init();
  void deinit();

  virtual void render() = 0;

  void StoW(const double &Sx, const double &Sy, double &Cx, double &Cy);
  void WtoS(const double &Cx, const double &Cy, double &Sx, double &Sy);

  bool findIntersection(const Vec3 &O, const Vec3 &R, double &closest_t,
                        PrimRef &intersected_primitive);
  SceneRef scene;

  void putPixel(int x, int y, Color c);

 protected:
  std::shared_ptr<Settings> settings;
  SDL_Renderer *_renderer = nullptr;
  SDL_Window *_window = nullptr;
  std::mutex draw_mutex;
};
