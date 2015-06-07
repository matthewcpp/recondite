#ifndef R_ASSETMANAGER_HPP
#define R_ASSETMANAGER_HPP

#include <functional>
#include <memory>
#include <map>

#include "rFileSystem.hpp"
#include "rString.hpp"

template <class Asset, class AssetData, class AssetFile>
class rAssetManager{
public:
	rAssetManager(rFileSystem* fileSystem);

	typedef Asset AssetType;
	typedef AssetData AssetDataType;
	typedef AssetFile AssetFileType;
	typedef std::function<bool(Asset*)> IteratorFunc;

public:
	Asset* LoadFromData(const AssetData& data, const rString& name);
	Asset* LoadFromPath(const rString& path, const rString& name);
	Asset* LoadOrRetain(const rString& path, const rString& name);

	Asset* Get(const rString& name);

	void ForEach(IteratorFunc func);

public:
	Asset* Retain(const rString& name);
	void Release(const rString& name);

	void Clear();

protected:
	virtual Asset* CreateAssetFromData(const AssetData& assetData, const rString& name) = 0;
	virtual void DisposeAsset(Asset* asset) = 0;

	void AddAsset(const rString& name, Asset* asset);

protected:
	rFileSystem* m_fileSystem;

private:
	struct AssetEntry{
		AssetEntry(Asset* a){ retainCount = 0; asset.reset(a); }

		int retainCount;
		std::unique_ptr<Asset> asset;
	};

	typedef std::shared_ptr<AssetEntry> AssetEntryRef;
	typedef std::map<rString, AssetEntryRef> AssetEntryMap;

	AssetEntryMap m_assets;
};

template <class Asset, class AssetData, class AssetFile>
rAssetManager<Asset, AssetData, AssetFile>::rAssetManager(rFileSystem* fileSystem){
	m_fileSystem = fileSystem;
}

template <class Asset, class AssetData, class AssetFile>
void rAssetManager<Asset, AssetData, AssetFile>::AddAsset(const rString& name, Asset* asset){
	m_assets[name].reset(new AssetEntry(asset));
}

template <class Asset, class AssetData, class AssetFile>
Asset* rAssetManager<Asset, AssetData, AssetFile>::LoadFromData(const AssetData& data, const rString& name){
	Asset* asset = nullptr;

	if (!m_assets.count(name)){
		asset = CreateAssetFromData(data, name);

		if (asset) AddAsset(name , asset);
	}

	return asset;
}

template <class Asset, class AssetData, class AssetFile>
Asset* rAssetManager<Asset, AssetData, AssetFile>::LoadFromPath(const rString& path, const rString& name){
	Asset* asset = nullptr;

	std::unique_ptr<AssetData> dataPtr;
	rContentError error = AssetFile::Read(m_fileSystem, path, dataPtr);

	if (dataPtr && error == rContentError::None){
		asset = LoadFromData(*dataPtr, name);
	}

	return asset;
}

template <class Asset, class AssetData, class AssetFile>
Asset* rAssetManager<Asset, AssetData, AssetFile>::LoadOrRetain(const rString& path, const rString& name){
	Asset* asset = Retain(name);

	if (!asset)
		asset = LoadFromPath(path, name);

	return asset;
}

template <class Asset, class AssetData, class AssetFile>
Asset* rAssetManager<Asset, AssetData, AssetFile>::Get(const rString& name){
	if (m_assets.count(name)){
		return m_assets[name]->asset.get();
	}
	else{
		return nullptr;
	}
}

template <class Asset, class AssetData, class AssetFile>
void rAssetManager<Asset, AssetData, AssetFile>::ForEach(IteratorFunc func){
	for (auto entry : m_assets){
		if (!func(entry.second->asset.get())) break;
	}
}

template <class Asset, class AssetData, class AssetFile>
Asset* rAssetManager<Asset, AssetData, AssetFile>::Retain(const rString& name){
	if (m_assets.count(name)){
		typename AssetEntryRef& ref = m_assets[name];
		ref->retainCount += 1;

		return ref->asset.get();
	}
	else{
		return nullptr;
	}
}

template <class Asset, class AssetData, class AssetFile>
void rAssetManager<Asset, AssetData, AssetFile>::Release(const rString& name){
	if (m_assets.count(name)){
		typename AssetEntryRef& ref = m_assets[name];
		ref->retainCount -= 1;

		if (ref->retainCount <= 0){
			DisposeAsset(ref->asset.get());
			m_assets.erase(name);
		}
	}
}

template <class Asset, class AssetData, class AssetFile>
void rAssetManager<Asset, AssetData, AssetFile>::Clear(){
	for (auto entry : m_assets){
		DisposeAsset(entry.second->asset.get());
	}

	m_assets.clear();
}

#endif