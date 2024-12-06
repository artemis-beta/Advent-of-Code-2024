
#pragma once

#include <fstream>
#include <string>

#include "spdlog/spdlog.h"

namespace AdventOfCode24::Day6 {
	typedef std::pair<int, int> coord;
	typedef std::pair<int, int> direction;
	typedef std::pair<coord,direction> status;
	std::pair<coord, std::vector<coord>> get_area_map(const std::filesystem::path& input_file);
};
