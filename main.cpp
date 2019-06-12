#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>

#include <core/settings.hpp>
#include <renderers/sampler_renderer.hpp>
#include <renderers/base_renderer.hpp>
#include <renderers/wireframe_renderer.hpp>

std::shared_ptr<BaseRenderer> m_renderer;

int main(int argc, char *argv[]) {
  Settings settings;
  settings.init_from_args(argc, argv);

  m_renderer = std::make_shared<SamplerRenderer>(std::make_shared<Settings>(settings),
                                                 std::make_shared<Scene>(Scene()));

  m_renderer->init();
  m_renderer->scene->loadGeometry("../geometry_samples/scene");

  m_renderer->render();

//  for (const auto &prim : m_renderer->scene->primitives) {
//    std::cout << typeid(prim).name() << std::endl;
//  }
//
//  std::cout << typeid(BaseRenderer).name() << std::endl;

  SDL_Event event;
  while (SDL_WaitEvent(&event) >= 0) {
    if (event.type == SDL_QUIT) {
      break;
    }
  }

  m_renderer->deinit();

  return 0;
}
