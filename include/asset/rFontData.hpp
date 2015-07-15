#ifndef R_FONTDATA_HPP
#define R_FONTDATA_HPP

#include <map>
#include <vector>
#include <algorithm>
#include <memory>
#include <functional>

#include "rBuild.hpp"
#include "rDefs.hpp"
#include "rString.hpp"

#include "xml/rXMLDocument.hpp"

#include "asset/rTextureData.hpp"
#include "rVector2.hpp"

#include "rFontGlyph.hpp"

#include "rPath.hpp"

#include "stream/rIFileStream.hpp"

struct rGlyphData : public rFontGlyph{
	rGlyphData();
	rGlyphData(int s, short w, short h, short t, short l, short a, unsigned char* d);
	~rGlyphData();

	unsigned char* data;
};

struct rGlyphDataHeightSortDesc{
	bool operator() (const rGlyphData* g1, const rGlyphData* g2){
		return g2->height < g1->height;
	}
};

typedef std::map <int, rGlyphData*> rGlyphDataMap;
typedef std::vector <rGlyphData*> rGlyphDataArray;

class RECONDITE_API rFontData{
public:
	rFontData(uint16_t size, rFontStyle style, uint16_t lineHeight, uint16_t ascender, uint16_t descender);
	~rFontData();

	typedef std::function<bool(rGlyphData*)> IteratorFunc;

public:
	void Clear();
	
	uint16_t Size() const;
	uint16_t Ascender() const;
	uint16_t Descender() const;
	uint16_t LineHeight() const;

	void ForEach(IteratorFunc func);

	rGlyphData* AddGlyph(int scancode, short width, short height, short top, short leftBearing, short advance, unsigned char* data);
	void GetGlyphData(rGlyphDataArray& glyphs) const;
	void RemoveGlyph(int scancode);
	size_t GlyphCount() const;

private:

	rGlyphDataMap m_glyphs;

	uint16_t m_size;
	rFontStyle m_fontStyle;

	uint16_t m_lineHeight;
	uint16_t m_ascender;
	uint16_t m_descender;
};

class RECONDITE_API rFontFamilyData{
public:
	rFontFamilyData();

public:
	void Clear();

	rFontData* CreateFont(uint32_t size, rFontStyle style, uint16_t lineHeight, uint16_t ascender, uint16_t descender);
	rFontData* GetFont(uint32_t size, rFontStyle style = rFontStyle::Normal);
	void DeleteFont(uint32_t size, rFontStyle style = rFontStyle::Normal);

	rString Name() const;
	void SetName(const rString& name);


	void GenerateTexture();
	const rTextureData& TextureData() const;

private:

	void GatherGlyphs(rGlyphDataArray& glyphs);
	void SetTexCoordsForGlyph(int x, int y, rGlyphData* glyph);
	void WriteGlyphDataToTexture(int x, int y, rGlyphData* glyph);

private:
	typedef std::map<int, std::shared_ptr<rFontData>> rFontDataMap;

	rFontDataMap m_fonts;
	rTextureData m_textureData;

	rString m_name;


	bool m_textureGenerated;
};

#endif
