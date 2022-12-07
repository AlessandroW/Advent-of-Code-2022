#include "day7.h"
#include "file.h"
#include <cstdlib>
#include <iostream>
#include <string_view>
#include <unordered_map>

namespace day7 {
struct directory {
  std::string name;
  std::string parent;
  std::vector<std::string> children;
  int size;
};

using index = std::unordered_map<std::string, directory>;

int calculate_size(index &index, const std::string &name) {
  const directory &dir = index[name];
  int size = dir.size;
  for (const std::string &child : dir.children)
    size += calculate_size(index, child);
  return size;
}

void parse_command(std::string_view command, index &index,
                   std::string &current_dir) {
  std::vector<std::string_view> lines = file::split(command, "\n");
  // cd
  if (lines[0][0] == 'c') {
    std::string_view dest = file::split(lines[0], " ")[1];
    if (dest[0] == '.') { // cd ..
      current_dir = index[current_dir].parent;
    } else if (std::string name =
                   current_dir + '/' + std::string(dest);
               index.contains(name)) {
      current_dir = name;
    } else { // cd dir_name
      index.emplace(name, directory{name, current_dir, {}, 0});
      index[current_dir].children.push_back(name);
      current_dir = name;
    }
  } else if (lines[0][0] == 'l') { // ls
    for (auto it = lines.begin() + 1; it != lines.end(); ++it) {
      if ((*it)[0] != 'd') { // must be a file
        // This works as the numbers are charcter separated 😂
        index[current_dir].size += std::atoi(file::split(*it, " ")[0].data());
      }
    }
  }
}

int solution1(index &index) {
  int result = 0;
  for (auto &[name, dir] : index) {
    if (int size = calculate_size(index, name); size <= 100000) {
      result += size;
    }
  }
  return result;
}

int solution2(index &index) {
  int smallest_size = calculate_size(index , "/");
  int required_space = 30000000 - (70000000 - smallest_size);
  for (auto &[name, dir] : index) {
    if (int size = calculate_size(index, name);
        size >= required_space and size < smallest_size) {
      smallest_size = size;
    }
  }
  return smallest_size;
}

void solve(std::string_view path) {
  std::string file = file::read_file(path);
  // First element is empty
  std::vector<std::string_view> commands = file::split(file, "$ ");
  index index;
  index.emplace("/", directory{"/", "/", {}, 0});
  std::string current_dir = "/";
  for (auto it = commands.begin() + 2; it != commands.end(); ++it) {
    parse_command(*it, index, current_dir);
  }
  std::cout << "Puzzle 1: " << solution1(index) << '\n';
  std::cout << "Puzzle 2: " << solution2(index) << '\n';
}
} // namespace day7
