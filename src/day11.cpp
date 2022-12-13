#include "day11.h"
#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

namespace day11 {

struct Monkey {
  std::queue<long long> items;
  std::function<long long(long long)> op;
  long long divisible;
  std::size_t true_monkey;
  std::size_t false_monkey;
  int total_items;

  Monkey(std::queue<long long> &&items, std::function<long long(long long)> op,
         long long divisible, std::size_t true_monkey, std::size_t false_monkey)
      : items(items), op(op), divisible(divisible), true_monkey(true_monkey),
        false_monkey(false_monkey), total_items(0){};

  void throw_item(long long item, std::vector<Monkey> &monkeys) {
    item = operation(item);
    if (item % divisible == 0)
      monkeys[true_monkey].items.push(item);
    else {
      monkeys[false_monkey].items.push(item);
    }
  }

  long long operation(long long old) {
    // Part 1
    old = op(old);
    // old /= 3; // Part 1
    return old;
  }

  void turn(std::vector<Monkey> &monkeys) {
    while (items.size() > 0) {
      ++total_items;
      throw_item(items.front(), monkeys);
      items.pop();
    }
  }
};

std::vector<Monkey> input() {
  std::vector<Monkey> monkeys;
  monkeys.emplace_back(
      std::queue<long long>({83, 62, 93}),
      [](long long old) { return (old % 9699690) * 17; }, 2, 1, 6);
  monkeys.emplace_back(
      std::queue<long long>({90, 55}),
      [](long long old) { return (old % 9699690) + 1; }, 17, 6, 3);
  monkeys.emplace_back(
      std::queue<long long>({91, 78, 80, 97, 79, 88}),
      [](long long old) { return (old % 9699690) + 3; }, 19, 7, 5);
  monkeys.emplace_back(
      std::queue<long long>({64, 80, 83, 89, 59}),
      [](long long old) { return (old % 9699690) + 5; }, 3, 7, 2);
  monkeys.emplace_back(
      std::queue<long long>({98, 92, 99, 51}),
      [](long long old) { return (old % 9699690) * (old % 9699690); }, 5, 0, 1);
  monkeys.emplace_back(
      std::queue<long long>({68, 57, 95, 85, 98, 75, 98, 75}),
      [](long long old) { return (old % 9699690) + 2; }, 13, 4, 0);
  monkeys.emplace_back(
      std::queue<long long>({74}),
      [](long long old) { return (old % 9699690) + 4; }, 7, 3, 2);
  monkeys.emplace_back(
      std::queue<long long>({68, 64, 60, 68, 87, 80, 82}),
      [](long long old) { return (old % 9699690) * 19; }, 11, 4, 5);
  return monkeys;
}

std::vector<Monkey> example() {
  std::vector<Monkey> monkeys;
  monkeys.emplace_back(
      std::queue<long long>({79, 98}),
      [](long long old) { return (old % 96577) * 19; }, 23, 2, 3);
  monkeys.emplace_back(
      std::queue<long long>({54, 65, 75, 74}),
      [](long long old) { return (old % 96577) + 6; }, 19, 2, 0);
  monkeys.emplace_back(
      std::queue<long long>({79, 60, 97}),
      [](long long old) { return (old % 96577) * (old % 96577); }, 13, 1, 3);
  monkeys.emplace_back(
      std::queue<long long>({74}),
      [](long long old) { return (old % 96577) + 3; }, 17, 0, 1);
  return monkeys;
}

void solve(std::string_view) {
  std::vector<Monkey> monkeys = input();
  // std::vector<Monkey> monkeys = example();

  int common_multiplicative = 1;
  for (const Monkey &monkey : monkeys) {
    common_multiplicative *= monkey.divisible;
  }
  std::cout << common_multiplicative << '\n';

  for (int round = 0; round < 10000; ++round)
    for (Monkey &monkey : monkeys) {
      monkey.turn(monkeys);
    }

  std::vector<long long> totals;
  for (Monkey &monkey : monkeys) {
    totals.push_back(monkey.total_items);
  }
  std::sort(totals.begin(), totals.end(),
            [](long long a, long long b) { return a > b; });
  std::cout << totals[0] * totals[1] << '\n';
}
} // namespace day11
