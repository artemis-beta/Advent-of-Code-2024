#include "advent_of_code/day_7.hxx"
#include "spdlog/spdlog.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>

namespace AdventOfCode24::Day7 {
    int64_t check_calibration_line(const std::string& line, bool include_concatenator, const char& delimiter) {
        auto divider_find = std::find(line.begin(), line.end(), delimiter);
        
        if(divider_find == line.end()) {
            throw std::runtime_error("Line did not match expected format, could not find delimiter '" + std::string(1, delimiter) + "'");
        }

        const std::string target_str(line.begin(), divider_find);
        const std::string operands(divider_find + 1, line.end());

        if(target_str.empty()) {
            throw std::runtime_error("Target string is empty for line: " + line);
        }

        int64_t target{-1};

        try {
            target = std::stol(target_str);
        } catch(std::exception& e) {
            throw std::runtime_error("Could not convert '" + target_str + "' to int64_t integer.");
        }

        if(target < 0) {
            throw std::runtime_error(target_str + " exceeds limit of int64_t integer.");
        }

        std::istringstream iss;
        iss.str(operands);
        int64_t number{-1};
        int n_numbers{0};
        std::vector<int64_t> operations{0};

        while(iss >> number) {
            std::vector<int64_t> results;

            n_numbers++;

            for(const int64_t& n : operations) {
                const int64_t multiply{((n==0) ? 1 : n) * number};
                const int64_t add{n + number};

                if(multiply < 0) {
                    throw std::runtime_error(std::to_string(multiply) + " exceeds limit of int64_t integer.");
                }

                if(add < 0) {
                    throw std::runtime_error(std::to_string(add) + " exceeds limit of int64_t integer.");
                }

                if(multiply <= target) results.push_back(multiply);
                if(add <= target) results.push_back(add);

                if(include_concatenator) {
                    const std::string concatenate_str{std::to_string(n) + std::to_string(number)};
                    const int64_t concatenate{std::stol(concatenate_str)};
                    if(concatenate <= target) results.push_back(concatenate);
                }
            }
            
            operations = results;

            if(results.empty()) {
                spdlog::warn("Line failed, operation results exceeded at number " + std::to_string(number));
                return 0;
            }
        }

        auto find_target = std::find(operations.begin(), operations.end(), target);

        if(find_target != operations.end()) {
            spdlog::info("Line '" + line + "' returned target after all numbers read.");
            return target;
        }

        auto max_loc = std::max_element(operations.begin(), operations.end());

        if(max_loc == operations.end()) {
            spdlog::warn("Line failed, operation result below target value after processing.");
        } else {
            const int64_t max_reached{*max_loc};
            spdlog::warn("Line failed, operation result below target value after processing " + std::to_string(n_numbers) + ": " + std::to_string(max_reached) + " < " + std::to_string(target));
        }
        return 0;
    }

    std::vector<int64_t> process_file(const std::filesystem::path& input_file, bool include_concatenator) {
        std::ifstream read_in(input_file, std::ios::in);
		std::string line;
        std::vector<int64_t> calibration_results;
        int n_lines{0};

        while (std::getline(read_in, line)) {
            if(line.empty()) continue;

            const int64_t calibration{check_calibration_line(line, include_concatenator)};

            if(calibration < 0) {
                throw std::runtime_error("Tried to append negative value " + std::to_string(calibration) + " to total!");
            }

            calibration_results.push_back(calibration);

            n_lines++;
        }
        spdlog::info("Processed " + std::to_string(n_lines) + " lines.");

        return calibration_results;
    }
};