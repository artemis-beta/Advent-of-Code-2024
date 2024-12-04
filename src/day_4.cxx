#include "advent_of_code/day_4.hxx"
#include <string>

namespace AdventOfCode24::Day4 {
	int x_matches(const std::string &word, const std::deque<std::string> &block, const int block_index) {
		if(block.empty() || block.size() < 3) return 0;
		if(word.size() != 3) {
			throw std::invalid_argument("Word must be of length 3");
		}

		int counter{0};
		
		spdlog::info("Processing block " + std::to_string(block_index));
		std::vector<std::string> print(3, std::string(block[0].size(), '.'));

		for(int column{0}; column < block[0].size() - 2; ++column) {
			if(block[0][column] != block[0][column + 2] && block[0][column] != block[2][column]) continue;
			if(block[0][column] == block[2][column + 2] || block[2][column] == block[0][column + 2]) continue;
			if(block[1][column + 1] != word[1]) continue;
			if(block[0][column] != word[0] && block[0][column] != word[2]) continue;
			if(block[2][column] != word[0] && block[2][column] != word[2]) continue;
			if(block[2][column + 2] != word[0] && block[2][column + 2] != word[2]) continue;
			if(block[0][column + 2] != word[0] && block[0][column + 2] != word[2]) continue;
			print[0][column] = block[0][column];
			print[2][column] = block[2][column];
			print[0][column + 2] = block[0][column + 2];
			print[2][column + 2] = block[2][column + 2];
			print[1][column+1] = block[1][column+1];
			counter++;
		}

		spdlog::info("Found " + std::to_string(counter) + " matches.");

		for(auto& row : print) {
			spdlog::debug(row);
		}

		return counter;
	}

