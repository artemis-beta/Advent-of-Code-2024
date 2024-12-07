#include <filesystem>
#include <string>
#include <set>
#include "spdlog/spdlog.h"

#include "advent_of_code/day_6.hxx"

using namespace AdventOfCode24::Day6;

int main(int argc, char** argv) {
    if(argc != 2) {
        spdlog::error("Expected input data file!");
        return 1;
    }

    spdlog::set_level(spdlog::level::info);

    const std::filesystem::path input_file{argv[1]};
    if(!std::filesystem::exists(input_file)) {
        throw std::runtime_error("File " + input_file.string() + " does not exist!");
    }

    const Map map{get_area_map(input_file)};

    const std::pair<ExitStatus, std::vector<coord>> path_check{get_path(map)};
    const std::set<coord> unique_elem(path_check.second.begin(), path_check.second.end());
    const std::vector<coord> optimum_obstacle_pos{patrol_loop_obstruction_positions(map)};

    spdlog::info("For file '" + input_file.string() + "' the number of unique coordinates visited by the guard is " + std::to_string(unique_elem.size()));
    spdlog::info("The number of locations in which an obstacle can be placed to cause the guard to loop is " + std::to_string(optimum_obstacle_pos.size()));
    
    show_result(map, path_check.second);
}