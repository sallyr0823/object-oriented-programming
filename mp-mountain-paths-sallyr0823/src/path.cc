#include "path.hpp"

#include "elevation_dataset.hpp"

Path::Path(size_t length, size_t starting_row) {
  starting_row_ = starting_row;
  length_ = length;
  path_ = std::vector<size_t>(length);
}
/*ElevationDataset path;
std::vector<std::vector<int>> path_data = path.GetData();
// path_
path_.push_back(starting_row);
length_ = length;
size_t r = starting_row;
starting_row_ = starting_row;
size_t height = path.Height();
size_t i = 0;
int ele_change = 0;

while (i < length - 1) {
  int r_ho = abs(path_data[r][i + 1] - path_data[r][i + 1]);
  if (r > 0 && r < height - 1) {
    int r_up = abs(path_data[r - 1][i + 1] - path_data[r][i + 1]);
    int r_do = abs(path_data[r + 1][i + 1] - path_data[r][i + 1]);
    int dis[3] = {r_up, r_ho, r_do};
    int min = r_up;
    for (int i = 0; i < 3; i++) {
      if (dis[i] < min) {
        min = dis[i];
        r = i;
      }
    }
    path_.push_back(r);
    ele_change += min;
  }
  if (r == 0) {
    int r_do = abs(path_data[r + 1][i + 1] - path_data[r][i + 1]);
    if (r_do < r_ho) {
      path_.push_back(r + 1);
      r++;
      ele_change_ += r_do;
    } else {
      path_.push_back(r);
      ele_change += r_ho;
    }
  }
  if (r == height - 1) {
    int r_up = abs(path_data[r - 1][i + 1] - path_data[r][i + 1]);
    if (r_up < r_ho) {
      path_.push_back(r - 1);
      r--;
      ele_change += r_up;
    } else {
      path_.push_back(r);
      ele_change += r_ho;
    }
  }
  i++;
}
ele_change_ = ele_change;
}*/

size_t Path::Length() const { return length_; }
size_t Path::StartingRow() const { return starting_row_; }
unsigned int Path::EleChange() const { return ele_change_; }
void Path::IncEleChange(unsigned int value) { ele_change_ += value; }

const std::vector<size_t>& Path::GetPath() const { return path_; }
void Path::SetLoc(size_t col, size_t row) {
  if (col >= 0 && col < length_) {
    path_.at(col) = row;
  } else {
    throw std::invalid_argument("Wrong argument");
  }
}