	int wordsearch_matches(const std::string& word, const std::deque<std::string>& block, const int row_index) {
		if(block.empty() || word.empty()) return 0;
		int counter{0};

		for(int column{0}; column < block[0].size(); ++column) {
			// Only perform the diagonal and vertical checks on full blocks
			if(block[0][column] == word[0] && block.size() == word.size()) {
				bool diag_rdown{true}, diag_ldown{true}, down{true};
				std::vector<std::string> print_diag_rdown(block.size(), std::string(block[0].size(), '.'));
				std::vector<std::string> print_diag_ldown(block.size(), std::string(block[0].size(), '.'));
				std::vector<std::string> print_down(block.size(), std::string(block[0].size(), '.'));

				for(int row{0}; row < word.size(); ++row) {
					if(block[row][column] != word[row]) {
						down = false;
					} else {
						print_down[row][column] = word[row];
					}
					if(column - row >= 0) {
						if(block[row][column - row] != word[row]) {
							diag_ldown = false;
						} else {
							print_diag_ldown[row][column - row] = word[row];
						}
					} else {
						diag_ldown = false;
					}
					if(column + row < block[0].size()) {
						if(block[row][column + row] != word[row]) {
							diag_rdown = false;
						} else {
							print_diag_rdown[row][column + row] = word[row];
						}
					} else {
						diag_rdown = false;
					}
				}
				counter += static_cast<int>(diag_rdown) + static_cast<int>(diag_ldown) + static_cast<int>(down);

				if(diag_rdown) {
					spdlog::debug("Found right-diagonal-down match at " + std::to_string(row_index) + "," + std::to_string(column));
					for(auto& row : print_diag_rdown) {
						spdlog::debug(row);
					}
				}
				if(diag_ldown) {
					spdlog::debug("Found left-diagonal-down match at " + std::to_string(row_index) + "," + std::to_string(column));
					for(auto& row : print_diag_ldown) {
						spdlog::debug(row);
					}
				}
				if(down) {
					spdlog::debug("Found down match at " + std::to_string(row_index) + "," + std::to_string(column));
					for(auto& row : print_down) {
						spdlog::debug(row);
					}
				}
			}
			// Only perform the diagonal and vertical checks on full blocks
			if(block[block.size()-1][column] == word[0] && block.size() == word.size()) {
				bool diag_rup{true}, diag_lup{true}, up{true};
				std::vector<std::string> print_diag_rup(block.size(), std::string(block[0].size(), '.'));
				std::vector<std::string> print_diag_lup(block.size(), std::string(block[0].size(), '.'));
				std::vector<std::string> print_up(block.size(), std::string(block[0].size(), '.'));

				for(int row{0}; row < word.size(); ++row) {
					if(block[block.size() - 1 - row][column] != word[row]) {
						up = false;
					} else {
						print_up[block.size() - 1 - row][column] = word[row];
					}
					if(column - row >= 0) {
						if(block[block.size()-1-row][column - row] != word[row]) {
							diag_lup = false;
						} else {
							print_diag_lup[block.size()-1-row][column - row] = word[row];
						}
					} else {
						diag_lup = false;
					}
					if(column + row < block[0].size()) {
						if(block[block.size()-1-row][column + row] != word[row]) {
							diag_rup = false;
						} else {
							print_diag_rup[block.size()-1-row][column + row] = word[row];
						}
					} else {
						diag_rup = false;
					}
				}
				counter += static_cast<int>(diag_rup) + static_cast<int>(diag_lup) + static_cast<int>(up);

				if(diag_rup) {
					spdlog::debug("Found right-diagonal-up match at "  + std::to_string(block.size()-1 + row_index) + "," + std::to_string(column));
					for(auto& row : print_diag_rup) {
						spdlog::debug(row);
					}
				}
				if(diag_lup) {
					spdlog::debug("Found left-diagonal-up match at " + std::to_string(block.size()-1 + row_index) + "," + std::to_string(column));

					for(auto& row : print_diag_lup) {
						spdlog::debug(row);
					}
				}
				if(up) {
					spdlog::debug("Found up match at " + std::to_string(block.size()-1 + row_index) + "," + std::to_string(column));

					for(auto& row : print_up) {
						spdlog::debug(row);
					}
				}
			}

			if(block[0][column] == word[0]) {
				bool horizontal{true};
				std::vector<std::string> print_hor(block.size(), std::string(block[0].size(), '.'));
				for(int word_i{0}; word_i < word.size(); ++word_i) {
					if(block[0][column + word_i] != word[word_i]) {
						horizontal = false;
						break;
					}
					print_hor[0][column + word_i] = word[word_i];
				}
				if(horizontal) {
					spdlog::debug("Found forward match at " + std::to_string(row_index) + "," + std::to_string(column));
					for(auto& row : print_hor) {
						spdlog::debug(row);
					}
					counter++;
				}
			}

			if(block[0][block[0].size() - 1 - column] == word[0]) {
				bool rhorizontal{true};
				std::vector<std::string> print_rhor(block.size(), std::string(block[0].size(), '.'));
				for(int word_i{0}; word_i < word.size(); ++word_i) {
					if(block[0][block[0].size() - 1 - column - word_i] != word[word_i]) {
						rhorizontal = false;
						break;
					}
					print_rhor[0][block[0].size() - 1 - column - word_i] = word[word_i];
				}
				if(rhorizontal) {
					spdlog::debug("Found reverse match at " + std::to_string(row_index) + "," + std::to_string(block[0].size() - 1 - column));
					for(auto& row : print_rhor) {
						spdlog::debug(row);
					}
					counter++;
				}
			}
		}

		return counter;
	}

	int count_matches_in_file(const std::filesystem::path& input_file, const std::string& word, bool wordsearch) {
		std::deque<std::string> lines;

        std::ifstream read_in(input_file, std::ios::in);
        std::string line;
		int line_counter{0};
		int instance_counter{0};

        while (std::getline(read_in, line)) {
			lines.push_back(line);
			
			if(lines.size() < word.size()) continue;
			if(lines.size() > word.size()) lines.pop_front();

			if(wordsearch) {
				instance_counter += wordsearch_matches(word, lines, line_counter);
			} else {
				instance_counter += x_matches(word, lines, line_counter);
			}
			line_counter++;
		}

		lines.pop_front();

		// Want to continue checking horizontals
		while(!lines.empty()) {
			instance_counter += (wordsearch) ? wordsearch_matches(word, lines, line_counter) : x_matches(word, lines, line_counter);
			line_counter++;
			lines.pop_front();
		}

		return instance_counter;
	}
};
