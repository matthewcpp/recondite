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

rFontData::rFontData(){
	m_size = 0;
	m_ascender = 0;
	m_descender = 0;

	m_textureGenerated = false;
}

rFontData::~rFontData(){
	Clear();
}

void rFontData::Clear(){
	for (rGlyphDataMap::iterator it = m_glyphs.begin(); it != m_glyphs.end(); ++it)
		delete it->second;

	m_glyphs.clear();

	m_name.clear();
	m_path.clear();
	m_textureFile.clear();

	m_size = 0;
	m_textureGenerated = false;
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

void rFontData::GenerateTexture(){
	rGlyphDataArray sortedGlyphs;

	for (rGlyphDataMap::iterator it = m_glyphs.begin(); it != m_glyphs.end(); ++it){
		sortedGlyphs.push_back(it->second);
	}

	std::sort(sortedGlyphs.begin(), sortedGlyphs.end(), rGlyphDataHeightSortDesc());

	short TEXTURE_SIZE = 256;

	m_textureData.Allocate(TEXTURE_SIZE,TEXTURE_SIZE,4);
	m_textureData.FillColor(rColor::Black);

	int rowHeight = sortedGlyphs[0]->height;
	int yIndex = 0;
	int xIndex = 0;

	for (size_t i = 0; i < sortedGlyphs.size(); i++){
		rGlyphData* g = sortedGlyphs[i];

		if (xIndex + g->width >= TEXTURE_SIZE ){
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

void rFontData::SetTexCoordsForGlyph(int x, int y, rGlyphData* glyph){
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

void rFontData::WriteGlyphDataToTexture(int x, int y, rGlyphData* glyph){
	rColor pixel(255,255,255,255);
	int dataIndex = 0;

	for (int yPos = 0; yPos < glyph->height; yPos++){
		for (int xPos = 0; xPos < glyph->width; xPos++){
			pixel.alpha = glyph->data[dataIndex++];

			m_textureData.SetPixel(x + xPos, y + yPos, pixel);
		}
	}
}

size_t rFontData::GlyphCount() const{
	return m_glyphs.size();
}

int rFontData::Size() const{
	return m_size;
}

void rFontData::SetSize(int size){
	m_size = size;
}

rString rFontData::Name() const{
	return m_name;
}

void rFontData::SetName(const rString& name){
	m_name = name;
}

const rTextureData& rFontData::TextureData() const{
	return m_textureData;
}



rString rFontData::TextureFile() const{
	return m_textureFile;
}

rString rFontData::TexturePath() const{
	rString dir = rPath::Directory(m_path);
	return rPath::Combine(dir, m_textureFile);
}

rString rFontData::GetPath() const{
	return m_path;
}

void rFontData::SetPath(const rString& path){
	m_path = path;
}

void rFontData::GetGlyphData(rGlyphDataArray& glyphs) const{
	glyphs.clear();
	glyphs.reserve(m_glyphs.size());

	for (rGlyphDataMap::const_iterator it = m_glyphs.begin(); it != m_glyphs.end(); ++it)
		glyphs.push_back(it->second);
}

bool rFontData::TextureDataPresent() const{
	return m_textureGenerated;
}

size_t rFontData::LineHeight () const{
	return m_lineHeight;
}

void rFontData::SetLineHeight(size_t lineHeight){
	m_lineHeight = lineHeight;
}

size_t rFontData::Ascender() const{
	return m_ascender;
}

void rFontData::SetAscender(size_t ascender){
	m_ascender = ascender;
}

size_t rFontData::Descender() const{
	return m_descender;
}

void rFontData::SetDescender(size_t descender){
	m_descender = descender;
}