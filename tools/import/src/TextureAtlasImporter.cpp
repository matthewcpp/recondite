#include "TextureAtlasImporter.hpp"

#include "3rdParty/stb_image.h"

namespace recondite { namespace import {

	int TextureAtlasImporter::ReadManifest(const rString& path) {
		rIFileStream stream(path);
		if (!stream.IsOk()) return 1;

		rXMLDocument doc;
		doc.LoadFromStream(stream);

		rXMLElement* entries = doc.GetRoot();

		for (size_t i = 0; i < entries->NumChildren(); i++) {
			rXMLElement* entry = entries->GetChild(i);

			std::unique_ptr<AtlasItem> atlasItem(new AtlasItem());

			entry->GetChild(0)->GetText(atlasItem->name);
			entry->GetChild(1)->GetText(atlasItem->path);

			int result = stbi_info(path.c_str(), &atlasItem->imageSize.x, &atlasItem->imageSize.y, 0);

			if (result == 0) {
				_atlasEntries.push_back(std::move(atlasItem));
			}
		}

		return 1;
	}

	int TextureAtlasImporter::GenerateAtlas(const rString& path, rTextureAtlasData& textureAtlasData, rTextureData& textureData) {
		int error = ReadManifest(path);

		return error;
	}
}}