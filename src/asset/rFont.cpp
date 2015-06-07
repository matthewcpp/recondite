#include "asset/rFont.hpp"

rFont::rFont(const rString& name, rTexture* texture, size_t size, size_t lineHeight, size_t ascender, size_t descender)
{
	m_texture = texture;
	m_size = size;
	m_lineHeight = lineHeight;
	m_ascender = ascender;
	m_descender = descender;

	m_name = name;
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
	return m_lineHeight;
}

void rFont::Clear(){
	for (rFontGlyphMap::iterator it = m_glyphs.begin(); it != m_glyphs.end(); ++it)
		delete it->second;
	
	m_glyphs.clear();
}

rTexture* rFont::Texture() const{
	return m_texture;
}

size_t rFont::Ascender() const{
	return m_ascender;
}

size_t rFont::Descender() const{
	return m_descender;
}


rSize rFont::MeasureString(const rString& str, int lineWidth) const{
	int baseline = Ascender();
	rSize result(0, 0);

	int spaceLeft = lineWidth;
	int wordWidth = 0;
	int wordDepth = 0;

	for (size_t i = 0; i < str.size(); i++){
		int c = str[i];

		if (c == '\n'){
			if (wordWidth > spaceLeft ){ //current word will not fit on this line
				baseline += LineHeight();
				spaceLeft = lineWidth - wordWidth;
				result.x = std::max(result.x, lineWidth - spaceLeft);
				result.y = baseline + wordDepth;
			}
			else{
				result.x = std::max(result.x, lineWidth - (spaceLeft - wordWidth));
			}

			baseline += LineHeight();
			result.y = baseline;

			spaceLeft = lineWidth;
			wordWidth = 0;
			wordDepth = 0;
		}
		else{
			const rFontGlyph* glyph = GetGlyph(c);

			if (c == ' '){
				if (wordWidth + glyph->advance > spaceLeft ){ //current word will not fit on this line
					baseline += LineHeight();
					result.x = std::max(result.x, lineWidth - spaceLeft);
					result.y = baseline + wordDepth;

					spaceLeft = lineWidth - wordWidth;
				}
				else {
					int bottom = baseline + glyph->height - glyph->top;
					result.x = std::max(result.x, lineWidth - (spaceLeft - wordWidth));
					result.y = std::max(result.y , baseline + wordDepth);
					spaceLeft -= wordWidth + glyph->advance;
				}

				wordWidth = 0;
				wordDepth = 0;
			}
			else{
				wordWidth += glyph->advance;
				wordDepth = std::max(wordDepth,  glyph->height - glyph->top);
			}
		}
	}

	//handle last 'word'
	result.x = std::max(result.x, lineWidth - (spaceLeft - wordWidth));
	result.y = std::max(result.y , baseline + (int)Descender());

	return result;
}
