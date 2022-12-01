#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace day1 {
    std::vector<int> extract_calories(std::string_view path);
    int solution1(const std::vector<int>& calories);
    int solution2(std::vector<int>& calories);
    void solve(std::string_view path);
}
