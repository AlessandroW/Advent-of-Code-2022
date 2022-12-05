#include "day5.h"
#include "file.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <tuple>

namespace day5 {
using instructions = std::vector<std::tuple<int, std::size_t, std::size_t>>;
using stacks = std::vector<std::vector<char>>;

stacks fill_stacks(std::string_view schema) {
  std::vector<std::string_view> lines = file::split(schema, "\n");
  std::size_t stack_numbers = static_cast<std::size_t>(
      std::atoi(lines.back().substr(lines.back().size() - 2, 1).data()));
  stacks stacks(stack_numbers);
  std::size_t stack = 0;
  for (auto it = lines.end() - 1; it != lines.begin();) {
    --it;
    std::string_view line = *it;
    for (std::size_t pos{1}; pos < line.size(); pos += 4) {
      if (line[pos] != ' ') {
        stacks[stack].push_back(line[pos]);
      }
      ++stack;
    }
    stack = 0;
  }
  return stacks;
}

void print_stacks(const stacks &stacks) {
  std::size_t max_size = 0;
  for (auto stack : stacks) {
    max_size = std::max(max_size, stack.size());
  }
  std::size_t i = max_size;
  do {
    std::cout << i;
    for (auto stack : stacks) {
      if (i > stack.size())
        std::cout << "   ";
      else
        std::cout << ' ' << stack[i - 1] << ' ';
    }
    std::cout << '\n';
    --i;
  } while (i > 0);
  std::cout << '\n';
}

instructions parse_instructions(std::string_view description) {
  std::vector<std::string_view> lines = file::split(description, "\n");
  instructions instructions;
  int amount = 0;
  size_t from = 0, to = 0;
  std::string_view::iterator begin, pos;
  for (std::string_view line : lines) {
    begin = line.begin() + 5;
    pos = std::find(begin, line.end(), ' ');
    amount = std::atoi(
        line.substr(5, static_cast<std::size_t>(std::distance(begin, pos)))
            .data());

    begin = pos + 6;
    pos = std::find(begin, line.end(), ' ');
    from = static_cast<std::size_t>(std::atoi(
        line.substr(
                static_cast<std::size_t>(std::distance(line.begin(), begin)),
                static_cast<std::size_t>(std::distance(begin, pos)))
            .data()));

    begin = pos + 3;
    pos = std::find(begin, line.end(), ' ');
    to = static_cast<std::size_t>(std::atoi(
        line.substr(
                static_cast<std::size_t>(std::distance(line.begin(), begin)),
                static_cast<std::size_t>(std::distance(begin, pos)))
            .data()));
    instructions.emplace_back(amount, from - 1, to - 1);
  }

  return instructions;
}

std::string solution(stacks stacks, const instructions &instructions,
                     int CrateMoverVersion) {
  for (auto [amount, from, to] : instructions) {
    if (CrateMoverVersion == 9001) {
      stacks[to].insert(stacks[to].end(), stacks[from].end() - amount,
                        stacks[from].end());
    } else {
      for (auto it = stacks[from].end(); it != stacks[from].end() - amount;) {
        --it;
        stacks[to].push_back(*it);
      }
    }
    stacks[from].erase(stacks[from].end() - amount, stacks[from].end());
  }
  std::stringstream s;
  for (auto stack : stacks) {
    s << stack.back();
  }
  return s.str();
}

void solve(std::string_view path) {
  std::string file = file::read_file(path);
  std::vector<std::string_view> parts = file::split(file, "\n\n");
  stacks stacks = fill_stacks(parts[0]);
  instructions instructions = parse_instructions(parts[1]);
  std::cout << "Puzzle 1:" << solution(stacks, instructions, 9000) << '\n';
  std::cout << "Puzzle 2:" << solution(stacks, instructions, 9001) << '\n';
}
} // namespace day5
