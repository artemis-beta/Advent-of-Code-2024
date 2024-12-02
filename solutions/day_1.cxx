#include <filesystem>
#include <numeric>
#include <string>
#include "spdlog/spdlog.h"

#include "advent_of_code/day_1.hxx"

using namespace AdventOfCode24::Day1;

int main(int argc, char** argv) {
    if(argc != 2) {
        spdlog::error("Expected input data file!");
        return 1;
    }

    const std::filesystem::path input_file{argv[1]};
    const std::vector<int> diffs{get_differences(input_file)};
    const std::vector<int> scores{get_similarity_scores(input_file)};

    const int diff_total = std::accumulate(diffs.begin(), diffs.end(), 0);
    const int score_total = std::accumulate(scores.begin(), scores.end(), 0);

    spdlog::info("For file '" + input_file.string() + "' the difference total is " + std::to_string(diff_total));
    spdlog::info("The simularity score is: " + std::to_string(score_total));

    return 0;
}