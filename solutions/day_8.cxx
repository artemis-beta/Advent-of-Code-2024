#include <filesystem>
#include <iostream>
#include <numeric>
#include <string>
#include <set>
#include "spdlog/spdlog.h"

#include "advent_of_code/day_8.hxx"

using namespace AdventOfCode24::Day8;

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

    Map communication_network{get_communication_network(input_file)};
    Map communication_network_w_resonance{communication_network};
    calculate_antinode_positions(communication_network, false);
    calculate_antinode_positions(communication_network_w_resonance, true);

    const size_t total_antinodes{communication_network.antinodes.size()};
    print_map(communication_network);
    spdlog::info("For file '" + input_file.string() + "' the total number of antinodes is " + std::to_string(total_antinodes));

    const size_t total_antinodes_w_resonance{communication_network_w_resonance.antinodes.size()};
    print_map(communication_network_w_resonance);
    spdlog::info("Taking into account resonant harmonics this is " + std::to_string(total_antinodes_w_resonance));
}