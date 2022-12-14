#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>

#include "day1.h"
#include "file.h"

namespace day1 {
std::vector<int> extract_calories(std::string_view path) {
  std::string input = file::read_file(path);
  std::vector<std::string_view> bags = file::split(input, "\n\n");
  std::vector<int> calories;
  auto strv2int = [](int result, std::string_view item) {
    return result + std::atoi(item.data());
  };
  for (const std::string_view bag : bags) {
    std::vector<std::string_view> items = file::split(bag, "\n");
    int bag_calories = std::accumulate(items.begin(), items.end(), 0, strv2int);
    calories.push_back(bag_calories);
  }
  return calories;
}

int solution1(const std::vector<int> &calories) {
  return *std::max_element(calories.begin(), calories.end());
}

int solution2(std::vector<int> &calories) {
  std::nth_element(calories.begin(), calories.begin() + 2, calories.end(),
                   std::greater{});
  return std::accumulate(calories.begin(), calories.begin() + 3, 0);
}

void solve(std::string_view path) {
  auto calories = day1::extract_calories(path);
  std::cout << "Puzzle 1: " << day1::solution1(calories) << '\n';
  std::cout << "Puzzle 2: " << day1::solution2(calories) << '\n';
}
} // namespace day1

