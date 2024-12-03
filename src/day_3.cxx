#include "advent_of_code/day_3.hxx"
#include "spdlog/spdlog.h"
#include <regex>
#include <stdexcept>
#include <string>

namespace AdventOfCode24::Day3 {
    std::vector<std::pair<int, int>> parse_line(std::istringstream& line) {
        std::vector<std::pair<int, int>> operations;

        const std::string line_str{line.str()};

        const std::regex find_valid_mul_statements{"mul\\(-?\\d+,-?\\d+\\)"};
        const std::regex find_numbers{"-?\\d+"};

        auto results_begin{std::sregex_iterator(line_str.begin(), line_str.end(), find_valid_mul_statements)};
        auto results_end {std::sregex_iterator()};

        for(std::sregex_iterator iter{results_begin}; iter != results_end; ++iter) {
            const std::smatch match{*iter};
            const std::string match_str{match.str()};

            auto numbers_begin{std::sregex_iterator(match_str.begin(), match_str.end(), find_numbers)};
            auto numbers_end {std::sregex_iterator()};

            std::pair<int, int> arguments{-1000, -1000};

            for(std::sregex_iterator n_iter{numbers_begin}; n_iter != numbers_end; ++n_iter) {
                const std::smatch n_match{*n_iter};
                int n_match_int{0};

                try {
                    n_match_int = std::stoi(match.str());
                } catch(std::invalid_argument& e) {
                    spdlog::error("Could not parse " + n_match.str());
                    return operations;
                }

                if(arguments.first == -1000) arguments.first = n_match_int;
                else arguments.second = n_match_int;
            }

            operations.push_back(arguments);
        }
        return operations;
    }
};