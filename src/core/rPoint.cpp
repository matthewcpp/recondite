#include "rPoint.hpp"

rPoint rPoint::operator+ (const rPoint& p) const{
	return rPoint(x + p.x, y + p.y);
}

rPoint& rPoint::operator+=(const rPoint& p){
	x += p.x;
	y+= p.y;

	return *this;
}

rPoint rPoint::operator- (const rPoint& p) const{
	return rPoint(x - p.x, y - p.y);
}

rPoint& rPoint::operator-=(const rPoint& p){
	x -= p.x;
	y -= p.y;

	return *this;
}

void rPoint::Set(int xx, int yy){
	x = xx;
	y = yy;
}
