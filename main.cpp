#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>

//#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//#include <core/settings.hpp>
//#include <renderers/base_renderer.hpp>
//#include <renderers/sampler_renderer.hpp>
//#include <renderers/wireframe_renderer.hpp>

// std::shared_ptr<BaseRenderer> m_renderer;

int main(int argc, char *argv[]) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GLFWwindow *window =
      glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
  if (window == nullptr) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cout << "Failed to initialize GLEW" << std::endl;
    return -1;
  }

  int width, height;
  glfwGetFramebufferSize(window, &width, &height);

  glViewport(0, 0, width, height);
  std::cout << width << " x " << height << std::endl;

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    //    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    //    glClear(GL_COLOR_BUFFER_BIT);
    //    glMatrixMode(GL_PROJECTION);
    //    glLoadIdentity();
    //    gluOrtho2D(0.0, (GLfloat)width, 0.0, (GLfloat)height);
    //    glMatrixMode(GL_MODELVIEW);
    //    glLoadIdentity();
    // Метка в виде крестика
    //    GLubyte bitmap_mark[] = {0x10, 0x10, 0x10, 0xFF, 0x10, 0x10, 0x10};
    //
    //    // Свойства распаковки
    //    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    //
    //    // Цвет метки
    //    glColor3d(1., 0., 0.);
    //
    //    // Позиция вывода растра
    //    glRasterPos2d(25., 25.);

    //    // Вывод битового массива
    //    glBitmap(7, 7, 4, 3, 0, 0, bitmap_mark);

    int W = 10, H = 10;

    unsigned char data[W][H][3];
    for (size_t x = 0; x < H; x++) {
      for (size_t y = 0; y < W; y++) {
        data[x][y][0] = 250;
        data[x][y][1] = 2;
        data[x][y][2] = 250;
      }
    }
    //
    //    glClearColor(0.0, 0.0, 0.0, 0.0);
    //    glShadeModel(GL_FLAT);
    //    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    //
    //    glClear(GL_COLOR_BUFFER_BIT);
    //    glRasterPos2i(0, 0);
    //    glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glRasterPos2d(-4.5, -3); // нижний левый угол
    glPixelZoom(1, 1);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // выравнивание
    glDrawPixels(W, H,                     // ширина и высота
                 GL_RGB, GL_UNSIGNED_BYTE, // формат и тип
                 data);                    // сами данные

    glfwSwapBuffers(window);
  }

  glfwTerminate();
  return 0;

  //  Settings settings;
  //  settings.init_from_args(argc, argv);
  //
  //  m_renderer = std::make_shared<SamplerRenderer>(
  //      std::make_shared<Settings>(settings),
  //      std::make_shared<Scene>(Scene()));
  //
  //  m_renderer->init();
  //  m_renderer->scene->loadGeometry("../geometry_samples/scene");
  //
  //  m_renderer->render();
  //
  //  //  for (const auto &prim : m_renderer->scene->primitives) {
  //  //    std::cout << typeid(prim).name() << std::endl;
  //  //  }
  //  //
  //  //  std::cout << typeid(BaseRenderer).name() << std::endl;
  //
  //  SDL_Event event;
  //  while (SDL_WaitEvent(&event) >= 0) {
  //    if (event.type == SDL_QUIT) {
  //      break;
  //    }
  //  }
  //
  //  m_renderer->deinit();
  //
  //  return 0;
}
