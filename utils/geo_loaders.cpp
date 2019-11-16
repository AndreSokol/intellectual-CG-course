#include "geo_loaders.hpp"

#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdlib.h>
#include <vector>

#include <base/vec3.hpp>
#include <primitives/triangle.hpp>

namespace geo_loaders {
namespace {
std::vector<std::string> splitString(const std::string &s, char delim = ' ') {
  std::stringstream ss(s);
  std::string item;
  std::vector<std::string> elems;
  while (std::getline(ss, item, delim)) {
    if (item.length() > 0) {
      elems.push_back(item);
    }
  }

  return elems;
}

int getFaceIndexes(const std::string &s, bool normal = false) {
  const auto &splitted = splitString(s, '/');
  const auto &index_s = splitted.at(normal ? splitted.size() - 1 : 0);
  return std::stoi(index_s) - 1;
}
} // namespace

std::vector<TriangleRef> LoadObj(const std::string &filename, const Vec3 &pos,
                                 const MatRef &mat) {
  std::ifstream file(filename);
  std::string line;

  std::vector<Vec3> vertices;
  std::vector<Vec3> normals;
  Tris tris;

  std::cout << "### Reading: " << filename << std::endl;

  while (getline(file, line)) {
    if (line[0] == '#')
      continue;

    const auto &data = splitString(line);

    if (data[0] == "v") {
      vertices.emplace_back(std::stod(data[1]), std::stod(data[2]),
                            std::stod(data[3]));

      std::cout << "v: vertices read " << vertices.size() << std::endl;
    } else if (data[0] == "vn") {
      normals.emplace_back(std::stod(data[1]), std::stod(data[2]),
                           std::stod(data[3]));

      std::cout << "vn: normals read " << normals.size() << std::endl;
    } else if (data[0] == "f") {
      int a = getFaceIndexes(data[1]);
      int b = getFaceIndexes(data[2]);
      int c = getFaceIndexes(data[3]);

      int n = getFaceIndexes(data[1], true);

      tris.push_back(
          std::make_shared<Triangle>(vertices[a] + pos, vertices[b] + pos,
                                     vertices[c] + pos, normals[n], mat));
      std::cout << "f: tris read " << tris.size() << std::endl;
    }
  }

  return tris;
}

} // namespace geo_loaders
