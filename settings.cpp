#include "settings.hpp"

#include <iostream>

void Settings::init_from_args(int argc, char **argv) {
  for (size_t i = 1; i < argc; i += 2) {
    std::string param_name(argv[i]);
    std::string param_value(argv[i + 1]);

    if (param_name == "-width") {
      std::cout << "setting WIDTH = " << param_value << std::endl;
      WIDTH = std::stoi(param_value);
    } else if (param_name == "-height") {
      std::cout << "setting HEIGHT = " << param_value << std::endl;
      HEIGHT = std::stoi(param_value);
    } else if (param_name == "-block-size") {
      std::cout << "setting BLOCK_SIZE = " << param_value << std::endl;
      BLOCK_SIZE = std::stoi(param_value);
    } else if (param_name == "-ssaa") {
      std::cout << "setting SSAA_ENABLED = " << (param_value == "1")
                << std::endl;
      SSAA_ENABLED = (param_value == "1");
    } else if (param_name == "-scaling") {
      std::cout << "setting SCALING_ENABLED = " << (param_value == "1")
                << std::endl;
      SCALING_ENABLED = (bool)(param_value == "1");
    } else if (param_name == "-background-color") {
      std::cout << "setting BACKGROUND_COLOR = " << param_value << std::endl;
      BACKGROUND_COLOR = Color(param_value);
    } else {
      std::cerr << "Unknown param " << param_name << std::endl;
    }
  }
}