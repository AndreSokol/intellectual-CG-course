#include "SDL.h"
#include <random>
#include <vector>
#include "utils/vec3.hpp"
//#include "primitives/Sphere.hpp"
#include "primitives/Triangle.hpp"
//#include "primitives/BasePrimitive.hpp"
#include <math.h>
#include "core/PointLight.hpp"
#include "core/Material.hpp"
#include "utils/geo_loaders.hpp"
#include "utils/task_queue.hpp"

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <mutex>
#include <algorithm>
#include <fstream>

#include "utils/bvh.hpp"

int WIDTH = 480;
int HEIGHT = 320;
int BIGGEST_WINDOW_SIZE = std::max(WIDTH, HEIGHT);
int D = 1;
int REFLECT_DEPTH_LIMIT = 2;

Color BACKGROUND_COLOR = Color(29, 33, 36);
Color AMBIENT = Color(0, 5, 10);

Tris triangles;
std::vector<PointLight> lightSources;

std::mutex draw_mutex;

BVHPtr BVH;

void StoW(const double &Sx, const double &Sy, double &Cx, double &Cy) {
  Cx = Sx;
  Cy = Sy;

  Cx = Cx - double(WIDTH) / 2.0;
  Cy = -(Cy - double(HEIGHT) / 2.0);

  return;
}

bool findIntersection(const Vec3 &O, const Vec3 &R,
                      double &closest_t, TriangleRef &triangle) {
  double t;
  bool is_intersected;
  closest_t = CLIPPING_DIST;

  for (size_t i = 0; i < triangles.size(); i += 1) {
    is_intersected = triangles[i]->intersect(O, R, t);

    if (!is_intersected) continue;

    if (t < closest_t && t > FLOAT_PRECISION) {
      closest_t = t;
      triangle = triangles[i];
    }
  }

  return closest_t < CLIPPING_DIST - FLOAT_PRECISION;
}

Color calculateLighting(const Vec3 &P, const Vec3 &V, TriangleRef sph) {
  Vec3 R = lightSources[0].position - P;
  Vec3 N = sph->normal(P);

  Color I = AMBIENT;

  double t;
  TriangleRef sph_id;
  bool is_in_shadow = findIntersection(P, R, t, sph_id);
  if (!is_in_shadow) {
    Material mat = sph->mat;
    I += mat.diffuseColor * (pcos(N, R) / R.length() / R.length() * 100);
  }

  return I;
}

Color traceRay(const Vec3 &O, const Vec3 &R) {
  double t = std::numeric_limits<double>::max();
//  int sph_id;

  TriangleRef triangle;
//  bool is_intersected = findIntersection(O, R, t, triangle);

  bool is_intersected = BVH->findIntersection(triangle, t, O, R);
//  std::cout << (is_intersected == true) << " " << (triangle == nullptr) << std::endl;
//  if (is_intersected && triangle == nullptr) {
//    t = std::numeric_limits<double>::max();;
//    is_intersected = BVH->findIntersection(triangle, t, O, R);
//  }

  if (!is_intersected) return BACKGROUND_COLOR;

  Color c = calculateLighting(O + t * R, R, triangle);
  return c;
}

void loadGeometry() {
  std::vector<Material> mats{Material(Color(242, 76, 39), 0.1),
                             Material(Color(76, 242, 39), 1000),
                             Material(Color(100, 100, 10), 0.1),
                             Material(Color(10, 100, 242), 0.1)};
  std::vector<Vec3> positions{Vec3(-2, 0, 8), Vec3(0, 0, 8), Vec3(2, 0, 8)};

  lightSources.emplace_back(Vec3(0, 10, 10), Color(255, 255, 255));

  std::ifstream input("../geometry_samples/scene");

  while (input.peek() != EOF) {
    double x, y, z;
    std::string obj_name;
    int mat_id;
    input >> x >> y >> z >> obj_name >> mat_id;

    const auto &pyramid_tris =
        geo_loaders::LoadObj("../geometry_samples/" + obj_name, Vec3(x, y, z), mats.at(mat_id));

    for (const auto &tri: pyramid_tris) {
      triangles.push_back(tri);
    }
  }
}

