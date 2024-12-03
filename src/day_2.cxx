#include "advent_of_code/day_2.hxx"


namespace AdventOfCode24::Day2 {
    std::vector<int> read_line(std::istringstream& line) {
        std::vector<int> line_vals;
        int number{-1000};

        while(line >> number) {
            line_vals.push_back(number);
        }
        return line_vals;
    }

    std::vector<int> level_trend(const std::vector<int>& values) {
        std::vector<int> trend(values.size() - 1, -1000);

        std::transform(
            values.begin(),
            values.end() - 1,
            values.begin() + 1,
            trend.begin(),
            [](int lower, int upper){
                return upper - lower;
            }
        );

        return trend;
    }

    auto check_numbers(const std::vector<int>& values, const int& overall_trend) {
        return std::adjacent_find(
            values.begin(),
            values.end(),
            [&overall_trend](int a, int b) {
                if(a == b || std::abs(a - b) > 3 || std::abs(a - b) < 1){
                    spdlog::warn("Invalid interval of size " + std::to_string(a - b));
                    return true;
                }
                if((overall_trend > 0 && a > b) || (overall_trend < 0 && a < b)) {
                    spdlog::warn("Interval of [" + std::to_string(a) + "," + std::to_string(b) + "] does not match " + ((overall_trend < 0) ? "negative" : "positive") + " trend");
                    return true;
                }
                return false;
            }
        );

    }

    bool level_trend_is_valid(const std::vector<int>& values, bool problem_dampening) {
        std::vector<int> trend{level_trend(values)};

        // Determines if numbers are ascending or descending
        const int general_trend = std::accumulate(
            trend.begin(),
            trend.end(),
            0,
            [](int prev, int val){
                if(val > 0) return prev + 1;
                if(val < 0) return prev - 1;
                return prev;
            }
        );

        // If the general trend is zero this is failure
        if(!general_trend) {
            spdlog::warn("No general direction found.");
            return false;
        }

        auto invalid_number_iter{check_numbers(values, general_trend)};

        // If no results then line is valid
        if(invalid_number_iter == values.end()) return true;
        if(!problem_dampening) return false;

        std::vector<int> test_erase_current(values);
        std::vector<int> test_erase_next(values);

        const int index = std::distance(values.begin(), invalid_number_iter);

        if(index < test_erase_current.size()) {
            test_erase_current.erase(test_erase_current.begin() + index);
            const bool current_pass{check_numbers(test_erase_current, general_trend) == test_erase_current.end()};
            if(current_pass) return true;
        }

        if(index + 1 < test_erase_next.size()) {
            test_erase_next.erase(test_erase_next.begin() + index + 1);
            const bool next_pass{check_numbers(test_erase_next, general_trend) == test_erase_next.end()};
            if(next_pass) return true;
        }

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
            const std::vector<int> values{read_line(stream)};

            const bool report_status{level_trend_is_valid(values, problem_dampening)};
            safe_reports.push_back(report_status);
            spdlog::debug("Line " + std::string((safe_reports[safe_reports.size() - 1]) ? "Passed" : "Failed"));
        }

        spdlog::info("Processed " + std::to_string(safe_reports.size()) + " layers.");

        return safe_reports;
    }

};
