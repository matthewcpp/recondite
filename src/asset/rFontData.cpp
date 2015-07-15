#include "asset/rFontData.hpp"

rGlyphData::rGlyphData(){
	data = nullptr;
}

rGlyphData::rGlyphData(int s, short w, short h, short t, short l, short a, unsigned char* d)
:rFontGlyph(s,w,h,t,l,a)
{
	data = new unsigned char [w * h];
	memcpy(data, d, w * h);
}

rGlyphData::~rGlyphData(){
	if (data)
		delete[] data;
}

rFontData::rFontData(uint16_t size, rFontStyle style, uint16_t lineHeight, uint16_t ascender, uint16_t descender){
	m_size = size;
	m_fontStyle = style;
	m_lineHeight = lineHeight;
	m_ascender = ascender;
	m_descender = descender;
}

rFontData::~rFontData(){
	Clear();
}

void rFontData::Clear(){
	m_glyphs.clear();
}

void  rFontData::ForEach(IteratorFunc func){
	for (auto glyphEntry : m_glyphs){
		if (!func(glyphEntry.second)) return;
	}
}

rGlyphData* rFontData::AddGlyph(int scancode, short width, short height, short top, short leftBearing, short advance, unsigned char* data){
	if (m_glyphs.count(scancode)){
		RemoveGlyph(scancode);
	}

	rGlyphData* glyph = new rGlyphData(scancode, width, height, top, leftBearing, advance, data);
	m_glyphs[scancode] = glyph;

	return glyph;
}

void rFontData::RemoveGlyph(int scancode){
	rGlyphDataMap::iterator it = m_glyphs.find(scancode);

	if (it != m_glyphs.end()){
		delete it->second;
		m_glyphs.erase(scancode);
	}
}

size_t rFontData::GlyphCount() const{
	return m_glyphs.size();
}

void rFontData::GetGlyphData(rGlyphDataArray& glyphs) const{
	glyphs.clear();
	glyphs.reserve(m_glyphs.size());

	for (rGlyphDataMap::const_iterator it = m_glyphs.begin(); it != m_glyphs.end(); ++it)
		glyphs.push_back(it->second);
}

uint16_t rFontData::LineHeight() const{
	return m_lineHeight;
}

uint16_t rFontData::Ascender() const{
	return m_ascender;
}

uint16_t rFontData::Descender() const{
	return m_descender;
}

//-----------------------

rFontFamilyData::rFontFamilyData(){
	m_textureGenerated = false;
}

rFontData* rFontFamilyData::CreateFont(uint32_t size, rFontStyle style, uint16_t lineHeight, uint16_t ascender, uint16_t descender){
	std::shared_ptr<rFontData> fontData;
	fontData.reset(new rFontData(size, style, lineHeight, ascender, descender));



	return fontData.get();
}

void rFontFamilyData::DeleteFont(uint32_t size, rFontStyle style){

}

rFontData* rFontFamilyData::GetFont(uint32_t size, rFontStyle style){
	return nullptr;
}

void rFontFamilyData::Clear(){
	m_fonts.clear();
}

rString rFontFamilyData::Name() const{
	return m_name;
}

void rFontFamilyData::SetName(const rString& name){
	m_name = name;
}

void rFontFamilyData::GatherGlyphs(rGlyphDataArray& glyphs){
	auto end = m_fonts.end();
	for (auto it = m_fonts.begin(); it != m_fonts.end(); ++it){
		it->second->ForEach([&glyphs](rGlyphData* glyphData)->bool{
			glyphs.push_back(glyphData);
			return true;
		});
	}
}

void rFontFamilyData::GenerateTexture(){
	rGlyphDataArray sortedGlyphs;
	GatherGlyphs(sortedGlyphs);

	std::sort(sortedGlyphs.begin(), sortedGlyphs.end(), rGlyphDataHeightSortDesc());

	short TEXTURE_SIZE = 256;

	m_textureData.Allocate(TEXTURE_SIZE, TEXTURE_SIZE, 4);
	m_textureData.FillColor(rColor::Black);

	int rowHeight = sortedGlyphs[0]->height;
	int yIndex = 0;
	int xIndex = 0;

	for (size_t i = 0; i < sortedGlyphs.size(); i++){
		rGlyphData* g = sortedGlyphs[i];

		if (xIndex + g->width >= TEXTURE_SIZE){
			yIndex += rowHeight;
			rowHeight = g->height;
			xIndex = 0;

			if (yIndex >= TEXTURE_SIZE) break;
		}

		WriteGlyphDataToTexture(xIndex, yIndex, g);
		SetTexCoordsForGlyph(xIndex, yIndex, g);

		xIndex += g->width;
	}

	m_textureGenerated = true;
}

void rFontFamilyData::SetTexCoordsForGlyph(int x, int y, rGlyphData* glyph){
	float TEXTURE_SIZE = 256.0f;

	float top = 1.0f - (y / TEXTURE_SIZE);
	float bottom = 1.0f - ((y + glyph->height) / TEXTURE_SIZE);
	float left = x / TEXTURE_SIZE;
	float right = (x + glyph->width) / TEXTURE_SIZE;

	glyph->texCoords[0].Set(left, top);
	glyph->texCoords[1].Set(right, top);
	glyph->texCoords[2].Set(right, bottom);
	glyph->texCoords[3].Set(left, bottom);
}

void rFontFamilyData::WriteGlyphDataToTexture(int x, int y, rGlyphData* glyph){
	rColor pixel(255, 255, 255, 255);
	int dataIndex = 0;

	for (int yPos = 0; yPos < glyph->height; yPos++){
		for (int xPos = 0; xPos < glyph->width; xPos++){
			pixel.alpha = glyph->data[dataIndex++];

			m_textureData.SetPixel(x + xPos, y + yPos, pixel);
		}
	}
}

const rTextureData& rFontFamilyData::TextureData() const{
	return m_textureData;
}