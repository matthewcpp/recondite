#ifndef R_FONTDATA_HPP
#define R_FONTDATA_HPP

#include <map>
#include <vector>
#include <algorithm>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "xml/rXMLDocument.hpp"

#include "data/rTexture2DData.hpp"
#include "rVector2.hpp"

struct rGlyphData{
	rGlyphData(int s, short w, short h, short t, short l, short a, unsigned char* d);
	~rGlyphData();

	int scancode;
	short width;
	short height;
	short top;
	short leftBearing;
	short advance;
	unsigned char* data;

	rVector2 texCoords[4];
};

struct rGlyphDataHeightSortDesc{
	bool operator() (const rGlyphData* g1, const rGlyphData* g2){
		return g2->height < g1->height;
	}
};

typedef std::map <int, rGlyphData*> rGlyphDataMap;
typedef std::vector <rGlyphData*> rGlyphDataArray;

class rFontData{
public:
	rFontData();
	~rFontData();

	void Clear();

	void GenerateTexture();

	rContentError WriteToFile(const rString& dir) ;

	int Size() const;
	void SetSize(int size);

	rString Name() const;
	void SetName(const rString& name);

	rGlyphData* AddGlyph(int scancode, short width, short height, short top, short leftBearing, short advance, unsigned char* data);
	void RemoveGlyph(int scancode);
	size_t GlyphCount() const;

	const rTexture2DData& TextureData() const;

private:
	void SetTexCoordsForGlyph(int x, int y, rGlyphData* glyph);
	void WriteGlyphDataToTexture(int x, int y, rGlyphData* glyph);

	rContentError WriteGlyphFile(const rString& path) const;

private:

	rGlyphDataMap m_glyphs;
	rTexture2DData m_textureData;

	rString m_name;

	int m_size;
	bool m_textureGenerated;
};

#endif