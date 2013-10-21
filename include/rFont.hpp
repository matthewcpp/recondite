#ifndef R_FONT_HPP
#define R_FONT_HPP

#include <map>

#include "rTypes.hpp"
#include "rDefs.hpp"

#include "rFontGlyph.hpp"
#include "rTexture2D.hpp"
#include "rAsset.hpp"

typedef std::map<int, rFontGlyph*> rFontGlyphMap;

class rFont : public rAsset{
public:
	rFont(rTexture2D* texture, int assetid, const rString& name, const rString& path);
	~rFont();
	
	const rFontGlyph* GetGlyph(int scancode) const;
	rFontGlyph* AddGlyph(const rFontGlyph& g);
	size_t NumGlyphs() const;
	rTexture2D* Texture() const;
	
	void RemoveGlyph(int scancode);
	
	void Clear();
	
	virtual rAssetType Type() const;
private:

	rFontGlyphMap m_glyphs;
	rTexture2D* m_texture;
};

typedef std::map<rString, rFont*> rFontMap;

#endif
