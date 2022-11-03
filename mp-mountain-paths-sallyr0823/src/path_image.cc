#include "path_image.hpp"

#include <fstream>
#include <iostream>

void PathImage::Imputpath(size_t row, const ElevationDataset& dataset) {
  const Color kRed(252, 25, 63);
  Path p(width_, row);
  p.SetLoc(0, row);
  path_image_[row][0] = kRed;
  for (size_t j = 1; j < width_; ++j) {
    int r_up = std::numeric_limits<int>::max();
    int r_do = std::numeric_limits<int>::max();

    int r_ho = abs(dataset.DatumAt(row, j - 1) - dataset.DatumAt(row, j));
    if (row > 0) {
      r_up = abs(dataset.DatumAt(row, j - 1) - dataset.DatumAt(row - 1, j));
    }
    if (row < height_ - 1) {
      r_do = abs(dataset.DatumAt(row, j - 1) - dataset.DatumAt(row + 1, j));
    }
    int dis[3] = {r_ho, r_do, r_up};
    int num[3] = {0, 1, -1};
    size_t min = 0;
    for (size_t k = 0; k < 3; k++) {
      if (dis[k] < dis[min]) {
        min = k;
      }
    }
    row = row + num[min];
    p.IncEleChange(dis[min]);
    p.SetLoc(j, row);
    path_image_[row][j] = kRed;
  }
  paths_.push_back(p);
}

PathImage::PathImage(const GrayscaleImage& image,
                     const ElevationDataset& dataset) {
  height_ = image.Height();
  width_ = image.Width();
  path_image_ = image.GetImage();
  const Color kGreen(31, 253, 13);
  size_t min_index = 0;
  for (size_t i = 0; i < height_; ++i) {
    Imputpath(i, dataset);
  }

  for (size_t j = 0; j < height_; ++j) {
    if (paths_[j].EleChange() < paths_[min_index].EleChange() &&
        j > min_index) {
      min_index = j;
    }
  }
  for (size_t m = 0; m < width_; ++m) {
    path_image_[paths_[min_index].GetPath()[m]][m] = kGreen;
  }
}

size_t PathImage::Height() const { return height_; }
size_t PathImage::Width() const { return width_; }
unsigned int PathImage::MaxColorValue() const { return kMaxColorValue; }
const std::vector<Path>& PathImage::Paths() const { return paths_; }
const std::vector<std::vector<Color>>& PathImage::GetPathImage() const {
  return path_image_;
}
void PathImage::ToPpm(const std::string& name) const {
  std::ofstream myfile(name);

  if (myfile.is_open()) {
    myfile << "P3" << std::endl;
    myfile << width_ << " " << height_ << std::endl;
    myfile << kMaxColorValue << std::endl;
    for (size_t i = 0; i < height_; ++i) {
      for (size_t j = 0; j < width_ - 1; ++j) {
        int r_out = path_image_[i][j].Red();
        int g_out = path_image_[i][j].Green();
        int b_out = path_image_[i][j].Blue();
        myfile << r_out << " " << g_out << " " << b_out << " ";
      }
      Color end = path_image_[i][width_ - 1];
      myfile << end.Red() << " " << end.Green() << " " << end.Blue() << " "
             << std::endl;
    }
  }
}