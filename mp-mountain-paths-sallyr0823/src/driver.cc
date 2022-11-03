#include <fstream>
#include <iostream>
#include <vector>

#include "elevation_dataset.hpp"
int main() {
  ElevationDataset a = ElevationDataset("prompt_5w_2h.dat", 5, 2);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 5; ++j) {
      std::cout << a.DatumAt(i, j) << std::endl;
      std::cout << a.Height() << a.Width() << std::endl;
    }
  }
}