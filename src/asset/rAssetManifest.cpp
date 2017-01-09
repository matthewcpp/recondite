#include "asset/rAssetManifest.hpp"

namespace recondite {
	void AssetManifest::Add(rAssetType type, const rString& name, const rString& path) {
		auto& content = const_cast<ContentVector&>(_Content(type));
		content.emplace_back(name, path);
	}

	bool AssetManifest::RemoveByName(rAssetType type, const rString& name) {
		auto& content = const_cast<ContentVector&>(_Content(type));

		for (size_t i = 0; i < content.size(); i++) {
			if (content[i].name == name) {
				auto it = content.begin();
				std::advance(it, i);
				content.erase(it);
				return true;
			}
		}

		false;
	}

	bool AssetManifest::RemoveByIndex(rAssetType type, size_t index) {
		auto& content = const_cast<ContentVector&>(_Content(type));

		if (index < content.size()) {
			auto it = content.begin();
			std::advance(it, index);

			content.erase(it);
			return true;
		}

		return false;
	}


	size_t AssetManifest::Count(rAssetType type) const {
		auto& content = _Content(type);

		return content.size();
	}

	bool AssetManifest::Get(rAssetType type, size_t index, rString& name, rString& path) const {
		auto& content = _Content(type);

		if (index < content.size()) {
			const ContentEntry& entry = content[index];

			name = entry.name;
			path = entry.path;

			return true;
		}
		
		return false;
	}

	void AssetManifest::Clear() {
		_models.clear();
	}

	void AssetManifest::Clear(rAssetType type) {
		auto& content = const_cast<ContentVector&>(_Content(type));
		content.clear();
	}

	const std::vector<AssetManifest::ContentEntry>& AssetManifest::_Content(rAssetType type) const {
		return _models;
	}

	void ReadAsset(recondite::AssetManifest* manifest, rXMLElement* element) {
		rAssetType assetType;
		rString val, name, path;
		element->GetAttribute("type", val);
		element->GetFirstChildNamed("name")->GetText(name);
		element->GetFirstChildNamed("path")->GetText(path);

		if (val == "model") {
			assetType = rAssetType::Model;
		}
		else {
			return;
		}

		manifest->Add(assetType, name, path);
	}

	int AssetManifest::Read(rIStream& stream) {
		rXMLDocument document;

		int error = document.LoadFromStream(stream);

		if (!error) {
			return Read(document);
		}
		else {
			return error;
		}
		
	}

	int AssetManifest::Read(const rXMLDocument& document) {
		rXMLElement* assets = document.GetRoot()->GetFirstChildNamed("assets");

		if (assets) {
			for (size_t i = 0; i < assets->NumChildren(); i++) {
				ReadAsset(this, assets->GetChild(i));
			}

			return 0;
		}

		return 1;
	}

	int AssetManifest::Write(rXMLDocument& document) const{
		rXMLElement* root = document.GetRoot();

		if (root) {
			rXMLElement* assets = root->GetFirstChildNamed("assets");

			if (!assets) {
				assets = document.GetRoot()->CreateChild("assets");
			}

			WriteNodes(_models, "model", assets);

			return 0;
		}

		return 1;
	}

	int AssetManifest::Write(rOStream& stream) const {
		rXMLDocument document;

		rXMLElement* assets = document.CreateRoot("manifest");
		Write(document);

		return document.WriteToStream(stream);
	}

	void AssetManifest::WriteNodes(const std::vector<AssetManifest::ContentEntry>& contentVector, const rString& type, rXMLElement* assetsNode) const{
		for (size_t i = 0; i < contentVector.size(); i++) {
			auto& entry = contentVector[i];

			rXMLElement* asset = assetsNode->CreateChild("asset");
			asset->AddAttribute("type", type);
			asset->CreateChild("name", entry.name);
			asset->CreateChild("path", entry.path);
		}
	}

	void AssetManifest::ReadNodes(rXMLElement* element) {

	}
}

