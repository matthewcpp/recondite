#include "data/rFontData.hpp"

rGlyphData::rGlyphData(int s, short w, short h, short t, short l, short a, unsigned char* d){
	scancode = s;
	width = w;
	height = h;
	top = t;
	leftBearing = l;
	advance = a;

	data = new unsigned char [w * h];
	memcpy(data, d, w * h);
}

rGlyphData::~rGlyphData(){
	if (data)
		delete[] data;
}

rFontData::rFontData(){
	m_size = 0;
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

#include <iostream>

void rFontData::GenerateTexture(){
	rGlyphDataArray sortedGlyphs;

	for (rGlyphDataMap::iterator it = m_glyphs.begin(); it != m_glyphs.end(); ++it){
		sortedGlyphs.push_back(it->second);
	}

	std::sort(sortedGlyphs.begin(), sortedGlyphs.end(), rGlyphDataHeightSortDesc());

	short TEXTURE_SIZE = 256;

	m_textureData.Allocate(TEXTURE_SIZE,TEXTURE_SIZE,4,false);
	m_textureData.FillColor(0,0,0,255);

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

const rTexture2DData& rFontData::TextureData() const{
	return m_textureData;
}

rContentError rFontData::WriteToFile(const rString& dir) {
	if (!m_textureGenerated)
		GenerateTexture();

	rContentError error = WriteGlyphFile (dir + m_name + ".rfnt");
	error = m_textureData.WriteToPath(dir + m_name + "_texture.rtex");

	return error;
}

rContentError rFontData::WriteGlyphFile(const rString& path) const{
	rXMLDocument document;
	rXMLElement* root = document.CreateRoot("font");

	root->CreateChild<rString>("name", m_name);
	root->CreateChild<int>("size", m_size);

	rXMLElement* glyphs = root->CreateChild("glyphs");
	rXMLElement* tc = NULL;

	for (rGlyphDataMap::const_iterator it = m_glyphs.begin(); it != m_glyphs.end(); ++it){
		rGlyphData* data = it->second;
		rXMLElement* glyph = glyphs->CreateChild("glyph");


		glyph->CreateChild<int>("scancode", data->scancode);
		glyph->CreateChild<short>("width", data->width);
		glyph->CreateChild<short>("height", data->height);
		glyph->CreateChild<short>("top", data->top);
		glyph->CreateChild<short>("leftBearing", data->leftBearing);
		glyph->CreateChild<short>("advance", data->advance);

		for (size_t i = 0; i < 4; i++){
			std::ostringstream s;
			s << "texCoord" << i;

			tc = glyph->CreateChild(s.str());
			tc->AddAttribute<float>("u", data->texCoords[i].x);
			tc->AddAttribute<float>("v", data->texCoords[i].y);
		}
	}

	document.WriteToFile(path);

	return rCONTENT_ERROR_NONE;
}