#include <fstream>
#include <sstream>

#include "file.h"

namespace file {
std::string read_file(std::string_view path) {
  std::ifstream file(path.data());
  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

std::vector<std::string_view> split(std::string_view strv,
                                    std::string_view delimiter) {
  std::vector<std::string_view> parts;
  std::size_t i = 0;
  std::size_t match = 0;
  while (i < strv.length()) {
    match = strv.find(delimiter, i);
    if (match == strv.npos)
      match = strv.length();
    parts.push_back(strv.substr(i, match - i));
    i = match + delimiter.length();
  }
  return parts;
}
} // namespace file
