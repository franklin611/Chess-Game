#ifndef _VEC_H_
#define _VEC_H_
class Vec {
		int x;
		int y;
		public:
			Vec(int x, int y);
			bool operator==(const Vec& other) const;
			int getX();
			int getY();
			void setX(int num);
			void setY(int num);
			Vec() = default;
			Vec(Vec&& other);
			Vec(const Vec& other);
			Vec& operator=(const Vec& other);
};

#endif
