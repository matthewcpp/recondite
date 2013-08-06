#include "rColor.hpp"

rColor::rColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a){
	Set(r,g,b,a);
}

void rColor::Set(unsigned char r, unsigned char g, unsigned char b, unsigned char a){
	red = r;
	green = g;
	blue = b;
	alpha = a;
}