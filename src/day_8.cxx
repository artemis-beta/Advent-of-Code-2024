#include "advent_of_code/day_8.hxx"
#include "spdlog/spdlog.h"
#include <string>
#include <numeric>

namespace AdventOfCode24::Day8 {
    coord smallest_vector(const coord& coordinate) {
        const coord abs_coord{std::abs(coordinate.first), std::abs(coordinate.second)};
        const coord dir_vec{(coordinate.first < 0) ? -1 : 1, (coordinate.second < 0) ? -1 : 1};

        const int greatest_common_denominator{std::gcd(coordinate.first, coordinate.second)};

        return {coordinate.first / greatest_common_denominator, coordinate.second / greatest_common_denominator};
    }
    Map get_communication_network(const std::filesystem::path& input_file) {
        std::ifstream read_in(input_file, std::ios::in);
		std::string line;
        Map communication_network;
        int n_lines{0};

        while (std::getline(read_in, line)) {
            if(line.empty()) continue;

            int n_columns{0};
            std::istringstream isstr;
            isstr.str(line);
            char element{'_'};

            while (isstr >> element) {
                n_columns++;
                if(element == '.') {
                    spdlog::debug("Skipping '" + std::to_string(n_lines) + "," + std::to_string(n_columns) + "' to " + element);
                    continue;
                }
                spdlog::info("Adding '" + std::to_string(n_lines) + "," + std::to_string(n_columns) + "' to " + element);
                communication_network.antennae.emplace(element, std::unordered_set<coord>{});
                communication_network.antennae[element].insert({n_lines, n_columns-1});
            }
            communication_network.size.second = n_columns;
            n_lines++;
        }

        communication_network.size.first = n_lines;

        return communication_network;
    }

    void calculate_antinode_positions(Map& communication_network, bool resonant_harmonics) {
        std::vector<std::pair<coord, coord>> processed;
        for(const auto& antenna_freq : communication_network.antennae) {
            for(const coord& pos_1 : antenna_freq.second) {
                for(const coord& pos_2 : antenna_freq.second) {
                    if(pos_1.first == pos_2.first && pos_1.second == pos_2.second) continue;
                    const std::pair<coord, coord> coord_pair{pos_1, pos_2};
                    
                    // See if the coordinate pair has already been processed
                    auto find_pair = std::find(processed.begin(), processed.end(), coord_pair);

                    if(find_pair != processed.end()) {
                        spdlog::debug(
                            "Skipping antenna-pair for '" + std::string(1, antenna_freq.first) + "': " +
                            std::to_string(pos_1.first) + "," + std::to_string(pos_1.second) + " and " +
                            std::to_string(pos_2.first) + "," + std::to_string(pos_2.second)
                        );
                        continue;
                    }
                    
                    spdlog::debug(
                        "Checking antenna-pair for '" + std::string(1, antenna_freq.first) + "': " +
                        std::to_string(pos_1.first) + "," + std::to_string(pos_1.second) + " and " +
                        std::to_string(pos_2.first) + "," + std::to_string(pos_2.second)
                    );
                    
                    processed.push_back(coord_pair);
                    processed.push_back({pos_2, pos_1});

                    coord separation{pos_2.first - pos_1.first, pos_2.second - pos_1.second};
                    coord rev_separation{-separation.first, -separation.second};

                    if(resonant_harmonics) {
                        separation = smallest_vector(separation);
                        rev_separation = smallest_vector(rev_separation);
                        communication_network.antinodes.insert(pos_1);
                        communication_network.antinodes.insert(pos_2);
                    }

                    bool forward_antinode{true}, reverse_antinode{true};
                    bool first_pass{false};
                    int counter{1};

                    while(!first_pass || (resonant_harmonics && (forward_antinode || reverse_antinode))) {
                        const coord candidate_1{
                            pos_2.first + counter * separation.first,
                            pos_2.second + counter * separation.second
                        };
                        const coord candidate_2{
                            pos_1.first + counter * rev_separation.first,
                            pos_1.second + counter * rev_separation.second
                        };

                        if(
                            candidate_1.first < communication_network.size.first &&
                            candidate_1.first >= 0 &&
                            candidate_1.second < communication_network.size.second &&
                            candidate_1.second >= 0
                        ) {
                            spdlog::debug("Adding antinode at " + std::to_string(candidate_1.first) + "," + std::to_string(candidate_1.second));
                            communication_network.antinodes.insert(candidate_1);
                        } else {
                            forward_antinode = false;
                        }

                        if(
                            candidate_2.first < communication_network.size.first &&
                            candidate_2.first >= 0 &&
                            candidate_2.second < communication_network.size.second &&
                            candidate_2.second >= 0
                        ) {
                            spdlog::debug("Adding antinode at " + std::to_string(candidate_2.first) + "," + std::to_string(candidate_2.second));
                            communication_network.antinodes.insert(candidate_2);
                        } else {
                            reverse_antinode = false;
                        }

                        first_pass = true;
                        
                        counter++;
                    }
                }
            }
        }
    }

    void print_map(const Map &communication_network) {
        for(int row{0}; row < communication_network.size.first; ++row) {
            for(int column{0}; column < communication_network.size.second; ++column) {
                const coord candidate{row, column};
                
                bool antennae_found{false};

                for(const auto& antennae : communication_network.antennae) {
                    auto find_antenna = std::find(antennae.second.begin(), antennae.second.end(), candidate);

                    if(find_antenna != antennae.second.end()) {
                        std::cout << std::string(1, antennae.first);
                        antennae_found = true;
                        break;
                    }
                }

                if(antennae_found) continue;

                auto find_antinode = std::find(
                    communication_network.antinodes.begin(),
                    communication_network.antinodes.end(),
                    candidate
                );

                if(find_antinode != communication_network.antinodes.end()) {
                    std::cout << "#";
                    continue;
                }

                std::cout << ".";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};