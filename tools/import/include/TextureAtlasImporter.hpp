#pragma once

#include <vector>


#include "rBuild.hpp"
#include "rDefs.hpp"
#include "rString.hpp"
#include "rRect.hpp"

#include "asset/rTextureAtlasData.hpp"
#include "asset/rTextureData.hpp"
#include "stream/rIFileStream.hpp"
#include "xml/rXMLDocument.hpp"

namespace recondite { namespace import {
	class RECONDITE_API TextureAtlasImporter {
	public:
		TextureAtlasImporter() {}
		int GenerateAtlas(const rString& path, rTextureAtlasData& textureAtlasData, rTextureData& textureData);

	private:
		int ReadManifest(const rString& path);
		
	private:
		struct AtlasItem{
			rString name;
			rString path;
			

			rSize imageSize;
			rRect packedArea;
		};

		std::vector<std::unique_ptr<AtlasItem>> _atlasEntries;

		rNO_COPY_CLASS(TextureAtlasImporter)
	};
}}