#include <fstream>
#include <iostream>
#include <vector>

#include "functions.hpp"
#include "utilities.hpp"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " [input_file] [dna_sequence]"
              << std::endl;
    return 1;
  }
  const std::string& file_name = argv[1];
  std::ifstream ifs{file_name};
  std::vector<std::vector<std::string>> dna_data;
  std::vector<std::string> subv;
  // dna_data is what we read from input file
  for (std::string line; std::getline(ifs, line); line = "") {
    subv = utilities::GetSubstrs(line, ',');
    dna_data.push_back(subv);
  }
  const std::string& test_dna = argv[2];
  // test_dna is dna_sequence
  std::vector<int> check_num = {};
  // check_num vector is what we need for Match function
  for (size_t i = 1; i < dna_data[0].size(); ++i) {
    check_num.push_back(SequenceNum(test_dna, dna_data[0][i]));
  }

  std::string answer;
  answer = Match(dna_data, check_num);
  std::cout << answer << std::endl;

  return 0;
}
