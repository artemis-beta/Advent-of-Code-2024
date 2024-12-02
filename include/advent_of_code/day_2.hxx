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
    const int BUFFER_SIZE{1024};
    bool safe_pair(int val_1, int val_2, int direction);
    int check_intervals(const std::vector<int>& numbers);
    bool report_is_safe(std::istringstream& line);
    std::vector<bool> check_reactor_safety(const std::filesystem::path& input_file, bool problem_dampening);
};
