#include <fstream>
#include <memory>
#include <string>
#include <filesystem>
#include <sstream>
#include <deque>
#include <numeric>
#include <optional>
#include <exception>
#include <ranges>
#include <algorithm>

#include "spdlog/spdlog.h"

namespace AdventOfCode24::Day9 {
    typedef std::unordered_map<int, std::deque<int>> layout;
    class DiskMap {
        private:
            layout disk_map;
            const int size{-1};
            int last_block_id{-1};
            int last_block_index{-1};
            std::optional<int> get_first_empty(const int& size) const;
        public:
            DiskMap(
                const layout& disk_map,
                const int size,
                const int last_block_id,
                const int last_block_index
            ) : disk_map(disk_map), size(size), last_block_id(last_block_id), last_block_index(last_block_index) {}
            DiskMap() {};
            void print() const;
            bool block_cleanup_iteration();
            std::optional<int> file_cleanup_iteration(const int& target_block_index);
            layout getMap() const {return disk_map;}
            long long checksum() const;
    };
    DiskMap get_disk_map(const std::string& entry);
    DiskMap cleanup_disk(const std::filesystem::path& input_fil, bool file_move, bool print_iterations=false);
};