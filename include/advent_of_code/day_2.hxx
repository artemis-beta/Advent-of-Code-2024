#pragma once

#include <sstream>
#include <cstdlib>
#include <string>
#include <filesystem>
#include <fstream>
#include <optional>
#include <sstream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <iterator>

#include "spdlog/spdlog.h"

namespace AdventOfCode24::Day2 {
    std::vector<int> level_trend(const std::vector<int>& values);
    std::vector<int> read_line(std::istringstream& line);
    bool level_trend_is_valid(const std::vector<int>& values, bool problem_dampening);
    bool check_numbers(const std::vector<int>& values);
    std::vector<bool> check_reactor_safety(const std::filesystem::path& input_file, bool problem_dampening);
};
