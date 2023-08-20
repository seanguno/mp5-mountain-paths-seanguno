#include "color.hpp"
#include <stdexcept>

Color::Color(int r, int g, int b): red_(r), green_(g), blue_(b) {
  if (!IsValid(r)) {
    throw std::runtime_error("invalid color value");
  }
  if (!IsValid(g)) {
    throw std::runtime_error("invalid color value");
  }
  if (!IsValid(b)) {
    throw std::runtime_error("invalid color value");
  }
}

// do not modify
bool operator==(const Color& rhs, const Color& lhs) {
  return (rhs.Red() == lhs.Red() && rhs.Green() == lhs.Green() &&
          rhs.Blue() == lhs.Blue());
}

bool Color::IsValid(int value) {
  return value >= kColorValueMin && value <= kColorValueMax;
}
