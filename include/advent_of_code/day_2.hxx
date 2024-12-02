#pragma once

#include <sstream>
#include <cstdlib>
#include <string>
#include <filesystem>
#include <fstream>

namespace AdventOfCode24::Day2 {
    const int BUFFER_SIZE{1024};
    bool is_safe(std::istringstream& line);
    bool check_reactor_safety(const std::filesystem::path& input_file);
};
