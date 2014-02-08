#include "rPoint.hpp"

const rPoint rPoint::Zero = rPoint(0,0);

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

float rPoint::Distance(const rPoint& pt) const{
	rPoint p = pt - *this;
	return std::sqrt(p.x * p.x + p.y * p.y);
}
