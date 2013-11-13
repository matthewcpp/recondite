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

#include "rFontGlyph.hpp"

#include "rPath.hpp"

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

class rFontData{
public:
	rFontData();
	~rFontData();

	void Clear();

	void GenerateTexture();

	rContentError WriteToFile(const rString& dir);

	rContentError LoadFromFile(const rString& dir, const rString& name);
	rContentError LoadFromStream(std::istream& glyph, std::istream& texture);

	rContentError LoadFontDataFromFile(const rString& path);
	rContentError LoadFontDataFromStream(std::istream& stream);

	rContentError LoadTextureFromFile(const rString& path);
	rContentError LoadTextureFromStream(std::istream& stream);
	

	int Size() const;
	void SetSize(int size);

	rString Name() const;
	void SetName(const rString& name);

	rString TextureFile() const;

	rGlyphData* AddGlyph(int scancode, short width, short height, short top, short leftBearing, short advance, unsigned char* data);
	void GetGlyphData(rGlyphDataArray& glyphs) const;
	void RemoveGlyph(int scancode);
	size_t GlyphCount() const;

	const rTexture2DData& TextureData() const;

	rString GetPath() const;

private:
	void SetTexCoordsForGlyph(int x, int y, rGlyphData* glyph);
	void WriteGlyphDataToTexture(int x, int y, rGlyphData* glyph);

	rContentError WriteGlyphFile(const rString& path) const;

	rContentError ReadGlyphFile(std::istream& stream);
	rContentError ParseGlyphs(rXMLDocument& document);

private:

	rGlyphDataMap m_glyphs;
	rTexture2DData m_textureData;

	rString m_name;
	rString m_textureFile;
	rString m_path;

	int m_size;
	bool m_textureGenerated;
};

#endif
