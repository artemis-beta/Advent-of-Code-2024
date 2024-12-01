#pragma once

#include <algorithm>
#include <iostream>
#include <deque>
#include <string>
#include <stdexcept>
#include <format>
#include <vector>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <optional>

#include "spdlog/spdlog.h"

namespace AdventOfCode::Day1 {
  typedef std::pair<std::deque<int>, std::deque<int>> file_data;
  std::optional<file_data> read_data(const std::filesystem::path& input);
  std::vector<int> get_differences(const std::filesystem::path& input);
};
