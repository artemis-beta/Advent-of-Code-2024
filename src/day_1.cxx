#include "day_1.hxx"

using namespace AdventOfCode::Day1;

std::optional<file_data> read_data(const std::filesystem::path& input) {
  std::ifstream read_in(input, std::ios::in);
  file_data out{std::deque<int>(), std::deque<int>()};

  if(!read_in.is_open()) {
    spdlog::error("Failed to open file {}", input.c_str());
    return {};
  }

  std::string line;
  std::string element;

  while (std::getline(read_in, line)) {
    std::istringstream stream(line);

    int index{0};
    
    for (std::string line; std::getline(line, element, ' ');) {
      
      const int num_element{std::stoi(element)};

      std::deque<int>& column = (index == 0) ? out.first : out.second;

      if(column.empty() || num_element >= column.back()) {
        column.push_back(num_element);
      } else {
        column.push_front(num_element);
      }
    }

  }

  read_in.close();

  return out;
}

std::vector<int> get_differences(const std::filesystem::path& input) {
  const std::optional<file_data> input_data = read_data(input);

  if(!input_data) {
    throw std::runtime_error(std::format("Failed to read input data for '{}'", input));
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
