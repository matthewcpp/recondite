#include "TextureAtlasImporter.hpp"

#include <vector>

#include "3rdParty/stb_image.h"

#include "rRect.hpp"
#include "rPath.hpp"

#include "xml/rXMLDocument.hpp"

namespace recondite { namespace import {
	struct AtlasItem : public RectPacker::Item{
		AtlasItem(const rString& n, const rString& p) : name(n), path(p){}
		rString name;
		rString path;
	};

	struct TextureAtlasImporter::Impl{
		std::vector<std::unique_ptr<AtlasItem>> atlasEntries;
		rString assetPathPrefix;
		int needsAlphaChannel;
	};

	TextureAtlasImporter::TextureAtlasImporter(){
		_impl.reset(new Impl);

		_impl->needsAlphaChannel = false;
	}

	TextureAtlasImporter::~TextureAtlasImporter(){}

	int TextureAtlasImporter::ReadManifestFromPath(const rString& path) {
		rIFileStream stream(path);

		rPath::Split(path, &_impl->assetPathPrefix, nullptr);
		
		return ReadManifestFromStream(stream);
	}

	int TextureAtlasImporter::ReadManifestFromStream(rIStream& stream){
		if (!stream.IsOk()) return 1;

		rXMLDocument doc;
		int error = doc.LoadFromStream(stream);

		if (error) return error;

		rXMLElement* entries = doc.GetRoot();

		for (size_t i = 0; i < entries->NumChildren(); i++) {
			rXMLElement* entry = entries->GetChild(i);

			rString name, path;

			entry->GetChild(0)->GetText(name);
			entry->GetChild(1)->GetText(path);

			if (!_impl->assetPathPrefix.empty()){
				path = rPath::Combine(_impl->assetPathPrefix, path);
			}

			if (!AddImage(name, path)) return 1;
		}

		return 0;
	}

	bool TextureAtlasImporter::AddImage(const rString& name, const rString& path){
		std::unique_ptr<AtlasItem> atlasItem(new AtlasItem(name, path));
		int bpp;
		int result = stbi_info(atlasItem->path.c_str(), &atlasItem->sourceSize.x, &atlasItem->sourceSize.y, &bpp);

		if (result == 1) {
			if (_impl->needsAlphaChannel == false && bpp == 4)
				_impl->needsAlphaChannel = true;

			_impl->atlasEntries.push_back(std::move(atlasItem));
			return true;
		}

		return false;
	}

	int TextureAtlasImporter::GenerateAtlas(rTextureAtlasData& textureAtlasData, rTextureData& textureData) {
		RectPacker packer;
		packer.SetMaxSize(rSize(1024, 1024));

		for (size_t i = 0; i < _impl->atlasEntries.size(); i++)
			packer.AddItem(_impl->atlasEntries[i].get());

		if (packer.Pack()){
			rSize resultSize = packer.GetResultSize();
			int bpp = _impl->needsAlphaChannel ? 4 : 3;
			textureData.Allocate(resultSize.x, resultSize.y, bpp, rColor(0,0,0,0));
			rVector2 uvOrigin, uvSize;

			for (size_t i = 0; i < _impl->atlasEntries.size(); i++){
				//write texture info to atlas file
				AtlasItem* item = _impl->atlasEntries[i].get();
				packer.CalculatePackedUVForItem(item, uvOrigin, uvSize);
				textureAtlasData.AddEntry(_impl->atlasEntries[i]->name, _impl->atlasEntries[i]->sourceSize, uvOrigin, uvSize);

				//write image data into texture
				int width, height, n;
				
				unsigned char *data = stbi_load(item->path.c_str(), &width, &height, &n, bpp);
				
				for (int h = 0; h < height; h++){
					for (int w = 0; w < width; w++){
						int index = (h * width * bpp) + (w * bpp);

						if (_impl->needsAlphaChannel)
							textureData.SetPixel(item->packedLocation.x + w, item->packedLocation.y + h, data[index], data[index + 1], data[index + 2], data[index + 3]);
						else
							textureData.SetPixel(item->packedLocation.x + w, item->packedLocation.y + h, data[index], data[index + 1], data[index + 2]);
					}
				}

				
				stbi_image_free(data);
			}

			return 0;
		}
		else{
			return 1;
		}
	}

	void TextureAtlasImporter::Clear(){
		_impl->atlasEntries.clear();
	}

	void TextureAtlasImporter::SetAssetPathPrefix(const rString& assetPrefix){
		_impl->assetPathPrefix = assetPrefix;
	}
}}