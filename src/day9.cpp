#include "day9.h"
#include "file.h"
#include <array>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <set>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace day9 {
int sign(int a) { return (a > 0) - (a < 0); };
struct Point {
  int x;
  int y;

  Point() : x(0), y(0){};

  void step(char direction) {
    if (direction == 'R') {
      ++x;
    } else if (direction == 'L') {
      --x;
    } else if (direction == 'U') {
      ++y;
    } else if (direction == 'D') {
      --y;
    }
  };

  void follow(const Point &H) {
    if (H.x == x) {
      if (std::abs(H.y - y) != 1)
        y += sign(H.y - y);
    } else if (H.y == y) {
      if (std::abs(H.x - x) != 1)
        x += sign(H.x - x);
    } else { // diagonal
      auto dist_x = std::abs(H.x - x);
      auto dist_y = std::abs(H.y - y);
      if (dist_x == 2) {
        y = (dist_y == 2) ? H.y - sign(H.y - y) : H.y;
        x = H.x - sign(H.x - x);
      } else if (dist_y == 2) {
        x = (dist_x == 2) ? H.x - sign(H.x - x) : H.x;
        y = H.y - sign(H.y - y);
      }
    }
  }
};

// There are more efficient hash functions but meh..
std::string to_string(const Point &p) {
  std::string s = std::to_string(p.x);
  s.append("-");
  s.append(std::to_string(p.y));
  return s;
}

template <size_t n>
void step(std::array<Point, n> &points, std::string_view instruction,
          std::set<std::string> &visited) {
  char direction = instruction[0];
  for (int step_size =
           std::atoi(instruction.substr(1, instruction.size() - 1).data());
       step_size > 0; --step_size) {
    points[0].step(direction);
    for (size_t i = 1; i < n; ++i) {
      points[i].follow(points[i - 1]);
    }
    visited.emplace(to_string(points[n - 1]));
  }
}

std::size_t solution1(const std::vector<std::string_view> directions) {
  std::set<std::string> visited;
  std::array<Point, 2> points;
  for (const auto &direction : directions) {
    step(points, direction, visited);
  }
  return visited.size();
}
std::size_t solution2(const std::vector<std::string_view> directions) {
  std::set<std::string> visited;
  std::array<Point, 10> points;
  for (const auto &direction : directions) {
    step(points, direction, visited);
  }
  return visited.size();
}

void solve(std::string_view path) {
  std::string file = file::read_file(path);
  std::vector<std::string_view> directions = file::split(file, "\n");

  std::cout << "Puzzle 1: " << solution1(directions) << '\n';
  std::cout << "Puzzle 2: " << solution2(directions) << '\n';
}
} // namespace day9
