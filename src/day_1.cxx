#include "advent_of_code/day_1.hxx"

namespace AdventOfCode24::Day1 {
  std::optional<file_data> read_data(const std::filesystem::path& input) {

    // Attempt to read file, if the read fails return null object
    std::ifstream read_in(input, std::ios::in);
    file_data out{std::vector<int>(), std::vector<int>()};

    if(!read_in.is_open()) {
      spdlog::error("Failed to open file {}", input.c_str());
      return {};
    }

    // Read the file line by line
    std::string line;
    std::string element;

    while (std::getline(read_in, line)) {
      std::istringstream stream(line, std::ios::in);

      // Whether to assign to the first or second vector
      bool is_first_col{true};
      
      // For each line split by space to get elements
      for (std::string element; std::getline(stream, element, ' ');) {

        // If the line is empty continue
        if(element.empty()) continue;

        const int num_element{std::stoi(element)};

        // Assign to either the first or second vector
        std::vector<int>& column = is_first_col ? out.first : out.second;

        column.push_back(num_element);
        
        is_first_col = false;
      }

    }

    // Sort both vectors/historian location lists
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

    // Compare the two lists after sorting them getting the difference between
    // the two numbers
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

    // Iterate through both lists and either count the occurrences in the second list
    // for each number in the first list. At the same time record the occurences so if
    // there are any repeated values these can just be retrieved from cache
    std::transform(
        validated_data.first.begin(),
        validated_data.first.end(),
        scores.begin(),
        [&scoring_map, validated_data](int a) {
          if(scoring_map.find(a) != scoring_map.end()) {
            return scoring_map.at(a);
          }
          const int n_occurrences = std::count_if(
            validated_data.second.begin(),
            validated_data.second.end(), 
            [a](int value){return value == a;}
          );
          scoring_map[a] = a * n_occurrences;
          return a * n_occurrences;
        }
    );

    return scores;

  }
};