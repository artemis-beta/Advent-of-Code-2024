#pragma once

#include <fstream>
#include <string>
#include <filesystem>
#include <unordered_map>
#include <optional>
#include <exception>
#include <sstream>

#include "spdlog/spdlog.h"

namespace AdventOfCode24::Day5 {
    std::optional<std::pair<int, int>> parse_rule(const std::string& order_statement, const char& delimiter);
    bool check_sequence(const std::vector<int>& sequence, const std::unordered_map<int, std::vector<int>>& ruleset);
    std::vector<int> process_file(const std::filesystem::path& input_file, const char& rule_delimiter='|', const char& sequence_delimiter=',', bool count_fixed=false);
    std::vector<int> order_line(const std::vector<int>& sequence, const std::unordered_map<int, std::vector<int>>& ruleset);
    bool sorting_algorithm(int val_1, int val_2);
};