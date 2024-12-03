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

#include "spdlog/spdlog.h"

namespace AdventOfCode24::Day2 {
    bool safe_pair(int val_1, int val_2, int direction);
    std::optional<int> check_intervals(const std::vector<int>& numbers);
    bool report_is_safe(std::istringstream& line, bool allow_dampening);
    std::vector<bool> check_reactor_safety(const std::filesystem::path& input_file, bool problem_dampening);
};
