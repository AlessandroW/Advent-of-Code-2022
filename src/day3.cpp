#include <algorithm>
#include <iostream>
#include <ostream>
#include <unordered_set>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

#include "day3.h"
#include "file.h"

namespace day3 {

char find_duplicate(std::string_view bag) {
  std::unordered_map<char, std::size_t> second_compartment;
  for (std::size_t pos = bag.size() / 2; pos < bag.size(); ++pos) {
    second_compartment.insert_or_assign(bag[pos], pos);
  }
  for (std::size_t pos = 0; pos < bag.size() / 2; ++pos) {
    if (second_compartment.contains(bag[pos])) {
      return bag[pos];
    }
  }
  return '?';
}

using iterator = std::vector<std::string_view>::iterator;
char find_duplicates(iterator begin, iterator end) {
  std::unordered_set<char> common_items;
  for (char c : *begin)
    common_items.insert(c);

  std::unordered_set<char> bag_items;
  for (iterator it = begin + 1; it < end - 1; ++it) {
    for (char c : *it)
      bag_items.insert(c);

    std::erase_if(common_items, [&bag_items](char item) {
      return not bag_items.contains(item);
    });
    bag_items.clear();
  }

  for (char c : *(end - 1))
    if (common_items.contains(c))
      return c;
  return '?';
}

int to_priority(char c) {
  if (c > 'Z')
    return static_cast<int>(c - 'a') + 1;
  return static_cast<int>(c - 'A') + 27;
}

void test_find_duplicate() {
  std::string bag = "vJrwpWtwJgWrhcsFMMfFFhFp";
  char duplicate = find_duplicate(bag);
  assert(duplicate != '?');
  assert(duplicate == 'p');
}

void test_to_priority() {
  assert(to_priority('A') == 27);
  assert(to_priority('a') == 1);
  assert(to_priority('Z') == 52);
  assert(to_priority('z') == 26);
}

void test_find_duplicates() {
  std::vector<std::string_view> bags =
      file::split("vJrwpWtwJgWrhcsFMMfFFhFp\n"
                  "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL\n"
                  "PmmdzqPrVvPwwTWBwg",
                  "\n");
  assert(find_duplicates(bags.begin(), bags.end()) == 'r');
  bags = file::split("adaA\n"
                     "zezd\n"
                     "dfdA",
                     "\n");
  assert(find_duplicates(bags.begin(), bags.end()) == 'd');
  bags = file::split("ctwDjvgtltgglHrSHCsQWBBDfS ZJZdVnmhmfCprnBTfS "
                     "dNddhhdPRRdbdNcvwCPCgCctjPlF",
                     " ");
}
int solution1(std::vector<std::string_view> bags) {
  int result = 0;
  for (std::string_view bag : bags)
    result += to_priority(find_duplicate(bag));
  return result;
}

int solution2(std::vector<std::string_view> bags) {
  int result = 0;
  for (iterator it = bags.begin(); it < bags.end(); it += 3) {
    result += to_priority(find_duplicates(it, it + 3));
  }
  return result;
}

void test() {
  test_find_duplicate();
  test_to_priority();
  test_find_duplicates();
}

void solve(std::string_view path) {
  test();
  std::string file = file::read_file(path);
  std::vector<std::string_view> bags = file::split(file, "\n");
  std::cout << "Puzzle 1: " << solution1(bags) << '\n';
  std::cout << "Puzzle 2: " << solution2(bags) << '\n';
}
} // namespace day3
