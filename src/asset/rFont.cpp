#include "asset/rFont.hpp"

#include <memory>
#include <vector>

namespace Font{
	struct FaceDataMetrics{
		uint16_t size;
		Font::Style style;

		int16_t lineHeight;
		int16_t ascender;
		int16_t descender;
	};

	struct Face::Impl{
		FaceDataMetrics metrics;
		Family* family;
		std::vector<Glyph> glyphs;
	};

	Face::Face(uint16_t size, Font::Style style, Family* family){
		_impl = new Impl();

		_impl->metrics.size = size;
		_impl->metrics.style = style;
		_impl->family = family;
	}

	Face::Face(Family* family){
		_impl = new Impl();
		_impl->metrics.size = 0;
		_impl->metrics.style = Style::Normal;
		_impl->family = family;
	}

	Face::~Face(){
		delete _impl;
	}

	Family* Face::GetFamily(){
		return _impl->family;
	}

	bool SearchForGlyph(uint32_t scancode, const std::vector<Glyph>& glyphs, size_t min, size_t max, size_t& result){
		if (min == max){
			if (glyphs[min].scancode == scancode){
				result = min;
				return true;
			}
			else{
				return false;
			}
		}
		else{
			size_t midpoint = (min + max) / 2;

			if (glyphs[midpoint].scancode == scancode){
				result = midpoint;
				return true;
			}
			else if (glyphs[midpoint].scancode > scancode){
				return SearchForGlyph(scancode, glyphs, min, midpoint - 1, result);
			}
			else{
				return SearchForGlyph(scancode, glyphs, midpoint + 1, max, result);
			}
		}
	}

	Glyph* Face::GetGlyph(uint32_t scancode){
		size_t result;
		
		if (SearchForGlyph(scancode, _impl->glyphs, 0, _impl->glyphs.size() - 1, result)){
			return &_impl->glyphs[result];
		}
		else{
			return nullptr;
		}
	}

	rSize Face::MeasureString(const rString& text){
		return rSize(0, 0);
	}


	void Face::AllocateGlyphs(size_t size){
		_impl->glyphs.resize(size);
	}

	bool Face::SetGlyph(uint32_t index, uint32_t scancode, int16_t width, int16_t height, int16_t top, int16_t leftBearing, int16_t advance, const rVector2& uvOrigin, const rVector2& uvSize){
		if (index >= _impl->glyphs.size()) return false;

		Glyph& glyph = _impl->glyphs[index];

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

	void Face::SetFaceMetrics(int16_t lineHeight, int16_t ascender, int16_t descender){
		_impl->metrics.lineHeight = lineHeight;
		_impl->metrics.ascender = ascender;
		_impl->metrics.descender = descender;
	}

	uint16_t Face::GetSize(){
		return _impl->metrics.size;
	}

	Style Face::GetStyle(){
		return _impl->metrics.style;
	}

	int16_t Face::GetAscender(){
		return _impl->metrics.ascender;
	}

	int16_t Face::GetDescender(){
		return _impl->metrics.descender;
	}

	int16_t Face::GetLineHeight(){
		return _impl->metrics.lineHeight;
	}

	struct rFontFileHeader;

	struct Family::Impl{
		rString name;
		std::vector<std::unique_ptr<Face>> faces;

		void InitHeader(rFontFileHeader& header);
	};

	Family::Family(){
		_impl = new Impl();
	}

	Family::~Family(){
		delete _impl;
	}

	Face* Family::GetFace(size_t size, Font::Style style){
		for (size_t i = 0; i < _impl->faces.size(); i++){
			if (_impl->faces[i]->GetSize() == size && _impl->faces[i]->GetStyle() == style)
				return _impl->faces[i].get();
		}

		return nullptr;
	}

	Face* Family::CreateFace(size_t size, Font::Style style){
		Face* face = new Face(size, style, this);
		_impl->faces.emplace_back(face);

		return face;
	}

	rString Family::GetName(){
		return _impl->name;
	}

	void Family::SetName(const rString& name){
		_impl->name = name;
	}

	const uint32_t MagicNumber = 1953392242; //rfnt
	const uint32_t CurrentVersion = 1;

	struct rFontFileHeader{
		uint32_t magicNumber;
		uint32_t version;
		uint32_t numFaces;
		uint32_t unused1;
		uint32_t unused2;
		uint32_t unused3;
	};

	void Family::Impl::InitHeader(rFontFileHeader& header){
		header.magicNumber = MagicNumber;
		header.version = CurrentVersion;
		header.numFaces = faces.size();
		header.unused1 = 0;
		header.unused2 = 0;
		header.unused3 = 0;
	}

	int Family::Read(rIStream& stream){
		rFontFileHeader header;
		stream.Read((char*)&header, sizeof(rFontFileHeader));

		for (uint32_t i = 0; i < header.numFaces; i++){
			Face* face = new Face(this);
			stream.Read((char*)&face->_impl->metrics, sizeof(FaceDataMetrics));

			uint32_t numGlyphs;
			stream.Read((char*)&numGlyphs, sizeof(uint32_t));
			face->_impl->glyphs.resize(numGlyphs);

			stream.Read((char*)face->_impl->glyphs.data(), sizeof(Glyph) * numGlyphs);

			_impl->faces.emplace_back(face);
		}

		return 0;
	}

	int Family::Write(rOStream& stream){
		rFontFileHeader header;
		_impl->InitHeader(header);
		stream.Write((char*)&header, sizeof(rFontFileHeader));

		for (size_t i = 0; i < _impl->faces.size(); i++){
			Face* face = _impl->faces[i].get();

			stream.Write((char*)&face->_impl->metrics, sizeof(FaceDataMetrics));

			uint32_t numGlyphs = face->_impl->glyphs.size();
			stream.Write((char*)&numGlyphs, sizeof(uint32_t));

			stream.Write((char*)face->_impl->glyphs.data(), sizeof(Glyph) * numGlyphs);
		}

		return 0;
	}
}
