#pragma once

#include <memory>

#include "BuildImport.hpp"
#include "rString.hpp"

#include "asset/rTextureAtlasData.hpp"
#include "asset/rTextureData.hpp"
#include "stream/rIStream.hpp"

#include "RectPacker.hpp"

namespace recondite { namespace import {
	class RECONDITE_IMPORT_API TextureAtlasImporter {
	public:
		TextureAtlasImporter();
		~TextureAtlasImporter();

	public:
		int ReadManifestFromPath(const rString& path);
		int ReadManifestFromStream(rIStream& stream);

		int GenerateAtlas(rTextureAtlasData& textureAtlasData, rTextureData& textureData);
		bool AddImage(const rString& name, const rString& path);

		void SetAssetPathPrefix(const rString& assetPrefix);

		void Clear();

	private:

		struct Impl;
		std::unique_ptr<Impl> _impl;

		rNO_COPY_CLASS(TextureAtlasImporter)
	};
}}