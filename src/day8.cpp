#include "day8.h"
#include "file.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>
#include <string_view>

namespace day8 {
using grid = std::vector<std::vector<int>>;
grid parse(const std::vector<std::string_view> &strvs) {
  grid grid;
  grid.reserve(strvs.size());
  for (std::string_view s : strvs) {
    std::vector<int> row;
    row.reserve(s.size());
    for (char c : s) {
      // 0 is 48 in ASCII
      row.emplace_back(static_cast<int>(c) - 48);
    }
    grid.emplace_back(row);
  }
  return grid;
}

int range_max(std::vector<int>::const_iterator begin,
              std::vector<int>::const_iterator end) {
  int max = -1;
  for (auto it = begin; it != end; ++it)
    if (*it > max)
      max = *it;
  return max;
}

int column_max(const grid &grid, size_t column, size_t begin, size_t end) {
  int max = -1;
  for (; begin < end; ++begin)
    if (grid[begin][column] > max)
      max = grid[begin][column];
  return max;
}

grid relative_min_max(const grid &grid) {
  std::vector<std::vector<int>> min_max;
  min_max.reserve(grid.size());
  for (std::size_t row_it = 0; row_it < grid.size(); ++row_it) {
    std::vector<int> row;
    row.reserve(grid[row_it].size());
    for (int col_it = 0; col_it < static_cast<int>(grid[row_it].size());
         ++col_it) {
      row.emplace_back(std::min(
          {range_max(grid[row_it].begin(), grid[row_it].begin() + col_it),
           range_max(grid[row_it].begin() + col_it + 1, grid[row_it].end()),
           column_max(grid, static_cast<std::size_t>(col_it), 0, row_it),
           column_max(grid, static_cast<std::size_t>(col_it), row_it + 1,
                      grid.size())}));
    }
    min_max.emplace_back(row);
  }
  return min_max;
}

int solution1(const grid &grid) {
  std::vector<std::vector<int>> min_max = relative_min_max(grid);
  int trees = 0;
  for (std::size_t row_it = 0; row_it < grid.size(); ++row_it) {
    for (std::size_t col_it = 0; col_it < grid[row_it].size(); ++col_it) {
      if (grid[row_it][col_it] > min_max[row_it][col_it])
        ++trees;
    }
  }
  return trees;
}

int range_until(int tree, std::vector<int>::const_iterator begin,
                std::vector<int>::const_iterator end) {
  int until = 0;
  for (auto it = begin; it != end; ++it)
    if (*it < tree)
      ++until;
    else
      return until += 1;
  return until;
}

int reverse_range_until(int tree, std::vector<int>::const_iterator begin,
                        std::vector<int>::const_iterator end) {
  if (begin == end)
    return 0;
  int until = 0;
  auto it = end;
  do {
    --it;
    if (*it < tree)
      ++until;
    else
      return until += 1;
  } while (it != begin);
  return until;
}

int column_until(const grid &grid, int tree, size_t column, size_t begin,
                 size_t end) {
  int until = 0;
  for (; begin != end; ++begin)
    if (grid.at(begin).at(column) < tree)
      ++until;
    else
      return until += 1;
  return until;
}

int reverse_column_until(const grid &grid, int tree, size_t column,
                         size_t begin, size_t end) {
  if (begin == end)
    return 0;
  int until = 0;
  do {
    --end;
    if (grid.at(end).at(column) < tree)
      ++until;
    else
      return until += 1;
  } while (end != begin);
  return until;
}

int scenic_score(const grid &grid) {
  int max_score = 0;
  for (std::size_t row_it = 0; row_it < grid.size(); ++row_it) {
    for (std::size_t col_it = 0; col_it < grid[row_it].size(); ++col_it) {
      int tree = grid[row_it][col_it];
      int score =
          reverse_range_until(tree, grid[row_it].begin(),
                              grid[row_it].begin() + static_cast<int>(col_it)) *
          range_until(tree, grid[row_it].begin() + static_cast<int>(col_it) + 1,
                      grid[row_it].end()) *
          reverse_column_until(grid, tree, col_it, 0, row_it) *
          column_until(grid, tree, col_it, row_it + 1, grid.size());
      if (score > max_score) {
        max_score = score;
      }
    }
  }
  return max_score;
}

int solution2(const grid &grid) { return scenic_score(grid); }

void solve(std::string_view path) {
  std::string file = file::read_file(path);
  std::vector<std::string_view> rows = file::split(file, "\n");
  grid grid = parse(rows);
  std::cout << "Puzzle 1: " << solution1(grid) << '\n';
  std::cout << "Puzzle 2: " << solution2(grid) << '\n';
}
} // namespace day8
