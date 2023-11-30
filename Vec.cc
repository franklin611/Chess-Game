#include "Vec.h"
#include <utility>

bool Vec::operator==(const Vec& other) const {
   return (x == other.x) && (y == other.y);
}

Vec& Vec::operator=(const Vec& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }

Vec::Vec(const Vec& other) : x(other.x), y(other.y) {}

Vec::Vec(Vec&& other)
        : x(std::move(other.x)), y(std::move(other.y)) {}

Vec::Vec(int x, int y): x{x}, y{y} {}

int Vec::getX(){ return x; }

int Vec::getY(){ return y; }

void Vec::setX(int num){ x = num; }

void Vec::setY(int num){ y = num; }