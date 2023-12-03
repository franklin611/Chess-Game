#include "Vec.h"

#include <utility>
using namespace std;

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

ostream &operator<<(ostream &out, Vec &v) {
    cout << "(" << char(v.getX() + 97) << ", " << v.getY() + 1<< ")"; // Conversion from our gameboard to coordinates on an actual chessboard
    return out;
}
