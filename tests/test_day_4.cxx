
#include <deque>
#include <gtest/gtest.h>
#include <string>
#include "advent_of_code/day_4.hxx"
#include "spdlog/spdlog.h"

using namespace AdventOfCode24::Day4;

#ifndef ADVENT_OF_CODE_DATA
  #error "ADVENT_OF_CODE_DATA is not defined!"
#endif

TEST(TestAOC, TestDay4pt1_example) {
  spdlog::set_level(spdlog::level::debug);
  const std::string word{"XMAS"};
  const std::filesystem::path input_file = std::filesystem::path(ADVENT_OF_CODE_DATA) / "day_4_1.txt";
  const int word_count{AdventOfCode24::Day4::count_matches_in_file(input_file, word, true)};

  ASSERT_EQ(word_count, 18);
}

TEST(TestAOC, TestDay4pt2_example_1) {
  const std::string word{"MAS"};
  const std::filesystem::path input_file = std::filesystem::path(ADVENT_OF_CODE_DATA) / "day_4_1.txt";
  const int word_count{AdventOfCode24::Day4::count_matches_in_file(input_file, word, false)};

  ASSERT_EQ(word_count, 9);
}

TEST(TestAOC, TestDay4pt1_example_2) {
  const std::string word{"XMAS"};
  const std::filesystem::path input_file = std::filesystem::path(ADVENT_OF_CODE_DATA) / "day_4_2.txt";
  const int word_count{AdventOfCode24::Day4::count_matches_in_file(input_file, word, true)};

  ASSERT_EQ(word_count, 18);
}

TEST(TestAOC, TestDay4pt1) {
  const std::string word{"XMAS"};
  const std::filesystem::path input_file = std::filesystem::path(ADVENT_OF_CODE_DATA) / ".." / ".." / "solutions" / "data" / "day_4.txt";
  const int word_count{AdventOfCode24::Day4::count_matches_in_file(input_file, word, true)};

  ASSERT_EQ(word_count, 2654);
}

TEST(TestAOC, TestDay4pt2) {
  const std::string word{"MAS"};
  const std::filesystem::path input_file = std::filesystem::path(ADVENT_OF_CODE_DATA) / ".." / ".." / "solutions" / "data" / "day_4.txt";
  const int word_count{AdventOfCode24::Day4::count_matches_in_file(input_file, word, false)};

  ASSERT_EQ(word_count, 1990);
}

