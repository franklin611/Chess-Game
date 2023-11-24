#include "Vec.h"

bool Vec::operator==(const Vec& other) const {
   return (x == other.x) && (y == other.y);
}

Vec::Vec(int x, int y): x{x}, y{y} {}
