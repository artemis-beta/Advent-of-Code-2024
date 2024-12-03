#pragma once
#include <vector>
#include <regex>
#include <filesystem>
#include <fstream>
#include <numeric>
#include <functional>
#include <stdexcept>
#include <optional>
#include <string>

#include "spdlog/spdlog.h"

namespace AdventOfCode24::Day3 {
    typedef std::pair<std::vector<int>, std::vector<int>> logic_set;
    bool use_calculation(int operation_index, logic_set logic_indexes);
    logic_set get_logic_indexes(const std::string& line);
    std::vector<std::pair<int, int>> parse_line(const std::string& line, bool logic_enabled, bool& do_state);
    std::vector<int> calculate_file_lines(const std::filesystem::path& input_file, bool logic_enabled);
};