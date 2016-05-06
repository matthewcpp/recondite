#ifndef R_FONTGLYPH_HPP
#define R_FONTGLYPH_HPP

#include <cstdint>


#include "rBuild.hpp"
#include "rVector2.hpp"

enum class rFontStyle : unsigned char{
	Normal, Bold, Italic
};

struct RECONDITE_API rFontGlyph{
public:
	rFontGlyph() {}
	rFontGlyph(uint32_t _scancode, int16_t _width, int16_t _height, int16_t _top, int16_t _leftBearing, int16_t _advance, const rVector2& _uvOrigin, const rVector2& _uvSize)
		:scancode(_scancode), width(_width), height(_height), top(_top), leftBearing(_leftBearing), advance(_advance), uvOrigin(_uvOrigin), uvSize(_uvSize) {}

public:
	uint32_t scancode;
	int16_t width;
	int16_t height;
	int16_t top;
	int16_t leftBearing;
	int16_t advance;

	rVector2 uvOrigin;
	rVector2 uvSize;
	rVector2 texCoords[4]; //temp
};

//temp
#include <vector>
typedef std::vector<rFontGlyph*> rFontGlyphArray;

class RECONDITE_API rFontFace{
	uint16_t m_size;
	rFontStyle m_fontStyle;

	uint16_t m_lineHeight;
	uint16_t m_ascender;
	uint16_t m_descender;
};

class RECONDITE_API rFontFamily{

};

#endif
