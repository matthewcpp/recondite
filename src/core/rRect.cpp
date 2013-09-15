#include "rRect.hpp"

rRect::rRect(const rPoint& point, const rSize& size){
	Set(point, size);
}

void rRect::Set(int xx, int yy, int wwidth, int hheight){
	x = xx;
	y = yy;
	
	width = wwidth;
	height = hheight;
}

void rRect::Set(const rPoint& point, const rSize& size){
	x = point.x;
	y = point.y;
	
	width = size.x;
	height = size.y;
}

	
void rRect::SetPosition(const rPoint& point){
	x = point.x;
	y = point.y;
}

void rRect::SetPosition(int xx, int yy){
	x = xx;
	y = yy;
}

void rRect::SetSize(const rSize& size){
	width = size.x;
	height = size.y;
}

void rRect::SetSize(int wwidth, int hheight){
	width = wwidth;
	height = hheight;
}

bool rRect::ContainsPoint(const rPoint& point){
	return 	point.x >= x && point.x <= x + width &&
			point.y >= y && point.y <= y + height;
}

int rRect::Left() const{
	return x;
}

int rRect::Right() const{
	return x + width;
}

int rRect::Bottom() const{
	return y + height;
}

int rRect::Top() const{
	return y;
}


