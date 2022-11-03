#include "elevation_dataset.hpp"

#include <fstream>
#include <iostream>
using namespace std;

ElevationDataset::ElevationDataset(const std::string& filename,
                                   size_t width,size_t height) {
  std::ifstream ifs{filename};
  int value = 0;
  width_ = width;
  height_ = height;
  int min = std::numeric_limits<int>::max();
  int max = std::numeric_limits<int>::min();
  size_t j = 0, i = 0;
  if (!ifs.is_open() || ifs.bad()) {
    throw std::runtime_error("Wrong file");
  }
  data_.push_back(std::vector<int>(width_, 0));
  while (ifs.good()) {
    ifs >> value;
    if (ifs.fail()) {
      ifs.clear();
      ifs.ignore(1, '\n');
    } else {
      if (j == width_) {
        i++;
        j = 0;
        data_.push_back(std::vector<int>(width_, 0));
      }
      data_[i][j] = value;
      j++;
      if (value < min) min = value;
      if (value > max) max = value;
    }
  }
  if (i != height_ - 1 || j != width_) {
    throw std::runtime_error("Inadequate data input!");
  }
  min_ele_ = min;
  max_ele_ = max;
}

size_t ElevationDataset::Width() const { return width_; }
size_t ElevationDataset::Height() const { return height_; }
int ElevationDataset::MaxEle() const { return max_ele_; }
int ElevationDataset::MinEle() const { return min_ele_; }
int ElevationDataset::DatumAt(size_t row, size_t col) const {
  // assert(row >= 0 && row <= height_ && col >= 0 && col <= width_);
  return data_[row][col];
}
const std::vector<std::vector<int>>& ElevationDataset::GetData() const {
  return data_;
}