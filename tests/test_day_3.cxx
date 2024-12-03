#include <gtest/gtest.h>
#include "advent_of_code/day_3.hxx"


#include <filesystem>
#include <sstream>
#include <utility>
#include <vector>
#include <numeric>

#ifndef ADVENT_OF_CODE_DATA
  #error "ADVENT_OF_CODE_DATA is not defined!"
#endif

TEST(TestAOC, TestDay3pt1_line_parse) {
    const std::string line("Gmul(4,5)L3£9mul(34,)&3yMul(3,4)?");
    bool do_state{true};
    const std::vector<std::pair<int,int>> parsed{AdventOfCode24::Day3::parse_line(line, false, do_state)};
    
    ASSERT_EQ(parsed.size(), 1);

    ASSERT_EQ(parsed[0].first, 4);
    ASSERT_EQ(parsed[0].second, 5);
}

TEST(TestAOC, TestDay3pt1) {
  spdlog::set_level(spdlog::level::debug);
  const std::filesystem::path input_file = std::filesystem::path(ADVENT_OF_CODE_DATA) / "day_3_1.txt";
  const std::vector<int> line_totals{AdventOfCode24::Day3::calculate_file_lines(input_file, false)};

  const int overall_total = std::accumulate(line_totals.begin(), line_totals.end(), 0);

  ASSERT_EQ(line_totals.size(), 1);
  ASSERT_EQ(overall_total, 161);
}

TEST(TestAOC, TestDay3pt2) {
  spdlog::set_level(spdlog::level::debug);
  const std::filesystem::path input_file = std::filesystem::path(ADVENT_OF_CODE_DATA) / "day_3_2.txt";
  const std::vector<int> line_totals{AdventOfCode24::Day3::calculate_file_lines(input_file, true)};

  const int overall_total = std::accumulate(line_totals.begin(), line_totals.end(), 0);

  ASSERT_EQ(line_totals.size(), 1);
  ASSERT_EQ(overall_total, 48);
}

TEST(TestAOC, TestDay3pt2_scenario_1) {
  spdlog::set_level(spdlog::level::debug);
  const std::filesystem::path input_file = std::filesystem::path(ADVENT_OF_CODE_DATA) / "day_3_3.txt";
  const std::vector<int> line_totals{AdventOfCode24::Day3::calculate_file_lines(input_file, true)};

  const int overall_total = std::accumulate(line_totals.begin(), line_totals.end(), 0);

  ASSERT_EQ(line_totals.size(), 2);
  ASSERT_EQ(overall_total, 17);
}