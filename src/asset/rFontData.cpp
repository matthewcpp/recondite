#include "asset/rFontData.hpp"

#include <memory>


namespace recondite {
	struct FontData::Impl {
		std::unique_ptr<rTextureData> textureData;
		std::unique_ptr<Font::Family> fontFamily;

		Impl();
	};

	FontData::Impl::Impl() {
		textureData.reset(new rTextureData());
		fontFamily.reset(new Font::Family());
	}

	FontData::FontData() {
		_impl = new Impl();
	}

	FontData::~FontData() {
		delete _impl;
	}

	int FontData::Read(rIStream& stream) {
		int error =_impl->fontFamily->Read(stream);

		if (!error)
		 error = _impl->textureData->Read(stream);

		return error;
	}

	int FontData::Write(rOStream& stream) {
		int error = _impl->fontFamily->Write(stream);

		if (!error)
			error = _impl->textureData->Write(stream);

		return error;
	}

	Font::Family* FontData::GetFamily() {
		return _impl->fontFamily.get();
	}

	Font::Family* FontData::ReleaseFamily() {
		return _impl->fontFamily.release();
	}

	rTextureData* FontData::GetTextureData() {
		return _impl->textureData.get();
	}

}
