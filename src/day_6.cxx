#include "advent_of_code/day_6.hxx"
#include "spdlog/spdlog.h"
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace AdventOfCode24::Day6 {
	coord new_direction(const coord& current_direction) {
		if(current_direction.first > 0) {
			return {0, -1};
		}
		if(current_direction.first < 0) {
			return {0, 1};
		}
		if(current_direction.second > 0) {
			return {1, 0};
		}
		if(current_direction.second < 0) {
			return {-1, 0};
		}

		throw std::runtime_error("Direction change failed for direction " + std::to_string(current_direction.first) + "," + std::to_string(current_direction.second));
	}

	Map get_area_map(const std::filesystem::path& input_file) {
		std::ifstream read_in(input_file, std::ios::in);
		std::string line;
		Map area_map;

		const std::unordered_map<char, coord> directions{
			{'^', {-1, 0}},
			{'v', {1, 0}},
			{'>', {0, 1}},
			{'<', {0, -1}}
		};

		int line_num{0};

        while (std::getline(read_in, line)) {
			int column{0};
			area_map.size.second = line.size();

			for(const char& symbol : line) {
				if(symbol == '.') {
					column++;
					continue;
				}

				// Firstly check if this is an obstruction location
				if(symbol == '#') {
					spdlog::debug("Found obstacle at [" + std::to_string(line_num) + "," + std::to_string(column) + "]");
					area_map.obstacles.push_back({line_num, column});
					column++;
					continue;
				}

				// Secondly check if this location is where the guard starts
				auto find_guard = directions.find(symbol);

				if(find_guard != directions.end()) {
					const coord start_dir{directions.at(symbol)};
					std::string sym_str{symbol};
					area_map.guard_direction = start_dir;
					area_map.guard_position = {line_num, column};
					spdlog::debug("Found Guard at [" + std::to_string(line_num) + "," + std::to_string(column) + "]");
					spdlog::debug("Guard facing direction '" + sym_str + "'");
				}
				column++;
			}

			line_num++;
		}

		area_map.size.first = line_num;

		return area_map;
	}

	void show_result(const Map& map, const std::vector<coord>&path) {
		for(int row{0}; row < map.size.first; ++row) {
			for(int column{0}; column < map.size.second; ++column) {
				const coord current{row, column};
				auto find_obstacle = std::find(map.obstacles.begin(), map.obstacles.end(), current);
				auto find_path = std::find(path.begin(), path.end(), current);

				if(row == map.obstacles[map.obstacles.size() - 1].first && column == map.obstacles[map.obstacles.size() - 1].second) {
					std::cout << "\x1B[34m■\033[0m";
				} else if(find_obstacle != map.obstacles.end()) {
					std::cout << "\x1B[31m■\033[0m";
				} else if(find_path != path.end()) {
					std::cout << "\x1B[32m■\033[0m";
				} else {
					std::cout << "■";
				}
			}

			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	std::pair<ExitStatus, std::vector<coord>> get_path(const Map& map) {
		spdlog::debug("Guard starting at " + std::to_string(map.guard_position.first) + "," + std::to_string(map.guard_position.second));
		coord current_pos{map.guard_position};
		coord current_dir{map.guard_direction};
		std::vector<coord> path{current_pos};
		const int HARD_LIMIT{map.size.first * map.size.second};

		while(true) {
			const coord next_coord{
				current_pos.first + current_dir.first, 
				current_pos.second + current_dir.second
			};

			const coord next_coord_2{
				next_coord.first + current_dir.first, 
				next_coord.second + current_dir.second
			};

			auto find_obstacle = std::find(map.obstacles.begin(), map.obstacles.end(), next_coord);

			auto find_next = std::find(path.begin(), path.end(), next_coord);
			auto find_next_2 = std::find(path.begin(), path.end(), next_coord_2);

			if(find_next != path.end() && find_next_2 != path.end()) {
				const int next_distance = std::distance(path.begin(), find_next);
				const int next_2_distance = std::distance(path.begin(), find_next_2);

				if(next_2_distance - next_distance == 1) {
					spdlog::warn("Loop detected aborting path.");
					return {ExitStatus::LoopDetected, path};
				}
			}

			// Need to prevent infinite looping, if path size is comparable to grid size this is likely a loop
			if(path.size() > HARD_LIMIT) {
				spdlog::warn("Path size is unusually large, assuming loop detected and aborting path.");
				return {ExitStatus::LoopDetected, path};
			}

			// Check if an obstacle was encountered
			if(find_obstacle != map.obstacles.end()) {
				spdlog::debug("Changing direction at " + std::to_string(current_pos.first) + "," + std::to_string(current_pos.second));
				current_dir = new_direction(current_dir);
			} else if(
				current_pos.first < 0 || current_pos.first >= map.size.first ||
				current_pos.second < 0 || current_pos.second >= map.size.second
			) {
				spdlog::debug("Guard exiting map region at " + std::to_string(current_pos.first) + "," + std::to_string(current_pos.second));
				path.pop_back();
				break;
			} else {
				current_pos = next_coord;
				path.push_back(current_pos);
			}
		}

		return {ExitStatus::ExitedMap, path};
	}
	std::vector<coord> patrol_loop_obstruction_positions(const Map& map) {
		// FIXME: Inefficiently done due to time constraints
		std::vector<coord> loopback_obs_positions;

		for(int row{0}; row < map.size.first; ++row) {
			spdlog::info("Process is " + std::to_string(1.0 * row / map.size.first * 100.0) + "% complete");
			for(int column{0}; column < map.size.second; ++column) {
				const int total_cells{map.size.first * map.size.second};
				spdlog::debug("Placing obstacle at " + std::to_string(row) + "," + std::to_string(column));
				// Exclude guard position
				if(column == map.guard_position.second && row == map.guard_position.first) continue;

				const coord current{row, column};

				// Exclude positions of current obstacles
				auto find_existing = std::find(map.obstacles.begin(), map.obstacles.end(), current);

				if(find_existing != map.obstacles.end()) continue;

				Map modified_map(map);
				modified_map.obstacles.push_back({row, column});

				const std::pair<ExitStatus, std::vector<coord>> path_check{get_path(modified_map)};

				if(path_check.first == ExitStatus::LoopDetected) {
					show_result(modified_map, path_check.second);
					loopback_obs_positions.push_back(current);
				}
			}
		}

		return loopback_obs_positions;
	}
};
