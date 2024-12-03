#include <filesystem>
#include <string>
#include "spdlog/spdlog.h"

#include "advent_of_code/day_2.hxx"

int main(int argc, char** argv) {
    if(argc != 2) {
        spdlog::error("Expected input data file!");
        return 1;
    }

    return 0;
}