#include "advent_of_code/day_2.hxx"

namespace AdventOfCode24::Day2 {
    bool safe_pair(int val_1, int val_2, int direction) {
        const int interval{val_2 - val_1};
        const int abs_interval{std::abs(interval)};

        if(abs_interval > 3 || abs_interval < 1) return false;

        if(direction > 0 && val_2 - val_1 <= 0) {
	        return false;
	    }
        else if(direction < 0 && val_2 - val_1 >= 0) {
             return false;
	    }

        return true;
    }
    bool level_is_safe(std::istringstream& line) {
        std::string element;
        int previous{-1};
        int direction{0};


        while(std::getline(line, element, ' ')) {
            if(element.empty()) continue;

	        const int number{std::stoi(element)};

            if(previous > 0) {
                if(!safe_pair(previous, number, direction)) return false;
                if(direction == 0) direction = number - previous;
            }
            previous = number;
        }

        return true;
    }

    bool check_reactor_safety(const std::filesystem::path& input_file) {
        // Attempt to read file, if the read fails return null object
        std::ifstream read_in(input_file, std::ios::in);
    }
};
