#pragma once

#include <vector>


#include "rBuild.hpp"
#include "rDefs.hpp"
#include "rString.hpp"
#include "rRect.hpp"
#include "rPath.hpp"

#include "asset/rTextureAtlasData.hpp"
#include "asset/rTextureData.hpp"
#include "stream/rIFileStream.hpp"
#include "xml/rXMLDocument.hpp"

#include "RectPacker.hpp"

namespace recondite { namespace import {
	class RECONDITE_API TextureAtlasImporter {
	public:
		TextureAtlasImporter();

	public:
		int ReadManifestFromPath(const rString& path);
		int ReadManifestFromStream(rIStream& stream);

		int GenerateAtlas(rTextureAtlasData& textureAtlasData, rTextureData& textureData);
		bool AddImage(const rString& name, const rString& path);

		void SetAssetPathPrefix(const rString& assetPrefix);

		void Clear();

	private:
		struct AtlasItem : public RectPacker::Item{
			AtlasItem(const rString& n, const rString& p) : name(n), path(p){}
			rString name;
			rString path;
		};

		std::vector<std::unique_ptr<AtlasItem>> _atlasEntries;
		rString _assetPathPrefix;
		int _needsAlphaChannel;

		rNO_COPY_CLASS(TextureAtlasImporter)
	};
}}