#include "asset/rFontData.hpp"

#include "rString.hpp"

#include <vector>
#include <memory>


struct rFontData::FaceData::Impl{
	uint16_t size;
	rFontStyle style;

	int16_t lineHeight;
	int16_t ascender;
	int16_t descender;

	std::vector<rFontGlyph> glyphs;
};

rFontData::FaceData::FaceData(uint16_t size, rFontStyle style){
	_impl = new Impl();

	_impl->size = size;
	_impl->style = style;
}

rFontData::FaceData::~FaceData(){
	delete _impl;
}

void rFontData::FaceData::AllocateGlyphs(uint32_t size){
	_impl->glyphs.resize(size);
}

void rFontData::FaceData::SetFaceMetrics(int16_t lineHeight, int16_t ascender, int16_t descender){
	_impl->lineHeight = lineHeight;
	_impl->ascender = ascender;
	_impl->descender = descender;
}

bool rFontData::FaceData::SetGlyph(uint32_t index, uint32_t scancode, int16_t width, int16_t height, int16_t top, int16_t leftBearing, int16_t advance, const rVector2& uvOrigin, const rVector2& uvSize){
	if (index >= _impl->glyphs.size()) return false;

	rFontGlyph& glyph = _impl->glyphs[index];

	glyph.scancode = scancode;
	glyph.width = width;
	glyph.height = height;
	glyph.top = top;
	glyph.leftBearing = leftBearing;
	glyph.advance = advance;
	glyph.uvOrigin = uvOrigin;
	glyph.uvSize = uvSize;

	return true;
}

struct rFontData::Impl{
	std::vector<std::unique_ptr<FaceData>> faceData;
};

rFontData::rFontData(){
	_impl = new Impl();
}

rFontData::~rFontData(){
	delete _impl;
}

size_t rFontData::NumFaces(){
	return _impl->faceData.size();
}

rFontData::FaceData* rFontData::GetFace(size_t index){
	if (index >= _impl->faceData.size())
		return nullptr;
	else
		return _impl->faceData[index].get();
}

rFontData::FaceData* rFontData::CreateFontFace(uint16_t size, rFontStyle style){
	FaceData* faceData = new FaceData(size, style);
	_impl->faceData.emplace_back(faceData);
	return faceData;
}

