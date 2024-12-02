#include <gtest/gtest.h>
#include "advent_of_code/day_1.hxx"

#include <filesystem>
#include <numeric>

#ifndef ADVENT_OF_CODE_DATA
  #error "ADVENT_OF_CODE_DATA is not defined!"
#endif

TEST(TestAOC, TestDay1pt1) {
  const std::filesystem::path input_file = std::filesystem::path(ADVENT_OF_CODE_DATA) / "day_1_1.txt";

  const std::vector<int> diffs{AdventOfCode24::Day1::get_differences(input_file)};
  const int diff_total = std::accumulate(diffs.begin(), diffs.end(), 0);

  ASSERT_EQ(diff_total, 11);
}

TEST(TestAOC, TestDay1pt2) {
  const std::filesystem::path input_file = std::filesystem::path(ADVENT_OF_CODE_DATA) / "day_1_1.txt";

  const std::vector<int> diffs{AdventOfCode24::Day1::get_similarity_scores(input_file)};
  const int score_total = std::accumulate(diffs.begin(), diffs.end(), 0);

  ASSERT_EQ(score_total, 31);
}
