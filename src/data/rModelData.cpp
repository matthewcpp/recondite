#include "data/rModelData.hpp"

rModelData::rModelData(){
	m_skeleton = NULL;
}

rModelData::~rModelData(){
	Clear();
}

void rModelData::Clear(){
	for (rMeshDataMap::iterator it = m_meshes.begin(); it != m_meshes.end(); ++it)
		delete it->second;
	
	for (rMaterialDataMap::iterator it = m_materials.begin(); it!= m_materials.end(); ++it)
		delete it->second;
	
	for (rTexture2DDataMap::iterator it = m_textures.begin(); it != m_textures.end(); ++it)
		delete it->second;
	
	m_geometry.Clear();
	m_meshes.clear();
	m_materials.clear();
	m_textures.clear();

	m_name.clear();
	m_path.clear();

	m_boundingBox.Empty();

	if (m_skeleton){
		delete m_skeleton;
	}

	m_skeleton = NULL;
}

size_t rModelData::MeshCount() const{
	return m_meshes.size();
}

rMeshData* rModelData::GetMeshData(const rString& name) const{
	rMeshData* meshData = NULL;
	
	rMeshDataMap::const_iterator result = m_meshes.find(name);
	
	if (result != m_meshes.end()){
		meshData = result->second;
	}
	
	return meshData;
}

rMeshData* rModelData::CreateMeshData(const rString& name){
	if (m_meshes.count(name)){
		return NULL;
	}
	else{
		rMeshData* meshData = new rMeshData();
		meshData->name = name;
		m_meshes[name] = meshData;
		
		return meshData;
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

size_t rModelData::MaterialCount() const{
	return m_materials.size();
}

rMaterialData* rModelData::GetMaterialData(const rString& name) const{
	rMaterialData* materialData = NULL;
	
	rMaterialDataMap::const_iterator result = m_materials.find(name);
	
	if (result != m_materials.end())
		materialData = result->second;
	
	return materialData;
}

rMaterialData* rModelData::CreateMaterialData(const rString& name){
	if (m_materials.count(name)){
		return NULL;
	}
	else{
		rMaterialData* materialData = new rMaterialData();
		m_materials[name] = materialData;
		
		return materialData;
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

size_t rModelData::TextureCount() const{
	return m_textures.size();
}

rTexture2DData* rModelData::GetTextureData(const rString& name) const{
	rTexture2DData* textureData = NULL;
	
	rTexture2DDataMap::const_iterator result= m_textures.find(name);
	
	if (result != m_textures.end()){
		textureData = result->second;
	}
	
	return textureData;
}

rTexture2DData* rModelData::CreateTextureData(const rString& name){
	if (m_textures.count(name)){
		return NULL;
	}
	else{
		rTexture2DData* textureData = new rTexture2DData();
		m_textures[name] = textureData;
		return textureData;
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

rGeometryData& rModelData::GetGeometryData(){
	return m_geometry;
}

const rGeometryData& rModelData::GetGeometryData() const{
	return m_geometry;
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
	return m_skeleton;
}

rSkeleton* rModelData::CreateSkeleton(){
	if (m_skeleton){
		return NULL;
	}
	else{
		m_skeleton = new rSkeleton();
		return m_skeleton;
	}
}

const rAlignedBox3& rModelData::GetBoundingBox() const {
	return m_boundingBox;
}

//---------------------
rMeshData::rMeshData(const rString& n, const rString& buf, const rString& mat){
	name = n;
	buffer = buf;
	material = mat;
}
