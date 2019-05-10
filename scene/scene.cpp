#include "scene.hpp"

#include <fstream>
#include <primitives/sphere.hpp>
#include <utils/geo_loaders.hpp>

void Scene::loadGeometry(const std::string &scene_filename) {
  std::vector<Material> mats{
      Material(Color(242, 76, 39), 0.1), Material(Color(76, 242, 39), 1000),
      Material(Color(100, 100, 10), 0.1), Material(Color(10, 100, 242), 0.1)};
  std::vector<Vec3> positions{Vec3(-2, 0, 8), Vec3(0, 0, 8), Vec3(2, 0, 8)};

  lightSources.emplace_back(Vec3(-2, 10, 10), Color(255, 255, 255));
  primitives.push_back(std::make_shared<Sphere>(
      Vec3(1, -1, 10), 1.0, std::make_shared<Material>(mats[0])));

  std::ifstream input(scene_filename);

  while (input.peek() != EOF) {
    double x, y, z;
    std::string obj_name;
    int mat_id;
    input >> x >> y >> z >> obj_name >> mat_id;

    const auto &pyramid_tris =
        geo_loaders::LoadObj("../geometry_samples/" + obj_name, Vec3(x, y, z),
                             std::make_shared<Material>(mats.at(mat_id)));

    for (const auto &tri : pyramid_tris) {
      primitives.push_back(tri);
    }
  }
}