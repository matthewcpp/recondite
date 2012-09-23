#include "rColor.hpp"

rColour::rColour(unsigned char r, unsigned char g, unsigned char b, unsigned char a){
	Set(r,g,b,a);
}

void rColour::Set(unsigned char r, unsigned char g, unsigned char b, unsigned char a){
	red = r;
	green = g;
	blue = b;
	alpha = a;
}