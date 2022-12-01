#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace file {
std::string read_file(std::string_view path);
std::vector<std::string_view> split(std::string_view strv,
                                    std::string_view delimiter);
} // namespace file
