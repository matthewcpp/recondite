#include "rColor.hpp"

const rColor rColor::White = rColor(255,255,255,255);
const rColor rColor::Red = rColor(255,0,0,255);
const rColor rColor::Green = rColor(0,255,0,255);
const rColor rColor::Blue = rColor(0,0,255,255);
const rColor rColor::Black = rColor(0,0,0,255);

void rColor::Set(unsigned char r, unsigned char g, unsigned char b, unsigned char a){
	red = r;
	green = g;
	blue = b;
	alpha = a;
}
