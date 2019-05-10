#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>

#include <core/settings.hpp>
#include <renderers/sampler_renderer.hpp>

int main(int argc, char *argv[]) {
  Settings settings;
  settings.init_from_args(argc, argv);

  SamplerRenderer m_renderer(std::make_shared<Settings>(settings),
                             std::make_shared<Scene>(Scene()));

  m_renderer.init();
  m_renderer.scene->loadGeometry("../geometry_samples/scene");

  m_renderer.render();

  SDL_Event event;
  while (SDL_WaitEvent(&event) >= 0) {
    if (event.type == SDL_QUIT) {
      break;
    }
  }

  m_renderer.deinit();

  return 0;
}
