#include <gtest/gtest.h>
#include <string>
#include <unordered_set>
#include "advent_of_code/day_8.hxx"
#include "spdlog/common.h"
#include "spdlog/spdlog.h"

using namespace AdventOfCode24::Day8;

#ifndef ADVENT_OF_CODE_DATA
  #error "ADVENT_OF_CODE_DATA is not defined!"
#endif

TEST(TestAOC, TestDay8pt1_example) {
  spdlog::set_level(spdlog::level::debug);
  const std::filesystem::path input_file = std::filesystem::path(ADVENT_OF_CODE_DATA) / "day_8_1.txt";
  const area_map antennae{
      {'0', {{1, 8}, {2, 5}, {3, 7}, {4, 4}}},
      {'A', {{5, 6}, {8, 8}, {9, 9}}}
  };
  const std::unordered_set<coord> antinodes{
    {0, 6},
    {0, 11},
    {1, 3},
  {2, 4},
  {2, 10},
    {3, 2},
    {4, 9},
    {5, 1},
  {6, 3},
  {7, 0},
  {7, 7},
  {10, 10},
  {11, 10}
  };
  const coord size{12, 12};

  Map communication_network{get_communication_network(input_file)};

  ASSERT_FALSE(communication_network.antennae.empty()) << "No antennae found.";
  ASSERT_EQ(communication_network.size, size);

  calculate_antinode_positions(communication_network, false);

  ASSERT_FALSE(communication_network.antinodes.empty()) << "No antinodes found.";

  print_map(communication_network);

  for(const auto& antenna : antennae) {
    for(const coord& pos : antenna.second) {
      auto find_entries = communication_network.antennae.find(antenna.first);

      ASSERT_TRUE(find_entries != communication_network.antennae.end()) << "Expected key '" << antenna.first << "' in antennae";

      auto find_pos = std::find(communication_network.antennae.at(antenna.first).begin(), communication_network.antennae.at(antenna.first).end(), pos);

      ASSERT_TRUE(find_pos != communication_network.antennae.at(antenna.first).end()) << "Expected coord " << pos.first
      << "," << pos.second << " in '" << antenna.first << "' in antennae";
    }
  }

  for(const coord& antinode : antinodes) {
    auto find_antinode = std::find(communication_network.antinodes.begin(), communication_network.antinodes.end(), antinode);

    ASSERT_TRUE(find_antinode != communication_network.antinodes.end()) << "Expected antinode at " << antinode.first << "," << antinode.second;
  }
}

TEST(TestAOC, TestDay8pt2_example) {
  const std::filesystem::path input_file = std::filesystem::path(ADVENT_OF_CODE_DATA) / "day_8_1.txt";

  Map communication_network{get_communication_network(input_file)};
  calculate_antinode_positions(communication_network, true);

  const std::unordered_set<coord> antinodes{
      {0, 0},
      {0, 1},
      {0, 6},
          {0, 11},
      {1, 1},
      {1, 3},
      {2, 2},
      {2, 4},
      {2, 10},
    {3, 2},
    {3, 3},
    {4, 9},
    {5, 1},
    {5, 5},
    {5, 11},
  {6, 3},
  {6, 6},
  {7, 0},
  {7, 5},
  {7, 7},
  {8, 2},
  {9, 4},
  {10, 1},
  {10, 10},
  {11, 3},
  {11, 10},
  {11, 11}
  };

  print_map(communication_network);

  for(const coord& antinode : antinodes) {
    auto find_antinode = std::find(communication_network.antinodes.begin(), communication_network.antinodes.end(), antinode);

    ASSERT_TRUE(find_antinode != communication_network.antinodes.end()) << "Expected antinode at " << antinode.first << "," << antinode.second;
  }
}