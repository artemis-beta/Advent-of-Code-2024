#include <filesystem>
#include <string>
#include "spdlog/spdlog.h"

#include "advent_of_code/day_2.hxx"

int main(int argc, char** argv) {
    if(argc != 2) {
        spdlog::error("Expected input data file!");
        return 1;
    }

    const std::filesystem::path input_file{argv[1]};

    const std::vector<bool> report_safety = AdventOfCode24::Day2::check_reactor_safety(input_file, false);
    const std::vector<bool> report_safety_dampened = AdventOfCode24::Day2::check_reactor_safety(input_file, true);
    const int n_safe = std::count_if(report_safety.begin(), report_safety.end(), [](bool x){return x;});
    const int n_safe_dampened = std::count_if(report_safety_dampened.begin(), report_safety_dampened.end(), [](bool x){return x;});

    spdlog::info("For file '" + input_file.string() + "' the number of safe reports is " + std::to_string(n_safe));
    spdlog::info("With dampening the number is " + std::to_string(n_safe_dampened));

    return 0;
}