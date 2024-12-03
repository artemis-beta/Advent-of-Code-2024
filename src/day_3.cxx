#include "advent_of_code/day_3.hxx"

namespace AdventOfCode24::Day3 {
    bool use_calculation(int operation_index, logic_set logic_indexes, const bool& current_state) {
        auto last_do_before_val = std::find_if(
            logic_indexes.first.rbegin(),
            logic_indexes.first.rend(),
            [operation_index](int value){return value < operation_index;}
        );

        auto last_dont_before_val = std::find_if(
            logic_indexes.second.rbegin(),
            logic_indexes.second.rend(),
            [operation_index](int value){return value < operation_index;}
        );

        // If we have not yet encountered any logic statements leave as existing
        if(last_do_before_val == logic_indexes.first.rend() && last_dont_before_val == logic_indexes.second.rend()) return current_state;

        return (*last_do_before_val) > (*last_dont_before_val);
    }
    logic_set get_logic_indexes(const std::string& line) {
        const std::regex find_dos("do\\(\\)");
        const std::regex find_donts("don't\\(\\)");

        logic_set logic_indexes;

        auto dos_begin{std::sregex_iterator(line.begin(), line.end(), find_dos)};
        auto dos_end {std::sregex_iterator()};
        auto donts_begin{std::sregex_iterator(line.begin(), line.end(), find_donts)};
        auto donts_end {std::sregex_iterator()};

        for(std::sregex_iterator iter{dos_begin}; iter != dos_end; ++iter) {
            const std::smatch do_match{*iter};
            const size_t index = std::distance(line.begin(), line.begin() + do_match.position());
            logic_indexes.first.push_back(static_cast<int>(index));
        }

        for(std::sregex_iterator iter{donts_begin}; iter != donts_end; ++iter) {
            const std::smatch dont_match{*iter};
            const size_t index = std::distance(line.begin(), line.begin() + dont_match.position());
            logic_indexes.second.push_back(static_cast<int>(index));
        }

        return logic_indexes;
    }

    std::vector<std::pair<int, int>> parse_line(const std::string& line, bool logic_enabled, bool& do_state) {
        std::vector<std::pair<int, int>> operations;

        const std::regex find_valid_mul_statements{"mul\\(-?\\d+,-?\\d+\\)"};
        const std::regex find_numbers{"-?\\d+"};

        auto results_begin{std::sregex_iterator(line.begin(), line.end(), find_valid_mul_statements)};
        auto results_end {std::sregex_iterator()};

        std::optional<std::pair<std::vector<int>, std::vector<int>>> logic_indexes = {};
        
        if(logic_enabled) logic_indexes = get_logic_indexes(line);

        for(std::sregex_iterator iter{results_begin}; iter != results_end; ++iter) {
            const std::smatch match{*iter};
            const std::string match_str{match.str()};
            bool calculation_active{true};

            auto numbers_begin{std::sregex_iterator(match_str.begin(), match_str.end(), find_numbers)};
            auto numbers_end {std::sregex_iterator()};

            std::pair<int, int> arguments{-1000, -1000};
            const size_t match_position = std::distance(line.begin(), line.begin() + match.position());

            for(std::sregex_iterator n_iter{numbers_begin}; n_iter != numbers_end; ++n_iter) {
                const std::smatch n_match{*n_iter};
                int n_match_int{0};

                try {
                    n_match_int = std::stoi(n_match.str());
                } catch(std::invalid_argument& e) {
                    spdlog::error("Could not parse " + n_match.str());
                    return operations;
                }

                if(arguments.first == -1000) arguments.first = n_match_int;
                else arguments.second = n_match_int;
            }

            bool state_result{do_state};
            
            if(logic_enabled) state_result = use_calculation(match_position, logic_indexes.value(), do_state);

            if(!logic_enabled || state_result) operations.push_back(arguments);

            // Update global state with latest state result
            do_state = state_result;
        }
        return operations;
    }

    std::vector<int> calculate_file_lines(const std::filesystem::path& input_file, bool logic_enabled) {
        std::vector<int> calculation_results;

        std::ifstream read_in(input_file, std::ios::in);
        std::string line;
        bool do_state{true};

        while (std::getline(read_in, line)) {
            const std::vector<std::pair<int, int>> line_calculations{parse_line(line, logic_enabled, do_state)};

            const int line_total = std::accumulate(
                line_calculations.begin(), 
                line_calculations.end(), 
                0, 
                [](int total, std::pair<int, int> couplet){
                    spdlog::debug("\t" + std::to_string(couplet.first) + " * " + std::to_string(couplet.second));
                    return total + (couplet.first * couplet.second);
                }
            );
            calculation_results.push_back(line_total);
        }

        return calculation_results;
    }
};