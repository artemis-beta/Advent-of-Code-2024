#include <gtest/gtest.h>
#include <unordered_map>
#include <vector>
#include "advent_of_code/day_9.hxx"
#include "spdlog/common.h"
#include "spdlog/spdlog.h"

using namespace AdventOfCode24::Day9;

#ifndef ADVENT_OF_CODE_DATA
  #error "ADVENT_OF_CODE_DATA is not defined!"
#endif

TEST(TestAOC, TestDay9pt1_parse_line) {
    const std::string test_input{"13579"};
    const layout expected{
        {0, {0}},
        {1, {4, 5, 6, 7, 8}},
        {2, {16, 17, 18, 19, 20, 21, 22, 23, 24}},
        {-1, { 1, 2, 3, 9, 10, 11, 12, 13, 14, 15 }}
    };

    const DiskMap disk_map{get_disk_map(test_input)};

    disk_map.print();

    ASSERT_EQ(expected, disk_map.getMap());
}

TEST(TestAOC, TestDay9pt1_clean_iter) {
    const std::string test_input{"13579"};
    const layout expected{
        {0, {0}},
        {1, {4, 5, 6, 7, 8}},
        {2, {16, 17, 18, 19, 20, 21, 22, 23, 1}},
        {-1, { 2, 3, 9, 10, 11, 12, 13, 14, 15, 24 }}
    };

    DiskMap disk_map{get_disk_map(test_input)};
    disk_map.block_cleanup_iteration();

    disk_map.print();

    ASSERT_EQ(expected, disk_map.getMap());
}

TEST(TestAOC, TestDay9pt1_example_1) {
    const std::filesystem::path input_file = std::filesystem::path(ADVENT_OF_CODE_DATA) / "day_9_1.txt";
    const DiskMap cleaned_disk{cleanup_disk(input_file, true)};

    const layout expected{
        {0, {0}},
        {1, {3, 4, 5}},
        {2, {8, 7, 6, 2, 1}},
        {-1, { 9, 14, 13, 12, 11, 10 }}
    };

    ASSERT_EQ(expected, cleaned_disk.getMap());
}

TEST(TestAOC, TestDay9pt1_example_2) {
    const std::filesystem::path input_file = std::filesystem::path(ADVENT_OF_CODE_DATA) / "day_9_2.txt";
    const DiskMap cleaned_disk{cleanup_disk(input_file, false)};
    const long long checksum{cleaned_disk.checksum()};

    ASSERT_EQ(checksum, 1928);
}

TEST(TestAOC, TestDay9pt2_example_2) {
    spdlog::set_level(spdlog::level::debug);
    const std::filesystem::path input_file = std::filesystem::path(ADVENT_OF_CODE_DATA) / "day_9_2.txt";
    const DiskMap cleaned_disk{cleanup_disk(input_file, true)};
    const long long checksum{cleaned_disk.checksum()};

    cleaned_disk.print();

    ASSERT_EQ(checksum, 2858);
}