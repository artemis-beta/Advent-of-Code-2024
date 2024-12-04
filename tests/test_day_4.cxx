
#include <gtest/gtest.h>
#include <string>
#include "advent_of_code/day_3.hxx"

using namespace AdventOfCode::Day4;

#ifndef ADVENT_OF_CODE_DATA
  #error "ADVENT_OF_CODE_DATA is not defined!"
#endif

TEST(TestAOC, TestDay4pt1_block_parse) {
	const std::string word{"XMAS"};
	const std::string block{"XJYSAMXOTX\nMHRHXMASMD\nAGKUWQAP\nSCYKOSTRY\n"};
	const int n_matches{get_matches(word, block)};

	ASSERT_EQ(n_matches, 4);
}

