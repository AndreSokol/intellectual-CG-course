#pragma once

#include <algorithm>

#include "utils/color.hpp"

class Settings {
public:
  int WIDTH = 480;
  int HEIGHT = 320;
  int BIGGEST_WINDOW_SIZE = std::max(WIDTH, HEIGHT);
  int D = 1;
  int REFLECT_DEPTH_LIMIT = 2;

  Color BACKGROUND_COLOR = Color(29, 33, 36);
  Color AMBIENT = Color(0, 5, 10);

  int BLOCK_SIZE = 1;
  bool SSAA_ENABLED = false;
  bool SCALING_ENABLED = true;

  Settings() = default;

  void init_from_args(int argc, char *argv[]);
};
