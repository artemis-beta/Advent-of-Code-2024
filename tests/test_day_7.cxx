#include <gtest/gtest.h>
#include <numeric>
#include <string>
#include "advent_of_code/day_7.hxx"
#include "spdlog/spdlog.h"

using namespace AdventOfCode24::Day7;

#ifndef ADVENT_OF_CODE_DATA
  #error "ADVENT_OF_CODE_DATA is not defined!"
#endif

TEST(TestAOC, TestDay7pt1_parse_line_pass) {
    const std::string test_line{": 10 2 5 3 4 2 5"};
    const std::vector<int> allowed{
        31,39,53,62,69,74,86,87,
        114,115,119,130,139,163,165,
        170,191,211,219,229,240,
        259,285,307,311,320,345,
        373,405,410,413,419,509,
        545,550,570,605,613,670,
        727,790,800,829,930,1030,
        1070,1120,1207,1270,1445,
        1510,1530,1840,2040,2070,
        2405,2520,3000,3040,3610,
        4120,6010,7200,12000
    };

    for(const int& value : allowed) {
        const int64_t result{check_calibration_line(std::to_string(value) + test_line, false)};
        ASSERT_EQ(result, value);
    }
}

TEST(TestAOC, TestDay7pt1_parse_line_fail) {
    const std::string test_line{"10: 2 2 5"};
    const int64_t result{check_calibration_line(test_line, false)};
    ASSERT_EQ(result, 0);
}

TEST(TestAOC, TestDay7pt1_example) {
    const std::filesystem::path input_file = std::filesystem::path(ADVENT_OF_CODE_DATA) / "day_7_1.txt";

    const std::vector<int64_t> calibration_results{process_file(input_file, false)};
    const std::vector<int64_t> expected_results{true, true, false, false, false, false, false, false, true};

    ASSERT_EQ(expected_results.size(), calibration_results.size());

    for(int i{0}; i < expected_results.size(); ++i) {
        if(expected_results[i]) {
            ASSERT_TRUE(calibration_results[i] > 0);
        } else {
            ASSERT_TRUE(calibration_results[i] == 0);
        }
    }

    const int total = std::accumulate(calibration_results.begin(), calibration_results.end(), 0);

    ASSERT_EQ(total, 3749);
}

TEST(TestAOC, TestDay7pt2_example) {
    const std::filesystem::path input_file = std::filesystem::path(ADVENT_OF_CODE_DATA) / "day_7_1.txt";

    const std::vector<int64_t> calibration_results{process_file(input_file, true)};
    const std::vector<int64_t> expected_results{true, true, false, true, true, false, true, false, true};

    ASSERT_EQ(expected_results.size(), calibration_results.size());

    for(int i{0}; i < expected_results.size(); ++i) {
        if(expected_results[i]) {
            ASSERT_TRUE(calibration_results[i] > 0);
        } else {
            ASSERT_TRUE(calibration_results[i] == 0);
        }
    }

    const int total = std::accumulate(calibration_results.begin(), calibration_results.end(), 0);

    ASSERT_EQ(total, 11387);
}
