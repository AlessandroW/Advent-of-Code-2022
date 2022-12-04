#include "day4.h"
#include "file.h"
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string_view>
#include <vector>

namespace day4 {
using it = std::string_view::iterator;
std::size_t get_pair_separator(std::string_view pair) {
  return static_cast<std::size_t>(
      std::distance(pair.begin(), std::find(pair.begin(), pair.end(), ',')));
}

std::pair<int, int> get_range(std::string_view strv, std::size_t begin,
                              std::size_t end) {
  it separator = std::find(strv.begin() + begin, strv.begin() + end, '-');
  int left =
      std::atoi(strv.substr(begin, static_cast<std::size_t>(
                                       std::distance(strv.begin(), separator)))
                    .data());
  int right = std::atoi(strv.substr(static_cast<std::size_t>(std::distance(
                                        strv.begin(), separator)) +
                                        1,
                                    end)
                            .data());
  return {left, right};
}

bool is_fully_contained(std::string_view pair) {
  std::size_t separator = get_pair_separator(pair);
  std::pair<int, int> first = get_range(pair, 0, separator);
  std::pair<int, int> second = get_range(pair, separator + 1, pair.size());
  auto contained = [](const std::pair<int, int> &a,
                      const std::pair<int, int> &b) {
    return a.first >= b.first and a.second <= b.second;
  };
  return contained(first, second) or contained(second, first);
}

bool is_contained(std::string_view pair) {
  std::size_t separator = get_pair_separator(pair);
  std::pair<int, int> first = get_range(pair, 0, separator);
  std::pair<int, int> second = get_range(pair, separator + 1, pair.size());
  auto overlaps = [](const std::pair<int, int> &a,
                     const std::pair<int, int> &b) {
    return not(a.first > b.second or a.second < b.first);
  };
  return overlaps(first, second) or overlaps(second, first);
}

void test_is_fully_contained() {
  assert(is_fully_contained("6-6,4-6"));
  assert(not is_fully_contained("2-4,6-8"));
}

void test_get_pair_separator() { assert(get_pair_separator("2-14,6-8") == 4); }

void test_get_range() {
  std::string_view s = "12-75";
  auto [left, right] = get_range(s, 0, s.size());
  assert(left == 12);
  assert(right == 75);
};

void test() {
  test_get_pair_separator();
  test_get_range();
  test_is_fully_contained();
}

int solution1(std::vector<std::string_view> pairs) {
  int result = 0;
  for (std::string_view pair : pairs)
    result += is_fully_contained(pair);
  return result;
}

int solution2(std::vector<std::string_view> pairs) {
  int result = 0;
  for (std::string_view pair : pairs)
    result += is_contained(pair);
  return result;
}

void solve(std::string_view path) {
  test();
  std::string file = file::read_file(path);
  std::vector<std::string_view> pairs = file::split(file, "\n");
  std::cout << "Puzzle 1: " << solution1(pairs) << '\n';
  std::cout << "Puzzle 2: " << solution2(pairs) << '\n';
}
} // namespace day4
