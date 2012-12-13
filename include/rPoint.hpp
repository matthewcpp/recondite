#ifndef R_POINT_HPP
#define R_POINT_HPP

struct rPoint{
	rPoint(){}
	rPoint(int xx , int yy) : x(xx) , y(yy){}
	
	void Set(int xx, int yy);

	int x;
	int y;
};

#endif