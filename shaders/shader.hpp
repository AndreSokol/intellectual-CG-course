#pragma once

#include <fstream>
#include <string>

namespace shader {

std::string Read(const std::string &path) {
  std::ifstream file(path);

  std::string str;
  std::string file_contents;

  while (std::getline(file, str)) {
    file_contents += str;
    file_contents.push_back('\n');
  }

  return file_contents;
}

} // namespace shader
