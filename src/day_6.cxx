#include "advent_of_code/day_6.hxx"

namespace AdventOfCode24::Day6 {
	std::pair<status, std::vector<coord>> get_area_map(const std::filesystem::path& input_file) {
	
        	std::ifstream read_in(input_file, std::ios::in);
        	std::string line;
		std::vector<coord> area_map;
		status guard_init{{-1,-1},{0,0}};
		const char guard_symbols[4]{'v','>','<','^'};


        	while (std::getline(read_in, line)) {
			char symbol{'@'};
			std::istringstream iss;
			iss.str(line);
			int column{0}

			while(iss >> symbol) {
				if(symbol == '#') {
					area_map.push_back({area_map.size(), column});
					column++;
					continue;
				}
				auto find_guard = std::find(std::begin(guard_symbols), std::end(guard_symbols), symbol);
			}
	}
};
