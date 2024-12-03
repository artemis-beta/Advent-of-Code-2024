#pragma once

#include "spdlog/spdlog.h"
#include <sstream>
#include <vector>
#include <regex>

namespace AdventOfCode24::Day3 {
    std::vector<std::pair<int, int>> parse_line(std::istringstream& line);
};