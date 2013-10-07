#include "rFont.hpp"

rFont::rFont(rTexture2D* texture, int assetid, const rString& name, const rString& path)
:rAsset(assetid, name, path)
{
	m_texture = texture;
}

rAssetType rFont::Type() const{
	return rASSET_FONT;
}

rFont::~rFont(){
	Clear();
}

const rFontGlyph* rFont::GetGlyph(int scancode) const{
	rFontGlyphMap::const_iterator result = m_glyphs.find(scancode);
	
	if (result == m_glyphs.end()){
		return NULL;
	}
	else{
		return result->second;
	}
}

rFontGlyph* rFont::AddGlyph(const rFontGlyph& g){
	RemoveGlyph(g.scancode);
	
	rFontGlyph* glyph = new rFontGlyph(g);
	m_glyphs[g.scancode]= glyph;
	
	return glyph;
}

void rFont::RemoveGlyph(int scancode){
	rFontGlyphMap::iterator result = m_glyphs.find(scancode);
	
	if (result != m_glyphs.end()){
		delete result->second;
		m_glyphs.erase(result);
	}
}

size_t rFont::NumGlyphs() const{
	m_glyphs.size();
}

void rFont::Clear(){
	for (rFontGlyphMap::iterator it = m_glyphs.begin(); it != m_glyphs.end(); ++it)
		delete it->second;
	
	m_glyphs.clear();
}
