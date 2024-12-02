/**
 * @file day_1.hxx
 * @author Kristian Zarebski (krizar312@gmail.com)
 * @brief Methods for solutions to Day 1 of AOC24
 * @version 0.1
 * @date 2024-12-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */
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

namespace AdventOfCode24::Day1 {
  typedef std::pair<std::vector<int>, std::vector<int>> file_data;

  /**
   * @brief Read data from an input file containing historian location lists
   * 
   * @param input the input data file containing lists
   * @return std::optional<file_data> the read data if successful
   */
  std::optional<file_data> read_data(const std::filesystem::path& input);

  /**
   * @brief Get the differences between pair of ordered historian location lists
   * 
   * @param input the input data file containing lists
   * @return std::vector<int> a vector of differences between the ordered lists
   */
  std::vector<int> get_differences(const std::filesystem::path& input);

  /**
   * @brief Get the similarity scores for a pair of historian location lists
   * 
   * @param input the input data file containing lists
   * @return std::vector<int> a vector of similarity scores for the two lists
   */
  std::vector<int> get_similarity_scores(const std::filesystem::path& input);
};
