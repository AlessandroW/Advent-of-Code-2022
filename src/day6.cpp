#include "day6.h"
#include "file.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_set>

namespace day6 {
    int get_distinct(std::string_view message, std::size_t count) {
        std::unordered_set<char> marker;
        for (auto it = message.begin(); it != message.end() - count; ++it) {
            marker.insert(it, it + count);
            if (marker.size() == count) {
                return static_cast<int>(std::distance(message.begin(), it + count));
            }
            marker.clear();
        }
        return 0;
    }

    void solve(std::string_view path) {
        std::string file = file::read_file(path);
        std::cout << "Puzzle 1: " << get_distinct(file, 4) << '\n';
        std::cout << "Puzzle 2: " << get_distinct(file, 14) << '\n';
    }
}
