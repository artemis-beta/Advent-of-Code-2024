#include "advent_of_code/day_2.hxx"
#include "spdlog/spdlog.h"
#include <string>

namespace AdventOfCode24::Day2 {
    bool safe_pair(int val_1, int val_2, int direction) {
        if(val_1 < 0) return true;

        const int interval{val_2 - val_1};
        const int abs_interval{std::abs(interval)};

        if(abs_interval > 3 || abs_interval < 1) {
            spdlog::debug("\t- Value " + std::to_string(val_2) + " failed due to interval " + std::to_string(abs_interval));
            return false;
        }

        if(direction > 0 && interval <= 0) {
            spdlog::debug("\t- Value " + std::to_string(val_2) + " failed due to interval " + std::to_string(interval) + " in positive flow");
	        return false;
	    }
        else if(direction < 0 && interval >= 0) {
            spdlog::debug("\t- Value " + std::to_string(val_2) + " failed due to interval " + std::to_string(interval) + " in negative flow");
            return false;
	    }

        return true;
    }

    int check_intervals(const std::vector<int>& numbers) {
        std::vector<int> directions(numbers.size() - 1);

        std::transform(
            numbers.begin(),
            numbers.end() - 1,
            numbers.begin() + 1,
            directions.begin(),
            [](int a, int b) {
                if(b > a) return 1;
                if(b == a) return 0;
                return -1;
            }
        );

        const int overall_dir = std::accumulate(directions.begin(), directions.end(), 0);

        spdlog::debug("\t- Overall direction is " + std::string((overall_dir < 0) ? "Negative" : "Positive"));

        if(!overall_dir) {
            spdlog::debug("\t- All intervals failed with value 0");
            return overall_dir;
        }

        const int differences = std::count_if(
            directions.begin(), 
            directions.end(), 
            [&overall_dir](int x){
                const bool x_forward{x < 0};
                const bool overall_dir_forward{overall_dir < 0};
                if(x_forward != overall_dir_forward) {
                    spdlog::debug("\t- Mismatch in direction between interval " + std::to_string(x) + " and direction " + std::to_string(overall_dir_forward));
                }
                return x_forward != overall_dir_forward;
            }
        );

        if(differences > 0) {
            spdlog::debug("\t- Intervals failed due to variance in direction.");
            return 0;
        }

        return overall_dir;
    }

    std::optional<int> check_report_values(const std::vector<int>& numbers, int direction) {        
        for(int i{0}; i < numbers.size() - 1; ++i) {
            if(!safe_pair(numbers[i], numbers[i+1], direction)) {
                return i + 1;
            }
        }

        return {};
    }

    bool report_is_safe(std::istringstream& line, bool allow_dampening) {
        std::vector<int> numbers;

        int number;

        while (line >> number) {
            numbers.push_back(number);
        }

        int interval_check{check_intervals(numbers)};

        if(!interval_check && !allow_dampening) return false;

        const std::optional<int> fail_index{check_report_values(numbers, interval_check)};

        if(!fail_index.has_value()) return true;
        if(!allow_dampening) return false;

        std::vector<int> dampened_first{numbers.begin(), numbers.end()};
        dampened_first.erase(dampened_first.begin() + fail_index.value() - 1);
        interval_check = check_intervals(dampened_first);

        const std::optional<int> damp_fail_index_first{check_report_values(dampened_first, interval_check)};
        if(!damp_fail_index_first.has_value()) return true;

        std::vector<int> dampened_second{numbers.begin(), numbers.end()};
        dampened_second.erase(dampened_second.begin() + fail_index.value());
        interval_check = check_intervals(dampened_second);

        const std::optional<int> damp_fail_index_second{check_report_values(dampened_second, interval_check)};
        if(!damp_fail_index_second.has_value()) return true;

        return false;
    }

    std::vector<bool> check_reactor_safety(const std::filesystem::path& input_file, bool problem_dampening) {
        spdlog::info("Problem Damping is " + ((problem_dampening) ? std::string("Enabled") : std::string("Disabled")));
        std::vector<bool> safe_reports;

        std::ifstream read_in(input_file, std::ios::in);
        std::string line;

        while (std::getline(read_in, line)) {
            spdlog::debug("Processing line " + std::to_string(safe_reports.size()));
            std::istringstream stream(line, std::ios::in);
            const bool report_status{report_is_safe(stream, problem_dampening)};
            safe_reports.push_back(report_status);
            spdlog::debug("Line " + std::string((safe_reports[safe_reports.size() - 1]) ? "Passed" : "Failed"));
        }

        spdlog::info("Processed " + std::to_string(safe_reports.size()) + " layers.");

        return safe_reports;
    }
};
