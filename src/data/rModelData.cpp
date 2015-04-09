#include "data/rModelData.hpp"

rModelData::rModelData(){
	m_skeleton = nullptr;

	m_geometry = std::make_unique<rTexCoordGeometryData>();
}

void rModelData::Clear(){
	m_geometry->Clear();
	m_meshes.clear();
	m_materials.clear();
	m_textures.clear();

	m_name.clear();
	m_path.clear();

	m_boundingBox.Empty();

	m_skeleton.reset();
}

//---------------------------------

size_t rModelData::MeshCount() const{
	return m_meshes.size();
}

rMeshData* rModelData::GetMeshData(const rString& name) const{
	auto result = m_meshes.find(name);

	if (result == m_meshes.end()){
		return nullptr;
	}
	else{
		return result->second.get();
	}
}

rMeshData* rModelData::CreateMeshData(const rString& name){
	if (m_meshes.count(name)){
		return nullptr;
	}
	else{
		rMeshDataPtr meshPtr = std::make_shared<rMeshData>(name);
		m_meshes[name] = meshPtr;

		return meshPtr.get();
	}
}

void rModelData::DeleteMeshData(const rString& name){
	m_meshes.erase(name);
}

void rModelData::GetMeshDataNames(rArrayString& names) const{
	names.clear();

	for (rMeshDataMap::const_iterator it = m_meshes.begin(); it != m_meshes.end(); ++it)
		names.push_back(it->first);
}

//---------------------------------

size_t rModelData::MaterialCount() const{
	return m_materials.size();
}

rMaterialData* rModelData::GetMaterialData(const rString& name) const{
	auto result = m_materials.find(name);
	
	if (result == m_materials.end()){
		return nullptr;
	}
	else {
		return result->second.get();
	}
}

rMaterialData* rModelData::CreateMaterialData(const rString& name){
	if (m_materials.count(name)){
		return nullptr;
	}
	else{
		rMaterialDataPtr materialPtr = std::make_shared<rMaterialData>();
		m_materials[name] = materialPtr;
		
		return materialPtr.get();
	}
}

void rModelData::DeleteMaterialData(const rString& name){
	m_materials.erase(name);
}

void rModelData::GetMaterialDataNames(rArrayString& names) const{
	names.clear();
	
	for (rMaterialDataMap::const_iterator it = m_materials.begin(); it!= m_materials.end(); ++it)
		names.push_back(it->first);
}

//---------------------------------

size_t rModelData::TextureCount() const{
	return m_textures.size();
}

rTexture2DData* rModelData::GetTextureData(const rString& name) const{
	auto result = m_textures.find(name);

	if (result == m_textures.end()){
		return nullptr;
	}
	else{
		return result->second.get();
	}
}

rTexture2DData* rModelData::CreateTextureData(const rString& name){
	if (m_textures.count(name)){
		return nullptr;
	}
	else{
		rTextureDataPtr texturePtr = std::make_shared<rTexture2DData>();
		m_textures[name] = texturePtr;
		return texturePtr.get();;
	}
}

void rModelData::DeleteTextureData(const rString& name){
	m_textures.erase(name);
}

void rModelData::GetTextureDataNames(rArrayString& names) const{
	names.clear();
	
	for (rTexture2DDataMap::const_iterator it = m_textures.begin(); it != m_textures.end(); ++it)
		names.push_back(it->first);
}

//---------------------------------

rTexCoordGeometryData* rModelData::GetGeometryData() const{
	return m_geometry.get();
}

void rModelData::SetBoundingBox(const rAlignedBox3& boundingBox){
	m_boundingBox = boundingBox;
}

void rModelData::SetName(const rString& name){
	m_name = name;
}

rString rModelData::GetName() const{
	return m_name;
}

void rModelData::SetPath(const rString& path){
	m_path = path;
}

rString rModelData::GetPath() const{
	return m_path;
}

rSkeleton* rModelData::GetSkeleton() const{
	return m_skeleton.get();
}

rSkeleton* rModelData::CreateSkeleton(){
	m_skeleton = std::make_unique<rSkeleton>();
	return m_skeleton.get();
}

const rAlignedBox3& rModelData::GetBoundingBox() const {
	return m_boundingBox;
}