#include <filesystem>
#include <string>
#include "spdlog/spdlog.h"

#include "advent_of_code/day_9.hxx"

using namespace AdventOfCode24::Day9;

int main(int argc, char** argv) {
    if(argc != 2) {
        spdlog::error("Expected input data file!");
        return 1;
    }

    spdlog::set_level(spdlog::level::info);

    const std::filesystem::path input_file{argv[1]};
    if(!std::filesystem::exists(input_file)) {
        throw std::runtime_error("File " + input_file.string() + " does not exist!");
    }

    //const DiskMap cleaned_disk{cleanup_disk(input_file, false)};
    //cleaned_disk.print();
    //const long long checksum{cleaned_disk.checksum()};
    const DiskMap cleaned_disk_file_move{cleanup_disk(input_file, true)};
    const long long checksum_file_move{cleaned_disk_file_move.checksum()};

    //spdlog::info("For file '" + input_file.string() + "' the disk check sum is " + std::to_string(checksum));
    cleaned_disk_file_move.print();
    spdlog::info("For file '" + input_file.string() + "' the disk check sum using file move is " + std::to_string(checksum_file_move));
    
}