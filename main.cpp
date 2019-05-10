#include "SDL.h"

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <math.h>
#include <mutex>
#include <random>
#include <thread>
#include <vector>

#include "core/material.hpp"
#include "core/point_light.hpp"
#include "primitives/base_primitive.hpp"
#include "primitives/sphere.hpp"
#include "primitives/triangle.hpp"
#include "settings.hpp"
#include "utils/bvh.hpp"
#include "utils/geo_loaders.hpp"
#include "utils/task_queue.hpp"
#include "utils/vec3.hpp"

typedef PrimRef ptr;

Settings settings;
Prims triangles;
std::vector<PointLight> lightSources;

std::mutex draw_mutex;

void StoW(const double &Sx, const double &Sy, double &Cx, double &Cy) {
  Cx = Sx;
  Cy = Sy;

  Cx = Cx - double(settings.WIDTH) / 2.0;
  Cy = -(Cy - double(settings.HEIGHT) / 2.0);
}

bool findIntersection(const Vec3 &O, const Vec3 &R, double &closest_t,
                      PrimRef &intersected_primitive) {
  double t;
  bool is_intersected;
  closest_t = CLIPPING_DIST;

  for (const auto &prim : triangles) {
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

Color calculateLighting(const Vec3 &P, const Vec3 &V, PrimRef &prim) {
  Vec3 R = lightSources[0].position - P;
  Vec3 N = prim->normal(P);

  Color I = settings.AMBIENT;

  double t = std::numeric_limits<double>::max();
  PrimRef sph_id;
  bool is_in_shadow = findIntersection(P, R, t, sph_id);
  if (pcos(N, R) >= 0 && !is_in_shadow) {
    I += prim->mat->diffuseColor * pcos(N, R);
  }

  return I;
}

Color traceRay(const Vec3 &O, const Vec3 &R) {
  double t = std::numeric_limits<double>::max();

  PrimRef prim;
  bool is_intersected = findIntersection(O, R, t, prim);

  if (!is_intersected)
    return settings.BACKGROUND_COLOR;

  Color c = calculateLighting(O + t * R, R, prim);
  return c;
}

void loadGeometry() {
  std::vector<Material> mats{
      Material(Color(242, 76, 39), 0.1), Material(Color(76, 242, 39), 1000),
      Material(Color(100, 100, 10), 0.1), Material(Color(10, 100, 242), 0.1)};
  std::vector<Vec3> positions{Vec3(-2, 0, 8), Vec3(0, 0, 8), Vec3(2, 0, 8)};

  lightSources.emplace_back(Vec3(-2, 10, 10), Color(255, 255, 255));
  triangles.push_back(std::make_shared<Sphere>(
      Vec3(1, -1, 10), 1.0, std::make_shared<Material>(mats[0])));

  std::ifstream input("../geometry_samples/scene");

  while (input.peek() != EOF) {
    double x, y, z;
    std::string obj_name;
    int mat_id;
    input >> x >> y >> z >> obj_name >> mat_id;

    const auto &pyramid_tris =
        geo_loaders::LoadObj("../geometry_samples/" + obj_name, Vec3(x, y, z),
                             std::make_shared<Material>(mats.at(mat_id)));

    for (const auto &tri : pyramid_tris) {
      triangles.push_back(tri);
    }
  }
}

void renderPixel(render_queue::Queue &rqueue, SDL_Renderer *renderer,
                 const Vec3 &O, int tid, int total_tasks) {
  render_queue::Task task;

  while (rqueue.pop(task)) {
    for (int i = task.s_x; i < task.f_x; i++) {
      for (int j = task.s_y; j < task.f_y; j++) {
        double Cx, Cy;
        StoW(i, j, Cx, Cy);
        Vec3 R = Vec3(Cx / settings.BIGGEST_WINDOW_SIZE,
                      Cy / settings.BIGGEST_WINDOW_SIZE, 1) *
                 settings.D;
        Color c = traceRay(O, normalize(R));

        if (settings.SSAA_ENABLED) {
          c = c * 0.25;

          StoW(i + 0.5, j + 0.5, Cx, Cy);
          R = Vec3(Cx / settings.BIGGEST_WINDOW_SIZE,
                   Cy / settings.BIGGEST_WINDOW_SIZE, 1) *
              settings.D;
          c += 0.25 * traceRay(O, normalize(R));

          StoW(i, j + 0.5, Cx, Cy);
          R = Vec3(Cx / settings.BIGGEST_WINDOW_SIZE,
                   Cy / settings.BIGGEST_WINDOW_SIZE, 1) *
              settings.D;
          c += 0.25 * traceRay(O, normalize(R));

          StoW(i + 0.5, j, Cx, Cy);
          R = Vec3(Cx / settings.BIGGEST_WINDOW_SIZE,
                   Cy / settings.BIGGEST_WINDOW_SIZE, 1) *
              settings.D;
          c += 0.25 * traceRay(O, normalize(R));
        }

        draw_mutex.lock();
        SDL_SetRenderDrawColor(renderer, c.r(), c.g(), c.b(), SDL_ALPHA_OPAQUE);
        if (settings.SCALING_ENABLED) {
          SDL_RenderDrawPoint(renderer, 2 * i, 2 * j);
          SDL_RenderDrawPoint(renderer, 2 * i + 1, 2 * j);
          SDL_RenderDrawPoint(renderer, 2 * i, 2 * j + 1);
          SDL_RenderDrawPoint(renderer, 2 * i + 1, 2 * j + 1);
        } else {
          SDL_RenderDrawPoint(renderer, i, j);
        }
        draw_mutex.unlock();
      }
    }
  }
}

int main(int argc, char *argv[]) {
  settings.init_from_args(argc, argv);

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *window =
      SDL_CreateWindow("Stupid Renderer", 100, 100, settings.WIDTH * 2,
                       settings.HEIGHT * 2, SDL_WINDOW_SHOWN);
  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
  SDL_RenderClear(renderer);

  const auto start_geo_load = std::chrono::system_clock::now();
  loadGeometry();
  const auto geo_load_duration =
      std::chrono::system_clock::now() - start_geo_load;

  Vec3 O = Vec3(0, 0, 0);

  const auto nproc = std::thread::hardware_concurrency() * 2;
  // int nproc = 1;
  std::cout << "CPU units found: " << nproc << std::endl;

  for (auto x : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
    render_queue::Queue rqueue(settings.HEIGHT, settings.WIDTH,
                               settings.BLOCK_SIZE);

    const auto total_tasks = rqueue.size();
    std::cout << "Tasks generated: " << total_tasks << std::endl;

    O = O + Vec3(-1, 0, 0);
    const auto start_render = std::chrono::system_clock::now();
    std::vector<std::thread> threads;
    threads.reserve(nproc);
    for (int i = 0; i < nproc; i++) {
      std::thread t(renderPixel, std::ref(rqueue), renderer, O, i, total_tasks);
      threads.push_back(std::move(t));
    }
    for (auto &t : threads) {
      t.join();
    }
    SDL_RenderPresent(renderer);
    const auto render_duration =
        std::chrono::system_clock::now() - start_render;

    std::cout << "Rendered, time:\n";
    std::cout << "Load geometry: " << geo_load_duration.count() / 1000000
              << "ms\n";
    std::cout << "Render: " << render_duration.count() / 1000000000.0 << "s\n";
    std::cout << "FPS: " << 1000000000.0 / render_duration.count() << "\n\n";
  }

  SDL_Event event;
  while (SDL_WaitEvent(&event) >= 0) {
    if (event.type == SDL_QUIT) {
      break;
    }
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
