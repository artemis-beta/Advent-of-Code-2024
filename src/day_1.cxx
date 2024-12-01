#include "advent_of_code/day_1.hxx"
#include <algorithm>
#include <unordered_map>

namespace AdventOfCode::Day1 {
  std::optional<file_data> read_data(const std::filesystem::path& input) {
    std::ifstream read_in(input, std::ios::in);
    file_data out{std::vector<int>(), std::vector<int>()};

    if(!read_in.is_open()) {
      spdlog::error("Failed to open file {}", input.c_str());
      return {};
    }

    std::string line;
    std::string element;

    while (std::getline(read_in, line)) {
      std::istringstream stream(line);

      bool is_first_col{true};
      
      for (std::string element; std::getline(stream, element, ' ');) {

        if(element.empty()) continue;

        const int num_element{std::stoi(element)};

        std::vector<int>& column = is_first_col ? out.first : out.second;

        column.push_back(num_element);
        
        is_first_col = false;
      }

    }

    std::sort(out.first.begin(), out.first.end());
    std::sort(out.second.begin(), out.second.end());

    read_in.close();

    return out;
  }

  std::vector<int> get_differences(const std::filesystem::path& input) {
    const std::optional<file_data> input_data = read_data(input);

    if(!input_data) {
      throw std::runtime_error("Failed to read input data for " + input.string());
    }

    const file_data validated_data{*input_data};

    std::vector<int> differences(validated_data.first.size());

    std::transform(
        validated_data.first.begin(),
        validated_data.first.end(),
        validated_data.second.begin(),
        differences.begin(),
        [](int a, int b) {return abs(a - b);}
    );

    return differences;
  }

  std::vector<int> get_similarity_scores(const std::filesystem::path& input) {
    const std::optional<file_data> input_data = read_data(input);

    if(!input_data) {
      throw std::runtime_error("Failed to read input data for " + input.string());
    }

    const file_data validated_data{*input_data};

    std::unordered_map<int, int> scoring_map;

    std::vector<int> scores(validated_data.first.size());

    std::transform(
        validated_data.first.begin(),
        validated_data.first.end(),
        scores.begin(),
        [&scoring_map, validated_data](int a) {
          if(scoring_map.find(a) != scoring_map.end()) {
            return scoring_map.at(a);
          }
          const int n_occurrences = std::count_if(validated_data.second.begin(), validated_data.second.end(), [a](int value){return value == a;});
          scoring_map[a] = a * n_occurrences;
          return a * n_occurrences;
        }
    );

    return scores;

  }
};