void renderPixel(render_queue::Queue &rqueue, SDL_Renderer *renderer, const Vec3 &O, int tid, int total_tasks) {
  render_queue::Task task;

  while (rqueue.pop(task)) {
    for (int i = task.s_x; i < task.f_x; i++) {
      for (int j = task.s_y; j < task.f_y; j++) {
        double Cx, Cy;
        StoW(i, j, Cx, Cy);
        Vec3 R = Vec3(Cx / BIGGEST_WINDOW_SIZE, Cy / BIGGEST_WINDOW_SIZE, 1) * D;
        Color c = traceRay(O, normalize(R));

        if (SSAA_ENABLED) {
          c = c * 0.25;

          StoW(i + 0.5, j + 0.5, Cx, Cy);
          R = Vec3(Cx / BIGGEST_WINDOW_SIZE, Cy / BIGGEST_WINDOW_SIZE, 1) * D;
          c += 0.25 * traceRay(O, normalize(R));

          StoW(i, j + 0.5, Cx, Cy);
          R = Vec3(Cx / BIGGEST_WINDOW_SIZE, Cy / BIGGEST_WINDOW_SIZE, 1) * D;
          c += 0.25 * traceRay(O, normalize(R));

          StoW(i + 0.5, j, Cx, Cy);
          R = Vec3(Cx / BIGGEST_WINDOW_SIZE, Cy / BIGGEST_WINDOW_SIZE, 1) * D;
          c += 0.25 * traceRay(O, normalize(R));
        }

        draw_mutex.lock();
        SDL_SetRenderDrawColor(renderer, c.r(), c.g(), c.b(), SDL_ALPHA_OPAQUE);
//        SDL_RenderDrawPoint(renderer, i, j);
        SDL_RenderDrawPoint(renderer, 2 * i, 2 * j);
        SDL_RenderDrawPoint(renderer, 2 * i + 1, 2 * j);
        SDL_RenderDrawPoint(renderer, 2 * i, 2 * j + 1);
        SDL_RenderDrawPoint(renderer, 2 * i + 1, 2 * j + 1);
        draw_mutex.unlock();
      }
    }
  }
}

int main(int argc, char *argv[]) {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *window = SDL_CreateWindow("Stupid Renderer", 100, 100, WIDTH * 2, HEIGHT * 2, SDL_WINDOW_SHOWN);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
  SDL_RenderClear(renderer);

  const auto start_geo_load = std::chrono::system_clock::now();
  loadGeometry();
  const auto geo_load_duration = std::chrono::system_clock::now() - start_geo_load;

  BVH = buildBVH(triangles);

  Vec3 O = Vec3(0, 0, 0);

//  const auto nproc = std::thread::hardware_concurrency() * 2;
  int nproc = 1;
  std::cout << "CPU units found: " << nproc << std::endl;

  double dlight = 0.4;
//    while (true) {
  dlight *= -1;
  for (int frame = 0; frame < 20; frame++) {
    lightSources[0].position = Vec3(dlight, 0, 0) + lightSources[0].position;
    render_queue::Queue rqueue(HEIGHT, WIDTH);

    const auto total_tasks = rqueue.size();
    std::cout << "Tasks generated: " << total_tasks << std::endl;

    const auto start_render = std::chrono::system_clock::now();
    std::vector<std::thread> threads;
    threads.reserve(nproc);
    for (int i = 0; i < nproc; i++) {
      std::thread t(renderPixel, std::ref(rqueue), renderer, O, i, total_tasks);
      threads.push_back(std::move(t));
    }
    for (auto &t: threads) {
      t.join();
    }
    SDL_RenderPresent(renderer);
    const auto render_duration = std::chrono::system_clock::now() - start_render;

    std::cout << "Rendered, time:\n";
    std::cout << "Load geometry: " << geo_load_duration.count() / 1000000 << "ms\n";
    std::cout << "Render: " << render_duration.count() / 1000000000.0 << "s\n";
    std::cout << "FPS: " << 1000000000.0 / render_duration.count() << "\n\n";
  }

//    }

//    SDL_Event event;
//    while (SDL_WaitEvent(&event) >= 0) {
//        if (event.type == SDL_QUIT) {
//            break;
//        }
//    }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
