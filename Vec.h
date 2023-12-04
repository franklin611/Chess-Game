#ifndef _VEC_H_
#define _VEC_H_

#include <iostream>
using namespace std;

class Vec {
		int x; // x coordinate of a piece 
		int y; // y coordinate of a piece 
		public:
			// default constructor 
			Vec(int x, int y);
			// equality operator 
			bool operator==(const Vec& other) const;
			// get the x coordinate
			int getX();
			// get the y coordinate 
			int getY();
			// set the x coordinate 
			void setX(int num);
			// set the y coordinate
			void setY(int num);
			// default constructor 
			Vec() = default;
			// move constructor 
			Vec(Vec&& other);
			// copy constructor 
			Vec(const Vec& other);
			// copy assignment operator 
			Vec& operator=(const Vec& other);
			friend ostream &operator<<(ostream &out, Vec &v); // Output operator to help display Vec coordinates tranlsated to points on the board
};

#endif
