#pragma once

#include <fstream>
#include <deque>
#include <string>
#include <algorithm>
#include <filesystem>

#include "spdlog/spdlog.h"

namespace AdventOfCode24::Day4 {
	int wordsearch_matches(const std::string& word, const std::deque<std::string>& block, const int block_index);
	int x_matches(const std::string& word, const std::deque<std::string>& block, const int block_index);
	int count_wordsearch_matches_in_file(const std::filesystem::path& input_file, const std::string& word);
	int count_matches_in_file(const std::filesystem::path& input_file, const std::string& word, bool wordsearch);
};
