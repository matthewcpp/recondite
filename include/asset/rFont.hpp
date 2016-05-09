#ifndef R_FONT_HPP
#define R_FONT_HPP

#include <map>
#include <algorithm>
#include <cstdint>

#include "rBuild.hpp"
#include "rString.hpp"

#include "asset/rTexture.hpp"

#include "stream/rIStream.hpp"
#include "stream/rOStream.hpp"

#include "rSize.hpp"



namespace Font{
	enum class Style : unsigned char{
		Normal, Bold, Italic
	};

	struct RECONDITE_API Glyph{
		uint32_t scancode;
		int16_t width;
		int16_t height;
		int16_t top;
		int16_t leftBearing;
		int16_t advance;

		rVector2 uvOrigin;
		rVector2 uvSize;
	};

	class Family;

	class RECONDITE_API Face{
	public:
		Face(uint16_t size, Style style);
		Face();
		~Face();

		Glyph* GetGlyph(uint32_t scancode);

		void AllocateGlyphs(size_t size);
		size_t NumGlyphs();

		void SetFaceMetrics(int16_t lineHeight, int16_t ascender, int16_t descender);
		bool SetGlyph(uint32_t index, uint32_t scancode, int16_t width, int16_t height, int16_t top, int16_t leftBearing, int16_t advance, const rVector2& uvOrigin, const rVector2& uvSize);

		rSize MeasureString(const rString& text);

		uint16_t GetSize();
		Style GetStyle();

	private:
		friend class Family;

	private:
		struct Impl;
		Impl* _impl;
	};

	class RECONDITE_API Family{
	public:
		Family();
		~Family();

		Face* GetFace(size_t size, Style style);
		Face* CreateFace(size_t size, Style style);

		rString GetName();
		void SetName(const rString& name);

	public:
		int Read(rIStream& stream);
		int Write(rOStream& stream);

	private:
		struct Impl;
		Impl* _impl;
	};
}

#endif
