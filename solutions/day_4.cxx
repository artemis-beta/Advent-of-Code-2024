#include <filesystem>
#include <string>
#include "spdlog/spdlog.h"

#include "advent_of_code/day_4.hxx"

using namespace AdventOfCode24::Day4;

int main(int argc, char** argv) {
    if(argc != 2) {
        spdlog::error("Expected input data file!");
        return 1;
    }

    spdlog::set_level(spdlog::level::debug);

    const std::filesystem::path input_file{argv[1]};
    if(!std::filesystem::exists(input_file)) {
        throw std::runtime_error("File " + input_file.string() + " does not exist!");
    }

    const int wordsearch_count{count_matches_in_file(input_file, "XMAS", true)};
    const int x_count{count_matches_in_file(input_file, "MAS", false)};

    spdlog::info("For file '" + input_file.string() + "' for wordsearch style matches, the program returned " + std::to_string(wordsearch_count));
    spdlog::info("For X-matches the count is " + std::to_string(x_count));

    return 0;
}