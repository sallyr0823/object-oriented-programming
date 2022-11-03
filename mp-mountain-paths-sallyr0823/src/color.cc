#include "color.hpp"

#include <iostream>
#include <stdexcept>

Color::Color(int r, int g, int b): red_(r), green_(g), blue_(b) {
  // need to ensure valid color has been constructed...
  int min = 0;
  int max = 255;
  if (r < min || r > max || g < min || g > max || b < min || b > max) {
    throw std::invalid_argument("invalid number");
  }
}

// do not modify
bool operator==(const Color& rhs, const Color& lhs) {
  return (rhs.Red() == lhs.Red() && rhs.Green() == lhs.Green() &&
          rhs.Blue() == lhs.Blue());
}
