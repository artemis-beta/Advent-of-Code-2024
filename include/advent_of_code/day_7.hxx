#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <sstream>
#include <exception>

#include "spdlog/spdlog.h"

namespace AdventOfCode24::Day7 {
    int64_t check_calibration_line(
        const std::string& line,
        bool include_concatenator,
        const char& delimiter = ':'
    );
    std::vector<int64_t> process_file(const std::filesystem::path& input_file, bool include_concatenator);
};