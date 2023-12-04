#include "Vec.h"

#include <utility>
using namespace std;

// equality operator 
bool Vec::operator==(const Vec& other) const {
   return (x == other.x) && (y == other.y);
}

// copy assignment operator 
Vec& Vec::operator=(const Vec& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
}

// copy constructor 
Vec::Vec(const Vec& other) : x(other.x), y(other.y) {}

// move constructor
Vec::Vec(Vec&& other)
        : x(std::move(other.x)), y(std::move(other.y)) {}

// defualt constuctor 
Vec::Vec(int x, int y): x{x}, y{y} {}

// get the x coordinate
int Vec::getX(){ return x; }

// get the y coordinate
int Vec::getY(){ return y; }

// set the x coordinate
void Vec::setX(int num){ x = num; }

// set the y coordinate
void Vec::setY(int num){ y = num; }

// output opearator 
ostream &operator<<(ostream &out, Vec &v) {
    cout << "(" << char(v.getX() + 97) << ", " << v.getY() + 1<< ")"; // Conversion from our gameboard to coordinates on an actual chessboard
    return out;
}
