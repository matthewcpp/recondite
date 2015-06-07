#ifndef R_FONTDATA_HPP
#define R_FONTDATA_HPP

#include <map>
#include <vector>
#include <algorithm>

#include "rBuild.hpp"
#include "rDefs.hpp"
#include "rString.hpp"

#include "xml/rXMLDocument.hpp"

#include "asset/rTextureData.hpp"
#include "rVector2.hpp"

#include "rFontGlyph.hpp"

#include "rPath.hpp"

#include "stream/rIFileStream.hpp"

struct RECONDITE_API rGlyphData : public rFontGlyph{
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
	rFontData();
	~rFontData();

	void Clear();

	void GenerateTexture();
	

	int Size() const;
	void SetSize(int size);

	size_t Ascender() const;
	void SetAscender(size_t ascender);

	size_t Descender() const;
	void SetDescender(size_t descender);

	size_t LineHeight () const;
	void SetLineHeight(size_t lineHeight);

	rString Name() const;
	void SetName(const rString& name);


	rGlyphData* AddGlyph(int scancode, short width, short height, short top, short leftBearing, short advance, unsigned char* data);
	void GetGlyphData(rGlyphDataArray& glyphs) const;
	void RemoveGlyph(int scancode);
	size_t GlyphCount() const;

	const rTextureData& TextureData() const;
	bool TextureDataPresent() const;

	rString GetPath() const;
	void SetPath(const rString& path);

	rString TextureFile() const;
	rString TexturePath() const;

	void SetTexCoordsForGlyph(int x, int y, rGlyphData* glyph);
	void WriteGlyphDataToTexture(int x, int y, rGlyphData* glyph);

private:

	rGlyphDataMap m_glyphs;
	rTextureData m_textureData;

	rString m_name;
	rString m_textureFile;
	rString m_path;

	int m_size;
	size_t m_lineHeight;
	size_t m_ascender;
	size_t m_descender;

	bool m_textureGenerated;
};

#endif
