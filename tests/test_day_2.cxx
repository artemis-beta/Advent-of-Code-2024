#include <algorithm>
#include <gtest/gtest.h>
#include "advent_of_code/day_2.hxx"
#include "spdlog/common.h"
#include "spdlog/spdlog.h"

#include <filesystem>
#include <sstream>
#include <string>

#ifndef ADVENT_OF_CODE_DATA
  #error "ADVENT_OF_CODE_DATA is not defined!"
#endif

using namespace AdventOfCode24::Day2;

TEST(TestAOC, TestDay2pt1_trend) {
    const std::string line("1 2 4 7 3 7 2 1");
    std::istringstream sstr;
    sstr.str(line);
    const std::vector<int> values{read_line(sstr)};
    const std::vector<int> trend{level_trend(values)};
    const std::vector<int> expected{1, 2, 3, -4, 4, -5, -1};

    ASSERT_EQ(expected.size(), trend.size());

    for(int i{0}; i < trend.size(); ++i) ASSERT_EQ(trend[i], expected[i]);
}

TEST(TestAOC, TestDay2pt1_invalid) {
    const std::string line("1 2 4 7 3 7 2 1");
    std::istringstream sstr;
    sstr.str(line);

    const std::vector<int> values{read_line(sstr)};
    const bool layer_safety = AdventOfCode24::Day2::level_trend_is_valid(values, false);

    ASSERT_FALSE(layer_safety);
}

TEST(TestAOC, TestDay2pt1_valid) {
    const std::string line("1 3 5 8 9 11 13");
    std::istringstream sstr;
    sstr.str(line);

    const std::vector<int> values{read_line(sstr)};
    const bool layer_safety = AdventOfCode24::Day2::level_trend_is_valid(values, false);

    ASSERT_TRUE(layer_safety);
}

TEST(TestAOC, TestDay2pt1_file1) {
    const std::filesystem::path input_file = std::filesystem::path(ADVENT_OF_CODE_DATA) / "day_2_1.txt";

    const std::vector<bool> layer_safety = AdventOfCode24::Day2::check_reactor_safety(input_file, false);

    ASSERT_EQ(layer_safety.size(), 6);

    const int n_safe = std::count_if(layer_safety.begin(), layer_safety.end(), [](bool x){return x;});

    ASSERT_EQ(n_safe, 2);
}

TEST(TestAOC, TestDay2pt1) {
    const std::filesystem::path input_file = std::filesystem::path(ADVENT_OF_CODE_DATA) / ".." / ".." / "solutions" / "data" / "day_2.txt";

    const std::vector<bool> layer_safety = AdventOfCode24::Day2::check_reactor_safety(input_file, false);

    ASSERT_EQ(layer_safety.size(), 1000);

    const int n_safe = std::count_if(layer_safety.begin(), layer_safety.end(), [](bool x){return x;});

    ASSERT_EQ(n_safe, 402);
}

TEST(TestAOC, TestDay2pt2_file1) {
    std::vector<bool> expected{true, false, false, true, true, true};
    const std::filesystem::path input_file = std::filesystem::path(ADVENT_OF_CODE_DATA) / "day_2_1.txt";
    int index{0};

    std::ifstream read_in(input_file, std::ios::in);
    std::string line;

    while (std::getline(read_in, line)) {
        spdlog::info("Running Line " + std::to_string(index));
        std::istringstream stream(line, std::ios::in);

        const std::vector<int> values{read_line(stream)};
        const bool layer_safety = AdventOfCode24::Day2::level_trend_is_valid(values, true);

        ASSERT_EQ(layer_safety, expected[index]);

        index++;
    }
}

TEST(TestAOC, TestDay2pt2_file2) {
    const std::filesystem::path input_file = std::filesystem::path(ADVENT_OF_CODE_DATA) / "day_2_2.txt";
    int index{0};

    std::ifstream read_in(input_file, std::ios::in);
    std::string line;

    while (std::getline(read_in, line)) {
        spdlog::info("Running Line " + std::to_string(index));
        std::istringstream stream(line, std::ios::in);

        const std::vector<int> values{read_line(stream)};
        const bool layer_safety = AdventOfCode24::Day2::level_trend_is_valid(values, true);

        bool expected = (index > 24) ? false : true;

        ASSERT_EQ(layer_safety, expected);

        index++;
    }
}

TEST(TestAOC, TestDay2pt2) {
    std::vector<bool> expected{true, false, false, true, true, true};
    const std::filesystem::path input_file = std::filesystem::path(ADVENT_OF_CODE_DATA) / ".." / ".." / "solutions" / "data" / "day_2.txt";
    int index{0};
    int counter{0};

    std::ifstream read_in(input_file, std::ios::in);
    std::string line;

    while (std::getline(read_in, line)) {
        spdlog::info("Running Line " + std::to_string(index));
        std::istringstream stream(line, std::ios::in);

        const std::vector<int> values{read_line(stream)};
        const bool layer_safety = AdventOfCode24::Day2::level_trend_is_valid(values, true);

        if(layer_safety) counter++;
        index++;
    }

    ASSERT_EQ(counter, 455);
}