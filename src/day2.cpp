#include <iostream>
#include <string_view>
#include <utility>

#include "day2.h"
#include "file.h"

namespace day2 {

enum symbol { rock = 'A', paper = 'B', scissors = 'C' };

char to_abc(char c) { return c - ('X' - 'A'); }

int to_points(char c) { return static_cast<int>(c - 'A' + 1); }

bool draw(char elve, char me) { return elve == me; }

bool won(char elve, char me) {
  if (elve == symbol::scissors and me == symbol::rock)
    return true;
  else if (me == symbol::scissors and elve == symbol::rock)
    return false;
  else if (elve < me)
    return true;
  return false;
}

int score(char elve, char me) {
  int result = to_points(me);
  if (draw(elve, me))
    result += 3;
  else if (won(elve, me))
    result += 6;
  // lost is += 0
  return result;
}

void test_solution1() {
  // Lost
  assert(score(paper, to_abc('X')) == 1);    // 1 + 0
  assert(score(scissors, to_abc('Y')) == 2); // 2 + 0
  assert(score(rock, to_abc('Z')) == 3);     // 3 + 0
  // Draw
  assert(score(rock, to_abc('X')) == 4);     // 1 + 3 = 4
  assert(score(paper, to_abc('Y')) == 5);    // 2 + 3 = 5
  assert(score(scissors, to_abc('Z')) == 6); // 3 + 3 = 6
  // Won
  assert(score(scissors, to_abc('X')) == 7); // 1 + 6 = 7
  assert(score(rock, to_abc('Y')) == 8);     // 2 + 6 = 8
  assert(score(paper, to_abc('Z')) == 9);    // 3 + 6 = 9
}

char resolve(char elve, char result) {
  if (result == 'X') {
    if (elve == rock)
      return scissors;
    return rock + ((elve - rock) - 1) % 3;
  } else if (result == 'Y')
    return elve;
  return rock + (elve - rock + 1) % 3;
}

void test_solution2() {
  // Lost
  assert(resolve(paper, 'X') == rock);
  assert(resolve(scissors, 'X') == paper);
  assert(resolve(rock, 'X') == scissors);
  // Draw
  assert(resolve(rock, 'Y') == rock);
  assert(resolve(paper, 'Y') == paper);
  assert(resolve(scissors, 'Y') == scissors);
  // Won
  assert(resolve(scissors, 'Z') == rock);
  assert(resolve(rock, 'Z') == paper);
  assert(resolve(paper, 'Z') == scissors);
}

void solve(std::string_view path) {
  test_solution1();
  test_solution2();

  int result_1 = 0, result_2 = 0;
  std::size_t i = 0, match = 0;
  std::string file = file::read_file(path);
  while (i < file.length()) {
    // Extract round
    match = file.find('\n', i);
    if (match == file.npos)
      match = file.length();
    result_1 += score(file[i], to_abc(file[match - 1]));
    result_2 += score(file[i], resolve(file[i], file[match - 1]));
    i = match + 1;
  }

  std::cout << "Puzzle 1: " << result_1 << '\n';
  std::cout << "Puzzle 2: " << result_2 << '\n';
}

} // namespace day2
