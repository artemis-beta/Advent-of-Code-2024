#include <gtest/gtest.h>
#include <numeric>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>
#include "advent_of_code/day_5.hxx"
#include "spdlog/spdlog.h"

using namespace AdventOfCode24::Day5;

#ifndef ADVENT_OF_CODE_DATA
  #error "ADVENT_OF_CODE_DATA is not defined!"
#endif

TEST(TestAOC, TestDay5pt1_parse_rule) {
    spdlog::set_level(spdlog::level::debug);
    const std::string test_line("34|78");
    const std::optional<std::pair<int, int>> rule{parse_rule(test_line, '|')};
    const std::pair<int, int> expected{34,78};

    ASSERT_TRUE(rule.has_value());
    ASSERT_EQ(expected, rule.value());
}

TEST(TestAOC, TestDay5pt1_sequence_check_pass) {
    const std::unordered_map<int, std::vector<int>> rule_set{
        {47, {53, 13, 29}},
    };
    const std::vector<int> sequence{rule_set.at(47)};
    ASSERT_TRUE(check_sequence(sequence, rule_set));
}

TEST(TestAOC, TestDay5pt1_sequence_check_fail) {
    const std::unordered_map<int, std::vector<int>> rule_set{
        {47, {53, 13, 29}},
    };
    const std::vector<int> sequence{53, 47, 13, 29};
    ASSERT_FALSE(check_sequence(sequence, rule_set));
}

TEST(TestAOC, TestDay5pt1_example) {
    spdlog::set_level(spdlog::level::debug);
    const std::filesystem::path input_file = std::filesystem::path(ADVENT_OF_CODE_DATA) / "day_5_1.txt";
    const std::vector<int> middle_values{process_file(input_file, '|', ',')};
    const std::vector<int> expected{61, 53, 29, 0, 0, 0};

    ASSERT_EQ(middle_values.size(), expected.size());

    for(int i{0}; i < expected.size(); ++i) {
        ASSERT_EQ(middle_values[i], expected[i]);
    }
}

TEST(TestAOC, TestDay5pt2_example) {
    spdlog::set_level(spdlog::level::debug);
    const std::filesystem::path input_file = std::filesystem::path(ADVENT_OF_CODE_DATA) / "day_5_1.txt";
    const std::vector<int> middle_values{process_file(input_file, '|', ',', true)};
    const std::vector<int> expected{0, 0, 0, 47, 29, 47};

    ASSERT_EQ(middle_values.size(), expected.size());

    for(int i{0}; i < expected.size(); ++i) {
        ASSERT_EQ(middle_values[i], expected[i]);
    }
}

TEST(TestAOC, TestDay5pt1) {
    spdlog::set_level(spdlog::level::debug);
    const std::filesystem::path input_file = std::filesystem::path(ADVENT_OF_CODE_DATA) / ".." / ".." / "solutions" / "data" / "day_5.txt";
    const std::vector<int> middle_values{process_file(input_file, '|', ',')};
    
    const int total_middle_val = std::accumulate(middle_values.begin(), middle_values.end(), 0);

    ASSERT_EQ(total_middle_val, 5166);
}

TEST(TestAOC, TestDay5pt2) {
    spdlog::set_level(spdlog::level::debug);
    const std::filesystem::path input_file = std::filesystem::path(ADVENT_OF_CODE_DATA) / ".." / ".." / "solutions" / "data" / "day_5.txt";
    const std::vector<int> middle_values{process_file(input_file, '|', ',', true)};
    
    const int total_middle_val = std::accumulate(middle_values.begin(), middle_values.end(), 0);

    ASSERT_EQ(total_middle_val, 4679);
}