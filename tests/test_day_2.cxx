#include <algorithm>
#include <gtest/gtest.h>
#include "advent_of_code/day_2.hxx"
#include "spdlog/common.h"
#include "spdlog/spdlog.h"

#include <filesystem>

#ifndef ADVENT_OF_CODE_DATA
  #error "ADVENT_OF_CODE_DATA is not defined!"
#endif

TEST(TestAOC, TestDay2pt1_file1) {
    spdlog::set_level(spdlog::level::debug);
    const std::filesystem::path input_file = std::filesystem::path(ADVENT_OF_CODE_DATA) / "day_2_1.txt";

    const std::vector<bool> layer_safety = AdventOfCode24::Day2::check_reactor_safety(input_file, false);

    ASSERT_EQ(layer_safety.size(), 6);

    const int n_safe = std::count_if(layer_safety.begin(), layer_safety.end(), [](bool x){return x;});

    ASSERT_EQ(n_safe, 2);
}

TEST(TestAOC, TestDay2pt1_file2) {
    spdlog::set_level(spdlog::level::debug);
    const std::filesystem::path input_file = std::filesystem::path(ADVENT_OF_CODE_DATA) / "day_2_2.txt";

    const std::vector<bool> layer_safety = AdventOfCode24::Day2::check_reactor_safety(input_file, true);

    ASSERT_EQ(layer_safety.size(), 25);

    const int n_safe = std::count_if(layer_safety.begin(), layer_safety.end(), [](bool x){return x;});

    ASSERT_EQ(n_safe, 24);
}

TEST(TestAOC, TestDay2pt2) {
    const std::filesystem::path input_file = std::filesystem::path(ADVENT_OF_CODE_DATA) / "day_2_1.txt";

    const std::vector<bool> layer_safety = AdventOfCode24::Day2::check_reactor_safety(input_file, true);

    const int n_safe = std::count_if(layer_safety.begin(), layer_safety.end(), [](bool x){return x;});

    ASSERT_EQ(n_safe, 4);
}