#include "data/rFontData.hpp"

rGlyphData::rGlyphData(){
	data = NULL;
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

	m_textureFile = m_name + "_texture.rtex";

	rContentError error = WriteGlyphFile (rPath::Assemble(dir , m_name , ".rfnt"));
	error = m_textureData.WriteToPath(rPath::Combine(dir , m_textureFile));

	return error;
}

rContentError rFontData::WriteGlyphFile(const rString& path) const{
	rXMLDocument document;
	rXMLElement* root = document.CreateRoot("font");

	root->CreateChild<rString>("name", m_name);
	root->CreateChild<int>("size", m_size);
	root->CreateChild<rString>("textureFile", m_textureFile);

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

rContentError rFontData::LoadFromStream(std::istream& glyph, std::istream& texture){
	Clear();

	ReadGlyphFile(glyph);
	m_textureData.LoadFromStream(texture);

	m_textureGenerated = true;

	return rCONTENT_ERROR_NONE;
}

rContentError rFontData::LoadFromFile(const rString& dir, const rString& name){
	std::string glyphPath(dir + name + ".rfnt");
	std::string texturePath(dir + name + "_texture.rtex");

	std::ifstream glyphStream(glyphPath.c_str());
	std::ifstream textureStream(texturePath.c_str(), std::ios::binary);

	m_path = glyphPath;

	LoadFromStream(glyphStream, textureStream);

	return rCONTENT_ERROR_NONE;
}

rContentError rFontData::ReadGlyphFile(std::istream& stream){
	rXMLDocument document;
	document.LoadFromStream(stream);
	rXMLElement* root = document.GetRoot();

	rXMLElement* prop = root->GetFirstChildNamed("name");
	if (prop)
		m_name = prop->Text();

	prop = root->GetFirstChildNamed("size");
	if (prop)
		prop->GetText<int>(m_size);

	prop = root->GetFirstChildNamed("textureFile");
	if (prop)
		m_textureFile = prop->Text();

	ParseGlyphs(document);

	return rCONTENT_ERROR_NONE;
}

rContentError rFontData::ParseGlyphs(rXMLDocument& document){
	rXMLElement* glyphs = document.GetRoot()->GetFirstChildNamed("glyphs");

	rXMLElement* prop = NULL;

	for (size_t i = 0; i < glyphs->NumChildren(); i++){
		rXMLElement* data = glyphs->GetChild(i);
		rGlyphData* glyph = new rGlyphData();

		prop = data->GetFirstChildNamed("scancode");
		if (prop)
			prop->GetText<int>(glyph->scancode);
		
		prop = data->GetFirstChildNamed("width");
		if (prop)
			prop->GetText<short>(glyph->width);

		prop = data->GetFirstChildNamed("height");
		if (prop)
			prop->GetText<short>(glyph->height);

		prop = data->GetFirstChildNamed("top");
		if (prop)
			prop->GetText<short>(glyph->top);

		prop = data->GetFirstChildNamed("leftBearing");
		if (prop)
			prop->GetText<short>(glyph->leftBearing);

		prop = data->GetFirstChildNamed("advance");
		if (prop)
			prop->GetText<short>(glyph->advance);

		for (size_t i = 0; i < 4; i++){
			std::ostringstream s;
			s << "texCoord" << i;

			float u,v;

			prop = data->GetFirstChildNamed(s.str());
			if (prop){
				prop->GetAttribute<float>("u", u);
				prop->GetAttribute<float>("v", v);

				glyph->texCoords[i].Set(u,v);
			}
		}

		m_glyphs[glyph->scancode] = glyph;
	}

	return rCONTENT_ERROR_NONE;
}

rContentError rFontData::LoadFontDataFromFile(const rString& path){
	std::ifstream file(path.c_str());

	if (file){
		return LoadFontDataFromStream(file);
	}
	else{
		return rCONTENT_ERROR_FILE_NOT_FOUND;
	}
}

rContentError rFontData::LoadTextureFromFile(const rString& path){
	std::ifstream file(path.c_str());

	if (file){
		return LoadTextureFromStream(file);
	}
	else{
		return rCONTENT_ERROR_FILE_NOT_FOUND;
	}
}

rContentError rFontData::LoadTextureFromStream(std::istream& stream){
	rContentError error = m_textureData.LoadFromStream(stream);
	m_textureGenerated = (error == rCONTENT_ERROR_NONE);

	return error;
}

rContentError rFontData::LoadFontDataFromStream(std::istream& stream){
	Clear();
	ReadGlyphFile(stream);
	m_textureGenerated = true;
	return rCONTENT_ERROR_NONE;
}

rString rFontData::TextureFile() const{
	return m_textureFile;
}

rString rFontData::GetPath() const{
	return m_path;
}

void rFontData::GetGlyphData(rGlyphDataArray& glyphs) const{
	glyphs.clear();
	glyphs.reserve(m_glyphs.size());

	for (rGlyphDataMap::const_iterator it = m_glyphs.begin(); it != m_glyphs.end(); ++it)
		glyphs.push_back(it->second);
}
