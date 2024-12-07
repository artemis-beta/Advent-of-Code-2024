#include <filesystem>
#include <iostream>
#include <numeric>
#include <string>
#include <set>
#include "spdlog/spdlog.h"

#include "advent_of_code/day_7.hxx"

using namespace AdventOfCode24::Day7;

int main(int argc, char** argv) {
    if(argc != 2) {
        spdlog::error("Expected input data file!");
        return 1;
    }

    spdlog::set_level(spdlog::level::info);

    const std::filesystem::path input_file{argv[1]};
    if(!std::filesystem::exists(input_file)) {
        throw std::runtime_error("File " + input_file.string() + " does not exist!");
    }

    const std::vector<long> calibration_results{process_file(input_file, false)};
    const std::vector<long> calibration_results_w_concat{process_file(input_file, true)};
    const long total = std::accumulate(calibration_results.begin(), calibration_results.end(), 0L);
    const long total_w_cat = std::accumulate(calibration_results_w_concat.begin(), calibration_results_w_concat.end(), 0L);

    spdlog::info("For file '" + input_file.string() + "' the total of successful calibration lines is " + std::to_string(total));
    spdlog::info("With concatenation operator '||' included, the total becomes: " + std::to_string(total_w_cat));
}