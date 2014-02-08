#ifndef R_POINT_HPP
#define R_POINT_HPP

#include <cmath>

struct rPoint{
	rPoint(){}
	rPoint(int xx , int yy) : x(xx) , y(yy){}
	
	void Set(int xx, int yy);

	rPoint operator+ (const rPoint& p) const;
	rPoint& operator+=(const rPoint& p);
	rPoint operator- (const rPoint& p) const;
	rPoint& operator-=(const rPoint& p);

	float Distance(const rPoint& pt) const;

	int x;
	int y;

	static const rPoint Zero;
};

#endif
