#include <gtest/gtest.h>
#include "advent_of_code/day_6.hxx"
#include "spdlog/spdlog.h"

using namespace AdventOfCode24::Day6;

#ifndef ADVENT_OF_CODE_DATA
  #error "ADVENT_OF_CODE_DATA is not defined!"
#endif

TEST(TestAOC, TestDay6pt1_create_map) {
    const Map expected(
        {10, 10},
        {6, 4},
        {-1, 0},
        {
            {0, 4}, {1, 9},
            {3, 2}, {4, 7},
            {6, 1}, {7, 8},
            {8, 0}, {9, 6}
        }
    );

    const std::filesystem::path input_file = std::filesystem::path(ADVENT_OF_CODE_DATA) / "day_6_1.txt";

    const Map map{get_area_map(input_file)};

    ASSERT_EQ(map.guard_direction, expected.guard_direction);
    ASSERT_EQ(map.guard_direction, expected.guard_direction);
    ASSERT_EQ(map.obstacles, expected.obstacles);
    ASSERT_EQ(map.size, expected.size);

    show_result(map);
}

TEST(TestAOC, TestDay6pt1_new_direction) {
    const coord original{0, 1};
    coord expected{1, 0};
    coord new_coord = new_direction(original);
    ASSERT_EQ(new_coord, expected);
    new_coord = new_direction(new_coord);
    expected = {0, -1};
    ASSERT_EQ(new_coord, expected);
    new_coord = new_direction(new_coord);
    expected = {-1, 0};
    ASSERT_EQ(new_coord, expected);
    new_coord = new_direction(new_coord);
    expected = {0, 1};
    ASSERT_EQ(new_coord, expected);
}

TEST(TestAOC, TestDay6pt1_example) {
    const std::filesystem::path input_file = std::filesystem::path(ADVENT_OF_CODE_DATA) / "day_6_1.txt";
    const Map map{get_area_map(input_file)};

    const std::pair<ExitStatus, std::vector<coord>> path_check{get_path(map)};
    const std::set<coord> unique_elem(path_check.second.begin(), path_check.second.end());
    
    show_result(map, path_check.second);
    
    ASSERT_EQ(unique_elem.size(), 41);
}

TEST(TestAOC, TestDay6pt2_example) {
    const std::filesystem::path input_file = std::filesystem::path(ADVENT_OF_CODE_DATA) / "day_6_1.txt";
    const Map map{get_area_map(input_file)};

    const std::vector<coord> loopback_obs_positions{patrol_loop_obstruction_positions(map)};

    ASSERT_EQ(loopback_obs_positions.size(), 6);
}