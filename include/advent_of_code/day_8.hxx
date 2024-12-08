#pragma once

#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <filesystem>
#include <algorithm>
#include <sstream>
#include <string>
#include <functional>
#include <iostream>

#include "spdlog/spdlog.h"

typedef std::pair<int,int> coord;

// Need to create custom hashing for the std::pair
template<>
struct std::hash<coord> {
    std::size_t operator()(const coord& c) const {
        return std::hash<int>()(c.first) ^ (std::hash<int>()(c.second) << 1);
    }
};

namespace AdventOfCode24::Day8 {
    typedef std::unordered_map<char, std::unordered_set<coord>> area_map;

    class Map {
        public:
            area_map antennae;
            std::unordered_set<coord> antinodes;
            coord size;
        Map(){};
        Map(const Map& map) : antennae(map.antennae), antinodes(map.antinodes), size(map.size) {}
    };

    coord smallest_vector(const coord& coordinate);
    Map get_communication_network(const std::filesystem::path& input_file);
    void calculate_antinode_positions(Map& communication_network, bool resonant_harmonics);
    void print_map(const Map& communication_network);
};