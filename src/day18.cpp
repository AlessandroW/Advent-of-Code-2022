#include "day18.h"
#include "file.h"
#include <array>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace day18 {
struct point {
  int x, y, z;
  int exposed = 6;

  point() : x(0), y(0), z(0), exposed(6){};
  point(std::string_view strv) {
    std::vector<std::string_view> points = file::split(strv, ",");
    // numbers are comma separated, i.e. parsed correctly.
    this->x = std::atoi(points[0].data());
    this->y = std::atoi(points[1].data());
    this->z = std::atoi(points[2].data());
  }
};

std::string point_to_str(int x, int y, int z) {
  std::stringstream s;
  s << x << ',' << y << ',' << z;
  return s.str();
}

std::array<std::string, 6> neighbors(point p) {
  return {point_to_str(p.x - 1, p.y, p.z), point_to_str(p.x + 1, p.y, p.z),
          point_to_str(p.x, p.y + 1, p.z), point_to_str(p.x, p.y - 1, p.z),
          point_to_str(p.x, p.y, p.z + 1), point_to_str(p.x, p.y, p.z - 1)};
}

void solve(std::string_view path) {
  std::string file = file::read_file(path);
  std::vector<std::string_view> drops = file::split(file, "\n");
  std::unordered_map<std::string, point> points;
  for (std::string_view drop : drops)
    points.emplace(drop, drop);
  for (auto &[name, p] : points)
    for (const std::string &neighbor : neighbors(p))
      if (points.contains(neighbor))
        --p.exposed;

  int exposed =
      std::accumulate(points.begin(), points.end(), 0,
                      [](int result, const std::pair<std::string, point> &p) {
                        return result + p.second.exposed;
                      });

  std::cout << exposed << '\n';

  std::unordered_map<std::string, point> air_pockets;
  for (auto &[name, p] : points)
    for (const std::string &neighbor : neighbors(p))
      if (not points.contains(neighbor))
        air_pockets.emplace(neighbor, neighbor);

  // Count only air pockets that are fully enclosed
  for (auto it = air_pockets.cbegin(); it != air_pockets.cend();) {
    auto [name, p] = *it;
    bool erased = false;
    for (const std::string &neighbor : neighbors(p))
      if (not points.contains(neighbor)) {
        air_pockets.erase(it++);
        erased = true;
        break;
      }
    if (not erased)
      ++it;
  }

  for (auto &[name, p] : air_pockets)
    for (const std::string &neighbor : neighbors(p))
      if (air_pockets.contains(neighbor))
        --p.exposed;


  int airea = // see what I did there?
      std::accumulate(air_pockets.begin(), air_pockets.end(), 0,
                      [](int result, const std::pair<std::string, point> &p) {
                        return result + p.second.exposed;
                      });

  for (auto &[name, p] : air_pockets)
      std::cout << name << ": " << p.exposed << '\n';

  std::cout << air_pockets.size() <<'\n';
  std::cout << exposed - airea << '\n';
}

} // namespace day18
