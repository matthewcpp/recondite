#ifndef R_FONTGLYPH_HPP
#define R_FONTGLYPH_HPP

#include <vector>
#include <cstring>

#include "rBuild.hpp"

#include "rVector2.hpp"

struct RECONDITE_API rFontGlyph{
public:
	rFontGlyph();
	rFontGlyph(const rFontGlyph& g);
	rFontGlyph(int s, short w, short h, short t, short l, short a);
	rFontGlyph(int s, short w, short h, short t, short l, short a, rVector2* tc);
	virtual ~rFontGlyph(){}
	
	void Set(int s, short w, short h, short t, short l, short a);

public:
	int scancode;
	short width;
	short height;
	short top;
	short leftBearing;
	short advance;

	rVector2 texCoords[4];
};

typedef std::vector<rFontGlyph*> rFontGlyphArray;

#endif
