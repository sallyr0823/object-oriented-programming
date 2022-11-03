#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "utilities.hpp"
int SequenceNum(const std::string& test_DNA, const std::string& check_dna);
std::string Match(std::vector<std::vector<std::string>> dna_data,
                  std::vector<int> input_dna);
#endif