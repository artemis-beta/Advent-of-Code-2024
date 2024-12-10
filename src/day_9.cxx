#include "advent_of_code/day_9.hxx"
#include "spdlog/spdlog.h"
#include <algorithm>
#include <deque>
#include <exception>
#include <iostream>
#include <memory>
#include <numeric>
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace AdventOfCode24::Day9 {
    DiskMap get_disk_map(const std::string& entry) {
        if(entry.empty()) {
            throw std::runtime_error("Cannot process empty string.");
        }
        std::istringstream isstr;
        isstr.str(entry);
        int number{-1};
        int line_pos{0};
        int block_index{0};
        int index{0};
        layout disk_map;

        for (const char& number_str : entry) {
            try {
                number = std::stoi(std::string(1, number_str));
            } catch(std::exception& e) {
                throw std::runtime_error("Could not convert value " + std::string(1, number_str));
            }

            if(line_pos % 2 == 1) {
                disk_map.emplace(-1, std::deque<int>());
                for(int n{0}; n < number; ++n) {
                    disk_map.at(-1).push_back(index);
                    index++;
                }
            } else {
                disk_map.emplace(block_index, std::deque<int>());
                for(int i{0}; i < number; ++i) {
                    disk_map.at(block_index).push_back(index);
                    index++;
                }
                block_index++;
            }

            line_pos++;
        }

        const int last_block_index{static_cast<int>(disk_map.at(block_index - 1).size()) - 1};

        return DiskMap(disk_map, index, block_index - 1, last_block_index);
    }

    void DiskMap::print() const{
        std::vector<std::string> output_vec(size, "X");

        for(const auto& map_entry : disk_map) {
            for(const int& pos : map_entry.second) {
                if(pos >= size) {
                    throw std::runtime_error(
                        "Cannot print map, recorded position " + std::to_string(pos) +
                        " is not within specified map size " + std::to_string(size));
                }
                output_vec[pos] = ((map_entry.first == -1) ? "." : std::to_string(map_entry.first));
            }
        }

        for(const std::string& output : output_vec) {
            std::cout << output;
        }

        std::cout << std::endl;
    }

    bool DiskMap::block_cleanup_iteration() {
        layout disk_layout{disk_map};

        if(disk_layout.at(-1).empty()) return {};

        const int first_empty = disk_layout.at(-1)[0];
        const int current_pos = disk_layout.at(last_block_id)[last_block_index];

        if(current_pos < first_empty) return false;
        
        disk_layout.at(last_block_id)[last_block_index] = first_empty;
        disk_layout.at(-1).pop_front();
        disk_layout.at(-1).push_back(current_pos);

        int new_last_block{-1};
        int new_last_index{-1};

        if(last_block_index < 1) {
            new_last_block = last_block_id - 1;
            if(new_last_block < 0) return false;
            new_last_index = disk_layout.at(new_last_block).size() - 1;
        } else {
            new_last_block = last_block_id;
            new_last_index = last_block_index - 1;
        }
        
        last_block_index = new_last_index;
        last_block_id = new_last_block;
        disk_map = disk_layout;

        return true;
    }
    
    std::optional<int> DiskMap::get_first_empty(const int& size) const {
        auto find_empties = disk_map.find(-1);
        
        if(find_empties == disk_map.end() || disk_map.at(-1).empty()) {
            return {};
        }

        for(int i{0}; i < disk_map.at(-1).size(); ++i) {
            int offset{0};
            while(disk_map.at(-1)[i + offset + 1] - disk_map.at(-1)[i + offset] == 1) {
                offset++;
            }
            if(offset + 1 >= size) return i;
        }

        return {};
    }

    std::optional<int> DiskMap::file_cleanup_iteration(const int& block_index) {
        if(block_index < 0) {
            spdlog::error("Block index < 0");
            return {};
        }
        if(disk_map.find(-1) == disk_map.end()) {
            spdlog::error("No blank space found!");
            return {};
        }

        const size_t size{disk_map.at(block_index).size()};
        std::sort(disk_map.at(-1).begin(), disk_map.at(-1).end());

        const std::optional<int> check_for_empty{get_first_empty(size)};

        if(!check_for_empty.has_value()) {
            spdlog::warn("Could not find any empty space to accomodate file " + std::to_string(block_index) + " of size " + std::to_string(size));
            return block_index - 1;
        }

        const int first_empty_index{disk_map.at(-1)[check_for_empty.value()]};

        std::deque<int> block_positions{disk_map.at(block_index)};

        if(block_positions.empty()) {
            spdlog::warn("Block " + std::to_string(block_index) + " is empty.");
            return block_index - 1;
        }

        std::sort(block_positions.begin(), block_positions.end());

        if(block_positions[0] <= first_empty_index) {
            spdlog::info("Block " + std::to_string(block_index) + " already at optimal position.");
            return block_index - 1;
        }

        disk_map.at(block_index).clear();

        for(int i{0}; i < size; ++i) {
            disk_map.at(block_index).push_back(first_empty_index + i);

            disk_map.at(-1).erase(std::remove(disk_map.at(-1).begin(), disk_map.at(-1).end(), first_empty_index + i), disk_map.at(-1).end());
        }

        for(const int& block_pos : block_positions) {
            disk_map.at(-1).push_back(block_pos);
        }

        return block_index - 1;
    }

    DiskMap cleanup_disk(const std::filesystem::path& input_file, bool file_move, bool print_iterations) {
        std::ifstream read_in(input_file, std::ios::in);
		std::string line;

        std::getline(read_in, line);

        DiskMap disk_map{get_disk_map(line)};

        if(file_move) {
            auto max_block = std::max_element(disk_map.getMap().begin(), disk_map.getMap().end(), [](const auto& a, const auto& b){return a.first < b.first;});
            if(max_block == disk_map.getMap().end()) {
                throw std::runtime_error("Failed to get maximum block index");
            }

            std::optional<int> block_index = {max_block->first};

            while(block_index.has_value()) {
                block_index = disk_map.file_cleanup_iteration(block_index.value());
                if(print_iterations) disk_map.print();
            }
        
        } else {
            while(!file_move && disk_map.block_cleanup_iteration()) {
                if(print_iterations) disk_map.print();
            }
        }

        return disk_map;
    }

    long long DiskMap::checksum() const {
        return std::accumulate(
            disk_map.begin(),
            disk_map.end(),
            0LL,
            [](const long long& total, const std::pair<int, std::deque<int>>& a) {
                // Do not include space which has index -1
                if(a.first < 0) return total;

                return total + a.first * std::accumulate(
                    a.second.begin(),
                    a.second.end(),
                    0LL
                );
            }
        );
    }
};