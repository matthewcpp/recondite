#include "rFontGlyph.hpp"

rFontGlyph::rFontGlyph(){
}

rFontGlyph::rFontGlyph(const rFontGlyph& g){
	Set(g.scancode,g.width,g.height,g.top,g.leftBearing,g.advance);
	memcpy(texCoords, g.texCoords, sizeof (rVector2) * 4);
}

rFontGlyph::rFontGlyph(int s, short w, short h, short t, short l, short a){
	Set(s,w,h,t,l,a);
	memset(texCoords, 0, sizeof (rVector2) * 4);
}

rFontGlyph::rFontGlyph(int s, short w, short h, short t, short l, short a, rVector2* tc){
	Set(s,w,h,t,l,a);
	memcpy(texCoords, tc, sizeof (rVector2) * 4);
}

void rFontGlyph::Set(int s, short w, short h, short t, short l, short a){
	scancode = s;
	width = w;
	height = h;
	top = t;
	leftBearing = l;
	advance = a;
}