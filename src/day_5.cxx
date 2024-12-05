#include "advent_of_code/day_5.hxx"
#include "spdlog/spdlog.h"
#include <deque>
#include <iterator>
#include <sstream>
#include <string>
#include <unordered_map>

namespace AdventOfCode24::Day5 {
    std::optional<std::pair<int, int>> parse_rule(const std::string& order_statement, const char& delimiter) {
        auto find_delimiter = std::find(order_statement.begin(), order_statement.end(), delimiter);

        if(find_delimiter == order_statement.end()) {
            spdlog::debug("No delimiter found, line is not a rule");
            return {};
        }

        const std::string key_str(order_statement.begin(), find_delimiter);
        const std::string value_str(find_delimiter + 1, order_statement.end());

        std::pair<int, int> key_value{-1, -1};

        try {
            key_value.first = std::stoi(key_str);
        } catch (std::exception& e) {
            spdlog::error("Could not parse match '" + key_str + "'");
            return {};
        }

        try {
            key_value.second = std::stoi(value_str);
        } catch(std::exception& e) {
            spdlog::error("Could not parse match '" + value_str + "'");
            return {};
        }

        return {key_value};
    }

    bool check_sequence(const std::vector<int>& sequence, const std::unordered_map<int, std::vector<int>>& ruleset) {
        for(int i = sequence.size() - 1; i >= 0; --i) {
            auto rule_find = ruleset.find(sequence[i]);
            if(rule_find == ruleset.end()) continue;
            const std::vector<int> rule{rule_find->second};
            const std::vector<int> lhs(sequence.begin(), sequence.begin() + i);

            auto rule_fail = std::find_if(
                lhs.begin(),
                lhs.end(),
                [rule](const int& n) {
                    auto value_in_rule = std::find(rule.begin(), rule.end(), n);
                    return value_in_rule != rule.end();
                }
            );

            if(rule_fail != lhs.end()) return false;
        }
        return true;
    }

    std::vector<int> process_file(const std::filesystem::path& input_file, const char& rule_delimiter, const char& sequence_delimiter, bool count_fixed) {
        std::ifstream read_in(input_file, std::ios::in);
        std::string line;
        std::vector<int> middle_values;
		int instance_counter{0};
        int line_counter{0};
        bool processing_ruleset{true};
        std::unordered_map<int, std::vector<int>> rule_set;

        while (std::getline(read_in, line)) {
            // Ignore empty lines
            if(line.empty()) continue;

            // Parsing of rule set at start of file
            if(processing_ruleset) {
                spdlog::debug("Processing L" + std::to_string(line_counter) + ": " + line + " as rule.");
                const std::optional<std::pair<int, int>> rule_check = parse_rule(line, rule_delimiter);
                if(rule_check.has_value()) {
                    const std::pair<int, int> rule{rule_check.value()};

                    rule_set.emplace(rule.first, std::vector<int>());
                    rule_set[rule.first].push_back(rule.second);

                    line_counter++;
                    continue;
                }
                processing_ruleset = false;
                line_counter++;
            }

            spdlog::debug("Processing L" + std::to_string(line_counter) + ": " + line + " as sequence.");

            std::vector<int> sequence;
            std::string num_str;
            std::istringstream sstr{line};

            try {
                while(std::getline(sstr, num_str, sequence_delimiter)) {
                    const int number{std::stoi(num_str)};
                    sequence.push_back(number);
                }
            } catch(std::exception& e) {
                spdlog::error("Failed to parse line " + line);
                return {};
            }

            spdlog::debug("Line registered " + std::to_string(sequence.size()) + " values.");

            if(check_sequence(sequence, rule_set)){
                if(count_fixed) {
                    middle_values.push_back(0);
                } else {
                    spdlog::debug("Adding value " + std::to_string(sequence[sequence.size() / 2]) + " to middle values.");
                    middle_values.push_back(sequence[sequence.size() / 2]);
                }
            } else {
                if(count_fixed) {
                    const std::vector<int> fixed_line{order_line(sequence, rule_set)};
                    
                    std::ostringstream os;
                    
                    for(const int& val : fixed_line) {
                        os << val << ",";
                    }

                    spdlog::debug("Line has been reordered to " + os.str());                    
                    spdlog::debug("Adding fixed value " + std::to_string(fixed_line[fixed_line.size() / 2]) + " to middle values.");
                    middle_values.push_back(fixed_line[fixed_line.size() / 2]);
                } else {
                    middle_values.push_back(0);
                }
            }

            line_counter++;
        }
        return middle_values;
    }

    std::vector<int> order_line(const std::vector<int>& sequence, const std::unordered_map<int, std::vector<int>>& ruleset) {

        std::vector<int> sorted(sequence);

        std::sort(sorted.begin(), sorted.end(), [&ruleset](const int& a, const int& b) {
            // First check if there is a rule for b
            // If there is no match move it anyway so the sort re-processes it later
            if(ruleset.find(b) == ruleset.end()) return true;

            // check if a is in b's rule
            const std::vector<int> b_rule{ruleset.at(b)};
            auto find_num = std::find(b_rule.begin(), b_rule.end(), a);
            return find_num == b_rule.end();
        });

        return sorted;
    }
};