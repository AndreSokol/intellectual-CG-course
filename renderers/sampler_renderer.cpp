#include "sampler_renderer.hpp"

#include <iostream>
#include <thread>

Color SamplerRenderer::calculateLighting(const Vec3 &P, const Vec3 &V,
                                         PrimRef &prim) {
  Vec3 R = scene->lightSources[0].position - P;
  Vec3 N = prim->normal(P);

  Color I = settings->AMBIENT;

  double t = std::numeric_limits<double>::max();
  PrimRef sph_id;
  bool is_in_shadow = findIntersection(P, R, t, sph_id);
  if (pcos(N, R) >= 0 && !is_in_shadow) {
    I += prim->mat->diffuseColor * pcos(N, R);
  }

  return I;
}

Color SamplerRenderer::traceRay(const Vec3 &O, const Vec3 &R) {
  double t = std::numeric_limits<double>::max();

  PrimRef prim;
  bool is_intersected = findIntersection(O, R, t, prim);

  if (!is_intersected)
    return settings->BACKGROUND_COLOR;

  Color c = calculateLighting(O + t * R, R, prim);
  return c;
}

void SamplerRenderer::renderPixel(render_queue::Queue &rqueue, const Vec3 &O,
                                  int tid, int total_tasks) {
  render_queue::Task task;

  while (rqueue.pop(task)) {
    for (int i = task.s_x; i < task.f_x; i++) {
      for (int j = task.s_y; j < task.f_y; j++) {
        double Cx, Cy;
        StoW(i, j, Cx, Cy);
        Vec3 R = Vec3(Cx / settings->BIGGEST_WINDOW_SIZE,
                      Cy / settings->BIGGEST_WINDOW_SIZE, 1) *
                 settings->D;
        Color c = traceRay(O, normalize(R));

        if (settings->SSAA_ENABLED) {
          c = c * 0.25;

          StoW(i + 0.5, j + 0.5, Cx, Cy);
          R = Vec3(Cx / settings->BIGGEST_WINDOW_SIZE,
                   Cy / settings->BIGGEST_WINDOW_SIZE, 1) *
              settings->D;
          c += 0.25 * traceRay(O, normalize(R));

          StoW(i, j + 0.5, Cx, Cy);
          R = Vec3(Cx / settings->BIGGEST_WINDOW_SIZE,
                   Cy / settings->BIGGEST_WINDOW_SIZE, 1) *
              settings->D;
          c += 0.25 * traceRay(O, normalize(R));

          StoW(i + 0.5, j, Cx, Cy);
          R = Vec3(Cx / settings->BIGGEST_WINDOW_SIZE,
                   Cy / settings->BIGGEST_WINDOW_SIZE, 1) *
              settings->D;
          c += 0.25 * traceRay(O, normalize(R));
        }

        putPixel(i, j, c);
      }
    }
  }
}

void SamplerRenderer::render() {
  //  const auto nproc = std::thread::hardware_concurrency() * 2;
  Vec3 O = Vec3(0, 0, 0);

  render_queue::Queue rqueue(settings->HEIGHT, settings->WIDTH,
                             settings->BLOCK_SIZE);

  const auto total_tasks = rqueue.size();
  std::cout << "Tasks generated: " << total_tasks << std::endl;

  const auto start_render = std::chrono::system_clock::now();

  renderPixel(rqueue, O, 1, 0);

  //  std::vector<std::thread> threads;
  //  threads.reserve(nproc);
  //  for (int i = 0; i < nproc; i++) {
  //    std::thread t(&SamplerRenderer::renderPixel, this);
  //    threads.push_back(std::move(t));
  //  }
  //  for (auto &t : threads) {
  //    t.join();
  //  }
  SDL_RenderPresent(_renderer);
  const auto render_duration = std::chrono::system_clock::now() - start_render;
}