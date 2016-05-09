#pragma once

#include <memory>
#include <cstdint>

#include "BuildImport.hpp"
#include "rString.hpp"

#include "stream/rIFileStream.hpp"
#include "asset/rFont.hpp"
#include "asset/rTextureData.hpp"

namespace recondite { namespace import {

	class RECONDITE_IMPORT_API FontImporter{
	public:
		FontImporter();
		~FontImporter();

	public:
		void SetAssetPathPrefix(const rString& assetPrefix);
		int AddFaceDescription(const rString& path, uint16_t size, Font::Style style);

	public:
		int ReadManifestFromPath(const rString& path);
		int ReadManifestFromStream(rIStream& stream);

		int GenerateFont(Font::Family& fontData, rTextureData& textureData);

	private:
		struct Impl;
		Impl* _impl;
	};

}}