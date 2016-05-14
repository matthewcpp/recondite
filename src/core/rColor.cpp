#include "rColor.hpp"

const rColor rColor::White = rColor(255,255,255,255);
const rColor rColor::Red = rColor(255,0,0,255);
const rColor rColor::Green = rColor(0,255,0,255);
const rColor rColor::Blue = rColor(0,0,255,255);
const rColor rColor::Black = rColor(0,0,0,255);
const rColor rColor::Transparent = rColor(0, 0, 0, 0);

void rColor::Set(unsigned char r, unsigned char g, unsigned char b, unsigned char a){
	red = r;
	green = g;
	blue = b;
	alpha = a;
}

void rColor::Set(const unsigned char* color){
	red = color[0];
	green = color[1];
	blue = color[2];
	alpha = color[3];
}

void rColor::ToArray(unsigned char* color) const{
	color[0] = red;
	color[1] = green;
	color[2] = blue;
	color[3] = alpha;
}

bool rColor::operator==(const rColor& color){
	return red == color.red && blue == color.blue && green == color.green && alpha == color.alpha;
}

bool rColor::operator!=(const rColor& color){
	return !(*this == color);
}