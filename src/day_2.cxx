#include "advenr_of_code/day_2.hxx"

namespace AdventOfCode24::Day2 {
    bool safe_pair(int val_1, int val_2, int direction) {
	const int interval{val_2 - val_1};
	const int abs_interval{std::abs(interval)};

        
        if(direction > 0 && val_2 - val_1 <= 0) {
	  return false;
	}
       	else if(direction < 0 && val_2 - val_1 >= 0) {
          return false;
	}
    }
    bool level_is_safe(std::istringstream line) {
       std::string element;
       int previous{-1};
       int direction{0};


       while(std::getline(line, element, ' ')) {
            if(element.empty()) continue;

	    const int number{std::stoi(element)};
	    
	    if(previous > -1) {
	        if(direction > 
       }
    }
};
