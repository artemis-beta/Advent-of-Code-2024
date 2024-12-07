#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <unordered_map>
#include <iostream>
#include <algorithm>

#include "spdlog/spdlog.h"

namespace AdventOfCode24::Day6 {
	typedef std::pair<int, int> coord;

	class Map {
		public:
			coord size{-1, -1};
			coord guard_position{-1,-1};
			coord guard_direction{0, 0};
			std::vector<coord> obstacles;
			Map(const coord& size, const coord& guard_position, const coord& guard_direction, const std::vector<coord>& obstacles) :
				size(size), guard_position(guard_position), guard_direction(guard_direction), obstacles(obstacles) {}
			Map(){};
			Map(const Map& other) : size(other.size), guard_position(other.guard_position), guard_direction(other.guard_direction), obstacles(other.obstacles) {} 
	};

	enum class ExitStatus {
		ExitedMap,
		LoopDetected,
	};

	Map get_area_map(const std::filesystem::path& input_file);
	void show_result(const Map& map, const std::vector<coord>&path={});
	coord new_direction(const coord& current_direction);
	std::pair<ExitStatus, std::vector<coord>> get_path(const Map& map);
	std::vector<coord> patrol_loop_obstruction_positions(const Map& map);
};
