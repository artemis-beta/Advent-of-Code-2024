#include <gtest/gtest.h>
#include "day_1.hxx"

#include <filesystem>
#include <numeric>

#ifndef ADVENT_OF_CODE_DATA
  #error "ADVENT_OF_CODE_DATA is not defined!"
#endif

using namespace AdventOfCode::Day1;

TEST(TestAOC, TestDay1) {
  const std::filesystem::path input_file = std::filesystem::path(ADVENT_OF_CODE_DATA) / "day_1_1.txt";

  const std::vector<int> diffs{get_differences(input_file)};
  const int diff_total = std::accumulate(diffs.begin(), diffs.end(), 0);

  ASSERT_EQ(diff_total, 11);
}
