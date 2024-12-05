#include <filesystem>
#include <numeric>
#include <string>
#include "spdlog/spdlog.h"

#include "advent_of_code/day_5.hxx"

using namespace AdventOfCode24::Day5;

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

    const std::vector<int> middle_values{process_file(input_file, '|', ',')};
    const std::vector<int> middle_fixed_values{process_file(input_file, '|', ',', true)};

    const int middle_total = std::accumulate(middle_values.begin(), middle_values.end(), 0);
    const int middle_fixed_total = std::accumulate(middle_fixed_values.begin(), middle_fixed_values.end(), 0);

    spdlog::info("For file '" + input_file.string() + "' summating the middle values of lines which pass the ruleset gives " + std::to_string(middle_total));
    spdlog::info("Counting only middle values of reordered values gives a total of " + std::to_string(middle_fixed_total));

    return 0;
}