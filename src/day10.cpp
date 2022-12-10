#include "day10.h"
#include "file.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

namespace day10 {
struct cpu {
  int clock;
  int reg;
};

int execute(cpu &cpu, const std::string_view &instruction) {
  int strength = 0;
  if (instruction.starts_with("noop")) {
    ++cpu.clock;
  } else {
    // addx
    cpu.clock += 2;
    if (cpu.clock % 40 == 20)
      strength = cpu.clock * cpu.reg;
    else if (cpu.clock % 40 == 21)
      strength = (cpu.clock - 1) * cpu.reg;

    cpu.reg += std::atoi(file::split(instruction, " ")[1].data());
  }
  return strength;
}

void draw(cpu &cpu) {
  if (cpu.clock % 40 == 0)
    std::cout << '\n';
  if (cpu.reg - 1 <= (cpu.clock % 40) and cpu.reg + 1 >= (cpu.clock % 40))
    std::cout << '#';
  else
    std::cout << '.';
}

void draw(cpu &cpu, const std::string_view &instruction) {
  draw(cpu);
  ++cpu.clock;
  if (!instruction.starts_with("noop")) { // addx
    draw(cpu);
    ++cpu.clock;
    cpu.reg += std::atoi(file::split(instruction, " ")[1].data());
  }
}

void solve(std::string_view path) {
  std::string file = file::read_file(path);
  std::vector<std::string_view> instructions = file::split(file, "\n");
  cpu cpu{0, 1};
  int strength = 0;
  for (const std::string_view &instruction : instructions) {
    strength += execute(cpu, instruction);
  }
  std::cout << strength << '\n';
  // Part 2
  cpu = {0, 1};
  for (const std::string_view &instruction : instructions) {
    draw(cpu, instruction);
  }
  std::cout << '\n';
}
} // namespace day10
