#include "functions.hpp"

#include <iostream>
#include <vector>

int SequenceNum(const std::string& test_DNA, const std::string& check_dna) {
  int count = 0;
  // test_DNA is the long input DNA
  // check_dna is the short sequence needed to be paired
  int max_count = 0;
  int num_size = static_cast<int>(check_dna.size());
  size_t i = 0;
  while (i < test_DNA.size() - check_dna.size() + 1) {
    if (test_DNA.substr(i, num_size) == check_dna) {
      i += num_size;
      count++;
    } else {
      i += 1;
      if (count > max_count) {
        max_count = count;
      }
      count = 0;
    }
    if (count > max_count) {
      max_count = count;
    }
  }
  return max_count;
}

std::string Match(std::vector<std::vector<std::string>> dna_data,
                  std::vector<int> input_dna) {
  // input_dna is the number of each consequtive sequences
  size_t count_m = 0;
  size_t line = 0;
  bool match = false;
  for (size_t i = 1; i < dna_data.size(); ++i) {
    for (size_t j = 1; j < dna_data[i].size(); ++j) {
      int num_j = std::stoi(dna_data[i][j]);
      if (input_dna[j - 1] == num_j) {
        count_m++;
      }
    }
    if (count_m == input_dna.size()) {
      line = i;
      match = true;
      break;
    }
  }
  if (match) {
    return dna_data[line][0];
  }
  return "No Match";
}
