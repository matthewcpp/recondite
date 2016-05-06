#ifndef R_FONTDATA_HPP
#define R_FONTDATA_HPP

#include "rBuild.hpp"
#include "rDefs.hpp"

#include "rFontGlyph.hpp"

#include "stream/rIStream.hpp"
#include "stream/rOStream.hpp"

class RECONDITE_API rFontData{
public:
	rFontData();
	~rFontData();

public:
	class RECONDITE_API FaceData{
	public:
		FaceData(uint16_t size, rFontStyle style);
		~FaceData();

	public:
		void AllocateGlyphs(uint32_t size);
		bool SetGlyph(uint32_t index, uint32_t scancode, int16_t width, int16_t height, int16_t top, int16_t leftBearing, int16_t advance, const rVector2& uvOrigin, const rVector2& uvSize);
		void SetFaceMetrics(int16_t lineHeight, int16_t ascender, int16_t descender);

	private:
		struct Impl;
		Impl* _impl;
	};

public:
	FaceData* CreateFontFace(uint16_t size, rFontStyle style);
	size_t NumFaces();
	FaceData* GetFace(size_t index);

	

public:
	int Read(rIStream& stream);
	int Write(rOStream& stream);

private:
	struct Impl;
	Impl* _impl;
};

#endif
