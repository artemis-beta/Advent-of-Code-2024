#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <filesystem>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <optional>

#include "spdlog/spdlog.h"

namespace AdventOfCode::Day1 {
  typedef std::pair<std::vector<int>, std::vector<int>> file_data;
  std::optional<file_data> read_data(const std::filesystem::path& input);
  std::vector<int> get_differences(const std::filesystem::path& input);
  std::vector<int> get_similarity_scores(const std::filesystem::path& input);
};
