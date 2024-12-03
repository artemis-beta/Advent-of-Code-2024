#include <gtest/gtest.h>
#include "advent_of_code/day_3.hxx"


#include <filesystem>
#include <sstream>
#include <utility>
#include <vector>

#ifndef ADVENT_OF_CODE_DATA
  #error "ADVENT_OF_CODE_DATA is not defined!"
#endif

TEST(TestAOC, TestDay3pt1_line_parse) {
    std::istringstream sstr(std::string("Gmul(4,5)L3£9mul(34,)&3yMul(3,4)?"), std::ios::in);
    const std::vector<std::pair<int,int>> parsed{AdventOfCode24::Day3::parse_line(sstr)};
    
    ASSERT_EQ(parsed.size(), 1);

    ASSERT_EQ(parsed[0].first, 4);
    ASSERT_EQ(parsed[0].second, 5);
}