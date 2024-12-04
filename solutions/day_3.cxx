#include <filesystem>
#include <string>
#include "spdlog/spdlog.h"

#include "advent_of_code/day_3.hxx"

using namespace AdventOfCode24::Day3;

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
    const std::vector<int> line_totals{calculate_file_lines(input_file, false)};
    const std::vector<int> line_totals_w_logic{calculate_file_lines(input_file, true)};
    const int overall_total = std::accumulate(line_totals.begin(), line_totals.end(), 0);
    const int overall_total_w_logic = std::accumulate(line_totals_w_logic.begin(), line_totals_w_logic.end(), 0);

    spdlog::info("For file '" + input_file.string() + "' the program returned " + std::to_string(overall_total));
    spdlog::info("With logic statements enabled, this changes to " + std::to_string(overall_total_w_logic));

    return 0;
}