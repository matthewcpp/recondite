#include "rFont.hpp"

rFont::rFont(rTexture2D* texture, size_t size, int assetid, const rString& name, const rString& path)
:rAsset(assetid, name, path)
{
	m_texture = texture;
	m_size = size;
}

rAssetType rFont::Type() const{
	return rASSET_FONT;
}

rFont::~rFont(){
	Clear();
}

rFontGlyph* rFont::GetGlyph(int scancode) const{
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
	return m_glyphs.size();
}

size_t rFont::Size() const{
	return m_size;
}

size_t rFont::LineHeight() const{
	return Size();
}

void rFont::Clear(){
	for (rFontGlyphMap::iterator it = m_glyphs.begin(); it != m_glyphs.end(); ++it)
		delete it->second;
	
	m_glyphs.clear();
}

rTexture2D* rFont::Texture() const{
	return m_texture;
}

rSize rFont::MeasureString(const rString& str, int lineWidth) const{
	rSize result(0, LineHeight());

	int spaceLeft = lineWidth;
	int wordWidth = 0;

	for (int i = 0; i < str.size(); i++){
		int c = str[i];

		if (c == '\n'){
			if (wordWidth > spaceLeft ){ //current word will not fit on this line
				result.y += LineHeight();
				result.x = std::max(result.x, lineWidth - (spaceLeft - wordWidth));
			}

			spaceLeft = lineWidth;
			wordWidth = 0;
		}
		else{
			const rFontGlyph* glyph = GetGlyph(c);

			if (c == ' '){
				if (wordWidth + glyph->advance > spaceLeft ){ //current word will not fit on this line
					result.y += LineHeight();
					result.x = std::max(result.x, lineWidth - spaceLeft);

					spaceLeft = lineWidth - wordWidth;
				}
				else {
					spaceLeft -= wordWidth + glyph->advance;
					wordWidth = 0;
				}
			}
			else{
				wordWidth += glyph->advance;
			}
		}
	}

	result.x = std::max(result.x, lineWidth - (spaceLeft - wordWidth));

	return result;
}
