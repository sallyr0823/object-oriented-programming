#include "grayscale_image.hpp"

#include <fstream>
#include <iostream>

GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) {
  height_ = dataset.Height();
  width_ = dataset.Width();
  image_ = std::vector<std::vector<Color>>(height_, std::vector<Color>(width_));
  // color image_
  for (size_t i = 0; i < height_; ++i) {
    for (size_t j = 0; j < width_; ++j) {
      if (dataset.MaxEle() == dataset.MinEle()) {
        image_[i][j] = Color(0, 0, 0);
      } else {
        int c = (int)std::round(
            (double)(dataset.DatumAt(i, j) - dataset.MinEle()) /
            (dataset.MaxEle() - dataset.MinEle()) * kMaxColorValue);
        image_[i][j] = Color(c, c, c);
      }
    }
  }
}

GrayscaleImage::GrayscaleImage(const std::string& filename,
                               size_t width,
                               size_t height) {
  ElevationDataset gray_data(filename, width, height);
  height_ = height;
  width_ = width;
  image_ = std::vector<std::vector<Color>>(height_, std::vector<Color>(width_));
  // color image_
  for (size_t i = 0; i < height_; ++i) {
    for (size_t j = 0; j < width_; ++j) {
      if (gray_data.MaxEle() == gray_data.MinEle()) {
        image_[i][j] = Color(0, 0, 0);
      } else {
        int c = (int)std::round(
            (double)(gray_data.DatumAt(i, j) - gray_data.MinEle()) /
            (gray_data.MaxEle() - gray_data.MinEle()) * kMaxColorValue);
        image_[i][j] = Color(c, c, c);
      }
    }
  }
}

size_t GrayscaleImage::Width() const { return width_; }
size_t GrayscaleImage::Height() const { return height_; }
unsigned int GrayscaleImage::MaxColorValue() const { return kMaxColorValue; }
const Color& GrayscaleImage::ColorAt(int row, int col) const {
  return image_[row][col];
}
const std::vector<std::vector<Color>>& GrayscaleImage::GetImage() const {
  return image_;
}
void GrayscaleImage::ToPpm(const std::string& name) const {
  std::ofstream ofs{name};

  if (ofs.is_open()) {
    ofs << "P3" << std::endl;
    ofs << width_ << " " << height_ << std::endl;
    ofs << kMaxColorValue << std::endl;
    for (size_t i = 0; i < height_; ++i) {
      for (size_t j = 0; j < width_ - 1; ++j) {
        ofs << image_[i][j].Red() << " " << image_[i][j].Green() << " "
            << image_[i][j].Blue() << " ";
      }
      Color end = image_[i][width_ - 1];
      ofs << end.Red() << " " << end.Green() << " " << end.Blue() << " "
          << "\n";
    }
  } else {
    throw std::runtime_error("Fail at offstream!");
  }
  ofs.close();
}