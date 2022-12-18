#include "day17.h"
#include "file.h"
#include <algorithm>
#include <array>
#include <bitset>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <iomanip>
#include <ios>
#include <iostream>
#include <ostream>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

namespace day17 {
enum direction { left = true, right = false };

std::array<std::uint8_t, 4> get_rock(size_t i) {
  switch (i) {
  case 0: {
    return {0b1111000, 0, 0, 0};
    ;
  };
  case 1: {
    return {0b0100000, 0b1110000, 0b0100000, 0};
  };
  case 2: {
    return {0b1110000, 0b0010000, 0b0010000, 0};
  };
  case 3: {
    return {0b1000000, 0b1000000, 0b1000000, 0b1000000};
  };
  case 4: {
    return {0b1100000, 0b1100000, 0, 0};
  };
  default: {
    throw std::exception();
  };
  }
}


std::ostream &operator<<(std::ostream &o,
                         const std::array<std::uint8_t, 4> &map) {
  for (size_t i = map.size(); i != 0; i--)
    o << '|' << std::bitset<7>(map[i - 1]) << "|\n";
  return o;
}
std::ostream &operator<<(std::ostream &o,
                         const std::vector<std::uint8_t> &map) {
  for (size_t i = map.size(); i != 0; i--) {
    o << '|';
    for (auto c : std::bitset<7>(map[i - 1]).to_string())
      o << (c == '1' ? '#' : '.');
    o << "|\n";
  }
  return o;
}

std::vector<direction> parse(std::string_view file) {
  std::vector<direction> directions;
  for (char c : file.substr(0, file.size() - 1)) {
    directions.emplace_back(direction(c == '<'));
  }
  return directions;
}

void land_rock(std::vector<std::uint8_t> &map,
               const std::array<std::uint8_t, 4> &rock, size_t height) {
  for (size_t i = 0; i < 4; ++i) {
    if ((i + height) < map.size())
      map[i + height] |= rock[i];
    else
      map.push_back(rock[i]);
  }
}

std::array<std::uint8_t, 4> &operator>>=(std::array<std::uint8_t, 4> &rock,
                                         std::uint8_t amount) {
  for (size_t i = 0; i < 4; ++i)
    rock[i] >>= amount;
  return rock;
}

std::array<std::uint8_t, 4> &operator<<=(std::array<std::uint8_t, 4> &rock,
                                         std::uint8_t amount) {
  for (size_t i = 0; i < 4; ++i)
    rock[i] <<= amount;
  return rock;
}

void shift(direction direction, std::array<std::uint8_t, 4> &rock,
           std::vector<std::uint8_t> &map, size_t height) {

  std::array<std::uint8_t, 4> shifted_rock = rock;
  if (direction == left) {
    for (size_t i = 0; i < 4; ++i)
      if ((rock[i] & 0b01'000'000) > 0) {
        return;
      }
    shifted_rock <<= 1;
  } else {
    for (size_t i = 0; i < 4; ++i) {
      if ((rock[i] & 0b00000001) > 0) {
        return;
      }
    }
    shifted_rock >>= 1;
  }
  for (size_t i = 0; i < 4; ++i) {
    if ((height + i) < map.size() and
        (shifted_rock[i] & map[height + i]) > 0) {
      return;
    }
  }
  rock = shifted_rock;
}

size_t fall(std::array<std::uint8_t, 4> &rock, std::vector<std::uint8_t> &map,
            size_t height) {
  if (height == 0)
    return 0;
  if (map.size() == 0)
    return height - 1;
  for (size_t i = 0; i < 4; ++i) {
    if ((i + height - 1) < map.size() and (rock[i] & map[i + height - 1]) > 0) {
      return height;
    }
  }
  return height - 1;
}

size_t get_height(const std::vector<std::uint8_t> &map) {
  for (size_t i = map.size(); i > 0; --i) {
    if (map[i - 1] > 0)
      return i;
  }
  return 0;
}

void solve(std::string_view path) {
  std::string file = file::read_file(path);
  std::vector<direction> directions = parse(file);
  size_t direction = 0;
  size_t height = 3;
  size_t new_height = 0;
  std::vector<std::uint8_t> map;
  std::array<std::uint8_t, 4> current_rock;

  for (size_t i = 0; i < 1'000'000'000'000; ++i) {
    height = get_height(map);
    new_height = height + 3;
    current_rock = get_rock(i % 5);
    current_rock >>= 2;
    while (new_height != height) {
      height = new_height;
      shift(directions[direction], current_rock, map, height);
      new_height = fall(current_rock, map, height);
      direction = (direction + 1) % directions.size();
    }
    land_rock(map, current_rock, height);
  }
  std::cout << "Final Height: " << get_height(map) << '\n';
}
} // namespace day17
