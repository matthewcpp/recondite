#include "rSize.hpp"

const rSize rSize::Default = rSize(-1, -1);

void rSize::Set(int xx , int yy){
	x = xx;
	y = yy;
}

bool rSize::operator == (const rSize& sz) const{
	return x == sz.x && y == sz.y;
}

bool rSize::operator != (const rSize& sz) const{
	return ! (*this == sz);
}
